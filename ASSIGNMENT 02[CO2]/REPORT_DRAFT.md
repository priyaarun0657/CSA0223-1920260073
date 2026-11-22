# CSA02 C Programming – Assignment 2 (CO2) – Report draft

**Student:**   **Register number:**   **Compiler:** GCC 13.3.0 (`gcc -Wall -Wextra`)
**GitHub:** `https://github.com/<your-username>/CSA02--Assignment2`

> All figures below are copied from the real runs in `BUILD_RESULTS.md` and the `output_*.png` screenshots.
> Operation counts (divisions, iterations, calls) are the primary evidence; timings vary between runs.

---

## Q1 – Precedence, associativity and the discount bug (K4)  `Task01/`

### Operator-by-operator order
`total = price * qty - price * qty * 15 / 100 * senior + price * qty * 5 / 100;`

`*` and `/` bind tighter than `+` and `-`; operators of equal precedence group left-to-right; `=` is lowest and right-to-left. So:

1. `T1 = price*qty`
2. `T2 = (((price*qty)*15)/100)*senior`   – three left-to-right steps, the division is **integer** division
3. `T3 = ((price*qty)*5)/100`             – integer division
4. `total = (T1 - T2) + T3`  – then stored by `=`

`net = total > 1000 ? total - 50 : total;` parses as `net = ((total > 1000) ? (total - 50) : total)` (`-` > `>` > `?:` > `=`).

### Predictions (before running) vs observed

| Bill | price, qty, senior | predicted total / net | observed total / net | intended total / net |
|---|---|---|---|---|
| A | 120, 10, 1 | 1080 / 1030 | 1080 / 1030 ✔ | 1071.00 / 1021.00 |
| B | 45, 7, 0 | 330 / 330 | 330 / 330 ✔ | 330.75 / 330.75 |
| C | 333, 3, 1 | 899 / 899 | 899 / 899 ✔ | 891.61 / 891.61 |

### Expressions that differ from the pharmacist's intention
1. **GST on the wrong base.** `price*qty*5/100` taxes the *undiscounted* gross; GST should be 5 % of (gross − discount). Bill A is overcharged Rs 9 (1080 vs 1071), Bill C Rs 7.39.
2. **Integer division.** `…*5/100` and `…*15/100` truncate: 15.75 → 15 (Bill B, −0.75), 149.85 → 149, 49.95 → 49. Paise are silently lost.
3. **`net`** compares the (wrong) `total` with 1000, so Bill A gets Rs 1030 instead of Rs 1021 – the statement itself is fine, its input is wrong. (Assumption: the Rs 50 offer applies to the final payable amount.)
4. `* senior` only works if `senior` is exactly 0 or 1; any other value scales the discount. Also `price*qty*15` can overflow `int` for very large bills.

### Inquiry – why `count = count++ + 1;` is undefined behaviour
`count` is modified twice – by `++` and by `=` – and no rule sequences those two side effects, so the C standard makes the whole expression undefined (C11 6.5p2: unsequenced modification of the same object). Any result is legal. With `-Wall`, gcc reports `warning: operation on 'count' may be undefined [-Wsequence-point]` (screenshot). On this compiler it printed 6, but that is not guaranteed.

### Design decision
```c
double gross    = (double)price * qty;
double discount = senior ? gross * 15.0 / 100.0 : 0.0;
double taxable  = gross - discount;
double payable  = taxable * 1.05;          /* or taxable + gst */
double net      = payable > 1000.0 ? payable - 50.0 : payable;
```
Intermediate variables **and** brackets only where they clarify. Each step has a name that mirrors the business rule (gross → discount → taxable → GST), so the GST-base bug becomes visible, and each value can be printed/tested. In production the amounts would be held as integer paise to avoid floating-point rounding.

### Alternative – intermediate variables
* Operations (counted from the source): the single expression does 6 multiplications + 2 divisions + 1 subtraction + 1 addition = 10; the version with `gross/discount/tax` does 4 multiplications + 2 divisions + 1 sub + 1 add = 8, because `price*qty` is computed once. An optimising compiler removes this difference (common-subexpression elimination), so time is O(1) in both.
* Extra space: three or four temporaries (typically registers) – O(1).
* Correctness/readability: much better; the bug sits in one named line instead of a 60-character expression.

---

## Q2 – When does short-circuit evaluation matter? (K4)  `Task02/`

### Experiments and what they show
* `0 && f()` and `1 || f()` – `f()` is **not** evaluated; `1 && f()` and `0 || f()` – it **is**.
* `0 & f()` – bitwise `&` has no short-circuit; `f()` runs anyway. On values, `1 && 2 = 1` but `1 & 2 = 0`, so `&` is not a drop-in for `&&` on conditions.

### Slow-call counts, 1000 passengers (20 % senior, 50 % eligible class, 10 % card holders)

| Version | Slow `verify_card()` calls | Passengers granted |
|---|---|---|
| V1 `(senior&&elig) \|\| verify` | **887** | 185 |
| V2 `verify \|\| (senior&&elig)` | 1000 | 185 |
| V3 nested `if` (V1 order) | 887 | 185 |
| V4 `(senior & elig) \| verify` | 1000 | 185 |

Effect of how often the cheap test is true (`q2_calls_chart.png`): P = 2.5 % → 964 vs 1000; 10 % → 887; 25 % → 738; 81 % → 189.

### Answer
Put the **cheap and decisive** condition first: for `A && B` the cheap, most-likely-false one; for `A || B` the cheap, most-likely-true one. Expected cost of `A || B` is `cA + (1−pA)·cB`, so order by cost/probability. The order is irrelevant when both operands are cheap and side-effect free, or when neither can skip the other.

### Changed condition – audit log
`verify_card()` now has a side effect, so order changes *behaviour*, not just cost: V1 logs 887 of 1000 passengers, V2/V4 log all 1000. If the regulation requires every passenger to be logged, short-circuit order must not decide it – log explicitly (cheap, separate from the slow check) and keep V1 order for the slow call, or accept 1000 slow calls (then order no longer matters for cost). My recommendation: **separate the audit record from the slow verification and keep the cheap-condition-first order.**

### Alternative concept
Nested `if` = same calls as V1 (887, same short-circuit). Non-short-circuit `&`/`|` = always n = 1000. For n passengers: V1/V3 between 0 and n calls, expected n·(1−p); V2/V4 exactly n. All are Θ(n) in the worst case; the saving is a constant factor (up to 81 % in the last row).

---

## Q3 – Device-status register with bitwise operators (K4)  `Task03/`

### Predicted vs observed register values
| Statement | Predicted | Observed |
|---|---|---|
| `reg = 0` | 00000000 | – |
| `switch_on(reg, LIGHT)` | 00000001 | – |
| `switch_on(reg, AC)` | 00000101 | `00000101` ✔ |
| `toggle(reg, FAN)` | 00000111 | – |
| `switch_off(reg, LIGHT)` | 00000110 | `00000110` ✔ |

Output: `AC is ON, PUMP is OFF` – equals the expected output. TODOs: `reg | (1u << dev)`, `reg & ~(1u << dev)`, `reg ^ (1u << dev)`, `(reg >> dev) & 1u`. Devices ON are counted in `q3_inquiry.c` with `reg &= reg - 1` (clears the lowest set bit): register 00000110 → 2, 11111111 → 8, 0 → 0 (kept out of `q3_register.c` so that `main()` stays exactly as given).

### Inquiry
* `<<` has higher precedence than `&`, so `reg & 1 << dev` is `reg & (1 << dev)` → the *mask value* (4 for reg=6, dev=2), truthy but not 1. `(reg & 1) << dev` tests only bit 0 and shifts the result → **0** for the same input, i.e. tests the wrong device. Correct test: `(reg >> dev) & 1`.
* A `signed char` with bit 7 set is −128; it is promoted to `int` with sign extension (`0xFFFFFF80`), `sc >> 1` is −64 (implementation-defined arithmetic shift), `sc >> 7` is −1, and `sc == 0x80` is false (gcc even warns, `-Wtype-limits`). `unsigned char` gives 128, 64, and true.

### Alternative – `char state[8]`
Time per set/clear/toggle/test: O(1) in both. Space for 1,000,000 homes: 1 MB vs 8 MB. Counting ON devices over all homes: 3,998,064 ON devices found by both; loop iterations 3,998,064 (one per ON bit) vs 8,000,000 (one per element).

---

## Q4 – else–if ladder or switch? (K4)  `Task04/`

TODO 1 output: `100:S 95:S 83:A 50:D 49:F -5:?` ✔ (matches expected).

| marks | ladder | switch | table | switch **without** range check | ladder comparisons |
|---|---|---|---|---|---|
| 100 | S | S | S | S | 3 |
| 90 | S | S | S | S | 3 |
| 89 | A | A | A | A | 4 |
| 0 | F | F | F | F | 7 |
| −1 | ? | ? | ? | **F** ✘ (−1/10 = 0) | 2 |
| 101 | ? | ? | ? | **S** ✘ (101/10 = 10) | 2 |

* **Missing `break`/`return`:** removing the break after `case 8` makes `83` return `B` (falls into `case 7`); all of 80–89 are wrong (10 values).
* **Why `switch` cannot test 75–84:** case labels are single integer constants, not ranges; 75–84 straddles the `marks/10` buckets 7 and 8. The `/10` trick works only because the boundaries are multiples of 10.
* **Easier to change:** the table (edit data) or ladder (edit constants); the switch breaks when boundaries stop being multiples of 10.
* **Boundary-exposing test set:** `−1, 0, 1, 49, 50, 51, 59, 60, 61, 69, 70, 71, 79, 80, 81, 89, 90, 91, 99, 100, 101` – each boundary and both neighbours plus both ends. It exposes the missing range check (−1, 101) and the missing break (80, 81, 89). Exhaustive check −20..120: ladder = switch = table for all 141; the no-check switch is wrong for 40; the missing-break switch is wrong for 10.

### Design decision – scholarship rule
Chosen: **2-D lookup table** `waiver[grade][income band]` (S: 100/75/50 %, A: 50/25/0, B: 25/0/0, others 0). Nested `if` grows as grades × bands and hides the rule in control flow; a switch inside an if is verbose. A table is data, easy to audit and change, and O(1).

### Alternative – lookup table `grades[11]`
Time O(1) per grade (one division and one index) vs up to k comparisons in the ladder (observed 2–7 including validation) – the switch is also O(1) (jump table or a few compares). Space: 11 bytes. Switch/table need the validation done separately.

---

## Q5 – Count the work done by a loop (K4)  `Task05/`

### Student-derived condition
If `n = a·b` with `a ≤ b`, then `a·a ≤ a·b = n`, so the smaller divisor is ≤ √n. Therefore loop only while `i*i <= n` (no `sqrt()`), stop with `return 0` the moment `n % i == 0`, and count one division per iteration.

### Division counts (all loop versions give the same answers)

| n | result | for 2..n−1 | for `i*i<=n` | while | do-while (guarded) |
|---|---|---|---|---|---|
| 97 | prime | 95 | 8 | 8 | 8 |
| 100 | not prime | 1 | 1 | 1 | 1 |
| 7919 | prime | 7917 | 87 | 87 | 87 |
| 999983 | prime | 999981 | 998 | 998 | 998 |
| 1000001 | not prime (101×9901) | 100 | 100 | 100 | 100 |
| 1000003 | prime | 1000001 | **999** | 999 | 999 |

TODO 1 output matches expected: `97: 8`, `100: 1`, `7919: 87`, `1000003: 999`. With `i < n`: 95, 1, 7917, 1000001.

### Inquiry
* **do-while, n = 2 and 3:** the body runs once *before* the test, so for n = 2 it computes `2 % 2 == 0` and wrongly reports "not prime"; for n = 3 it does one division although 2·2 > 3. Fix: handle `n < 4` before the loop.
* **Overflow:** with 32-bit `unsigned`, `i*i` wraps at i = 65536 (computed 0, 65537 → 131073), so `i*i <= n` stays true and the loop would not stop; with 64-bit it wraps at i = 2³². Use `i <= n / i`.

### Alternative – Sieve of Eratosthenes, N = 1,000,003
| Method | Work |
|---|---|
| Trial division (√n), every n ≤ N | 67,741,504 divisions (78,499 primes found) |
| Sieve, once | 2,122,051 marking operations, 78,499 primes, **1,000,004 bytes** |
| Per later query | trial: up to 999 divisions, O(√n); sieve: 1 lookup, O(1) |

Complexity: sieve O(N log log N) time once + O(N) space, then O(1) per query; trial division O(√n) per query with O(1) space. For only a few tickets, trial division is cheaper.

---

## Q6 – Loops that must terminate: loan schedule (K5)  `Task06/`

### Loop design
**`while`**: the number of months is unknown in advance and a zero loan needs zero iterations. Termination: `balance > 0.005` (half a paisa) – **not** `balance != 0`, because floating point rarely hits exactly 0: `1.0 − 0.1` ten times leaves `1.3877787807814457e-16`, so `while (bal != 0)` keeps running (observed: runs past 10 steps to −0.2). Last month: `pay = (balance < E) ? balance : E`. If repayment ≤ interest the balance never falls – refuse up front.

### Hand calculation vs program (Rs 10,000, 2 %/month, Rs 2,000)
| Month | Interest | Closing balance |
|---|---|---|
| 1 | 200.00 | 8200.00 |
| 2 | 164.00 | 6364.00 |
| 3 | 127.28 | 4491.28 |
| 4 | 89.83 | 2581.11 |
| 5 | 51.62 | 632.73 |
| 6 | 12.65 | 0.00 (final payment 645.38) |

6 months, total interest **Rs 645.38**, total paid Rs 10,645.38 – the program matches the hand table on all rows.

### Growth investigation (`q6_months_chart.png`)
Predicted `n = ⌈−ln(1 − rP/E)/ln(1+r)⌉` vs measured months: E=5000 → 3/3; 2000 → 6/6; 1000 → 12/12; 500 → 26/26; 300 → 56/56; 250 → 82/82; 210 → 154/154; 205 → 188/188; 201 → 268/268; 200.5 → 303/303; 200.01 → 501/501; E = 200 or less → never. Months grow without bound as E → r·P = Rs 200.

### Deployment decision
Safety limit of **360 months** via `break`. Repayment ≤ Rs 200 → refused immediately ("repayment must exceed the first month's interest"). Repayment 200.001 → stops at 360 months with Rs 9,937.67 still owed and the message "increase EMI / extend tenure – manual review". Rationale: a loan system must never hang, and the borrower/officer gets an actionable message.

### Alternative – closed formula
Time O(1) vs O(n) iterations; space O(1) both. Precision: the formula is sensitive when `rP/E` ≈ 1 (the `log(1−x)` loses digits) and gives a fractional month count needing `ceil`; the loop accumulates rounding error each month but handles the short last payment and prints the schedule. The two agreed in every repayable case above.

---

## Q7 – Day-4 Design Challenge: Diagnose, Redesign, Validate (K5)  `Task07/`

**Program chosen:** the Q5 prime test (trial division by √n).

### A. Diagnose the bottleneck (2)
Evidence (Q5): 97 → 8, 7919 → 87, 1000003 → **999** divisions; all `n % i`. Almost all work is the single `n % i` inside the loop; the count grows as √n; and ~2/3 of the work is repeated/unnecessary: every even `i > 2` and every multiple of 3 is tried although `n % 2` and `n % 3` already settled those cases. Over every ticket n ≤ 1,000,003 the original does 67,741,504 divisions.

### B. Design objective (2)
*(1)* For a large prime such as 1,000,003, **at most 35 % of the original divisions (≤ 350)**; *(2)* no extra memory; *(3)* identical answers for every n ≤ 1,000,003.

### C. Redesign (4)
Property exploited: every prime > 3 is of the form 6k − 1 or 6k + 1 (any other residue mod 6 is divisible by 2 or 3). So test 2 and 3 once, then divisors 5, 7, 11, 13, 17, 19, … (`i`, `i+2`, `i += 6`) while `i*i <= n`.
```
if n < 2: return 0;  if n < 4: return 1
if n % 2 == 0 or n % 3 == 0: return 0
for i = 5; i*i <= n; i += 6:
    if n % i == 0 or n % (i+2) == 0: return 0
return 1
```
Extra memory: none. New trade-off: two fixed divisions up front and slightly more code; the redesign is worse for tiny primes 5 and 7 (2 divisions vs 1). `i*i` overflow still applies (unchanged from the original).

### D. Prediction (1) – written in `q7_redesign.c` before the first run
97: 8 → 4; 7919: 87 → 30; 999983: 998 → 334; 1000003: 999 → 334 (ratio ≈ 0.334); 1000001: 100 → 35; 100: 1 → 1; 5, 7: 1 → 2. Batch over n ≤ 1,000,003: about **0.37–0.42 of the original (25–28 M divisions)**.

### E. Implement and validate (2)
| n | original | redesign | predicted | ratio |
|---|---|---|---|---|
| 5 | 1 | 2 | 2 | 2.000 |
| 7 | 1 | 2 | 2 | 2.000 |
| 25 | 4 | 3 | 3 | 0.750 |
| 97 | 8 | 4 | 4 | 0.500 |
| 100 | 1 | 1 | 1 | 1.000 |
| 7919 | 87 | 30 | 30 | 0.345 |
| 999983 | 998 | 334 | 334 | 0.335 |
| 1000001 | 100 | 35 | 35 | 0.350 |
| 1000003 | 999 | **334** | 334 | 0.334 |

All n ≤ 1,000,003: original **67,741,504**, redesign **23,739,568** divisions (ratio 0.350, 65 % fewer); answers that differ: **0** (78,499 primes in both). Redesign is cheaper for 333,328 values, equal for 666,674, and more expensive for only 2 (n = 5, 7). CPU time in one run: 0.238 s vs 0.088 s (varies per run).

### F. Defend the final design (2)
*Objective achieved:* 334 ≤ 350 for the large prime (0.334 ≤ 0.35), no extra memory, 0 mismatches. *Prediction check:* all single-input predictions were exact; the batch prediction (0.37–0.42) was too cautious – the measured 0.350 is better, because composites with no factor of 2 or 3 also gain (e.g. 1000001: 100 → 35). *Costs:* extra code complexity and +1 division for the tiny primes 5 and 7. *Where the original is still preferable:* very small n, code where clarity matters more than the ~3× constant factor. *Larger picture:* the redesign remains O(√n) per query – only the constant drops to one third. If the organisers must test *many* tickets, the sieve from Q5 (2,122,051 operations, 1 MB) is better than either, at the cost of memory; for a few queries the 6k ± 1 test is the better trade.

---

# Additional experiments (one extra program per task)

## Q1 extra – `Task01/q1_more_precedence.c`
* **Precedence quiz:** 15 expressions predicted by hand before running – 15/15 correct (`2 + 3 * 4 = 14`, `1 + 2 << 3 = 24`, `5 & 3 == 3` = 1 because `==` binds tighter than `&`, `3 > 2 > 1` = 0, nested `?:` groups right-to-left). gcc `-Wparentheses` warns about the unbracketed ones (4 warnings, intentional).
* **10-bill audit** (buggy expression vs integer-paise billing): wrong on **8 of 10** bills; the two exact matches (bills 1 and 6) are non-senior bills whose GST has no fractional part. Examples: bill 7 (senior, Rs 1500) buggy 1300 vs correct 1288.75 (+11.25); bill 3 buggy 330 vs 330.75 (−0.75 truncation). Net error over the 10 bills: +Rs 46.95. Lesson: the bug is systematic, not rare.

## Q2 extra – `Task02/q2_three_conditions.c`
Three conditions joined by `||`: A cost 1, P 0.30; B cost 10, P 0.10; C (slow) cost 100, P 0.05; 20,000 passengers, all six orders.

| Order | Cost per passenger |
|---|---|
| A,B,C | **70.98** (predicted 71.00 = 1 + 0.7·10 + 0.63·100) |
| A,C,B | 77.75 |
| B,A,C | 73.87 |
| B,C,A | 100.80 |
| C,A,B | 107.61 |
| C,B,A | 110.36 (1.6× the best) |

Order by ascending cost / P(true) (3.3, 100, 2000 → A, B, C). Every order grants the same 8037 passengers: for side-effect-free conditions, reordering changes cost, never the answer.

## Q3 extra – `Task03/q3_stress_test.c`
Verified the four bit functions and the popcount against an array model: every register 0–255 × every device 0–7 × four operations = **8,192 checks, 0 failures** (and other bits untouched); sum of popcounts over 0–255 = 1024 as predicted (8 × 128); **1,000,000 random operations, 0 mismatches**; a predicted sequence involving bit 7 (`10000000 → 10000001 → 00000001 → 00010001 → 00010000 → 10011000`) matched exactly with `unsigned char`.

## Q4 extra – `Task04/q4_scholarship_full.c`
Twelve students (marks, income): grade, income band, waiver. Marks 101 and −3 are rejected. Nested `if`, `switch`-inside-`if` and the 2-D table produce identical results for all 101 × 3 = 303 (marks, band) cases. Income boundaries are a design decision that must be tested: 249,999 → band 0, 250,000 → band 1, 500,000 → band 1, 500,001 → band 2 (upper edge inclusive in band 1).

## Q5 extra – `Task05/q5_loops_extra.c`
* **break:** first prime ≥ 1,000,000 = 1000003 (predicted), found after 4 candidates and 1,101 divisions.
* **continue:** prime counts 25 / 168 / 1229 for ≤ 100 / 1000 / 10000 (as predicted), same with and without skipping evens. **My prediction that skipping evens would roughly halve the divisions was wrong**: the divisions fell only to 79 %, 91 %, 96 %, because `is_prime` already rejects an even number after one division, so `continue` saves just one division per even number.
* **goto:** leaves both nested loops at once: 1000001 = 101 × 9901 after 4,192,191 inner iterations.
* **do-while:** digit sum/reversal of 987654 = 39 / 456789 as predicted; input 0 correctly counts 1 digit (a `while (v > 0)` loop would count 0).

## Q6 extra – `Task06/q6_more_loans.c`
| Loan | P, rate, repay | Hand estimate | Double sim | Paise sim | Total interest (double / paise) |
|---|---|---|---|---|---|
| S1 | 50,000, 1.5 %, 3,000 | 20 | 20 | 20 | 7971.75 / 7971.72 |
| S2 | 5,000, 3 %, 500 | 13 | 13 | 13 | 1033.77 / 1033.77 |
| S3 | 20,000, 1 %, 1,000 | 23 | 23 | 23 | 2426.96 / 2426.96 |
| S4 | 100,000, 1 %, 1,000 | never | limit hit | limit hit | repayment = month-1 interest |
| S5 | 100,000, 1 %, 1,100 | 241 | 241 | 241 | 165,085.21 / 165,085.28 |

Integer paise (rate in basis points, interest rounded half-up each month) agrees with the double version on months and differs by at most 7 paise in total interest – money should be kept in integers. With a loan of 0, `while` reports 0 months but `do-while` reports a phantom installment, so `while` is correct. If the last payment were a full EMI instead of "pay only the balance", Rs 10,000 at 2 % ends at month 6 with Rs 1,354.62 **overpaid**.

## Q7 extra – `Task07/q7_scaling.c`
Smallest prime ≥ 10^k, k = 1…12 (original / 6k±1 / wheel-30 divisions): 10^3 → 30 / 12 / 11; 10^6 → 999 / 334 / 268; 10^9 → 31,621 / 10,542 / 8,435; 10^12 → 999,999 / 333,334 / 266,668. Ratios settle at **0.333** (6k±1) and **0.267** (wheel-30), as predicted (2/6 and 8/30); the wheel-30 estimate of ~269 for 1,000,003 was 268. Both are worse for tiny n (11: 2 vs 2 vs 3). Validation on all n ≤ 2,000,000: 148,933 primes, 0 mismatches; total divisions 179,492,732 → 62,149,072 (0.346) → 50,726,788 (0.283). Conclusion for the Day-4 defence: the redesigns lower the constant but the work still grows as √n (10^12 needs ~3×10^5 divisions even after redesign); wheel-30 gives ~20 % fewer divisions than 6k±1 at the cost of a step table, so the simpler 6k±1 remains the recommended final design.

---

## Evidence checklist
Predictions before execution ✔ (Q1, Q3, Q6, Q7) · operator-by-operator explanation ✔ · observed outputs ✔ (`output_*.png`) · call/division/iteration counts ✔ · tables/graphs ✔ (`*_chart.png`) · complete-the-code TODOs run ✔ · alternative-concept complexity analysis ✔ · design decisions defended ✔.
