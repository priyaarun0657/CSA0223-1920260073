# BUILD_RESULTS

Course: CSA02 C Programming | Assignment 2 (CO2)

Compiler: `gcc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0` on Linux x86_64

Every program was compiled with `-Wall -Wextra` and executed. Output below is the raw output of that run
(timing lines such as `CPU time` differ from run to run; all operation counts are deterministic).

## Task01/q1_precedence.c

- compile: `gcc -Wall -Wextra -o q1 q1_precedence.c`
- compiler warnings: 1 (intentional - see report)
- exit status: 0

```text
Bill   price qty sen | BUGGY total/net (pred)   | BUGGY total/net (observed)  | INTENDED total / net
A        120  10   1 | pred 1080 / 1030          | obs 1080 / 1030 [MATCH]      |  1071.00 /  1021.00
       gross=1200.00 discount=180.00 taxable=1020.00 gst=51.00 | error of buggy total = +9.00
B         45   7   0 | pred  330 / 330           | obs  330 / 330  [MATCH]      |   330.75 /   330.75
       gross=315.00 discount=0.00 taxable=315.00 gst=15.75 | error of buggy total = -0.75
C        333   3   1 | pred  899 / 899           | obs  899 / 899  [MATCH]      |   891.61 /   891.61
       gross=999.00 discount=149.85 taxable=849.15 gst=42.46 | error of buggy total = +7.39

count = 5; count = count++ + 1;  ->  count = 6   (UB: any value is allowed;
this compiler happens to give 6, a different compiler could give 7 or crash)
```

compiler diagnostics:

```text
q1_precedence.c: In function ‘main’:
q1_precedence.c:62:11: warning: operation on ‘count’ may be undefined [-Wsequence-point]
   62 |     count = count++ + 1;      /* modifies 'count' twice without a sequence point */
      |     ~~~~~~^~~~~~~~~~~~~
```

## Task02/q2_shortcircuit.c

- compile: `gcc -Wall -Wextra -o q2 q2_shortcircuit.c`
- compiler warnings: 0
- exit status: 0

```text
=== Experiment 1: is the second operand evaluated? ===
  0 && f():
    A evaluated -> 0
    result=0 (B skipped)
  1 && f():
    A evaluated -> 1
    B evaluated -> 1
    result=1 (B evaluated)
  1 || f():
    A evaluated -> 1
    result=1 (B skipped)
  0 || f():
    A evaluated -> 0
    B evaluated -> 0
    result=0 (B evaluated)
  0 & f()  (bitwise, NO short-circuit):
    A evaluated -> 0
    B evaluated -> 1
    result=0 (B evaluated even though A is 0)
  Value difference on non-boolean operands: 1 && 2 = 1 , 1 & 2 = 0

=== Experiment 2: slow-function calls for 1000 passengers ===
  population: 20% senior, 50% eligible class, 10% card holders
  V1 (senior&&elig)||verify : calls= 887  granted=185
  V2 verify||(senior&&elig) : calls=1000  granted=185
  V3 nested if (V1 order)   : calls= 887  granted=185
  V4 (senior&elig)|verify    : calls=1000  granted=185

=== Experiment 3: effect of how often the cheap test is true ===
  %senior %elig | P(cheap true) | calls V1 | calls V2 | saved by order
       5    50 |         2.50% |      964 |     1000 | 36
      20    50 |        10.00% |      887 |     1000 | 113
      50    50 |        25.00% |      738 |     1000 | 262
      90    90 |        81.00% |      189 |     1000 | 811

=== Changed condition: verify_card() now writes an audit log ===
  V1 audit-log entries = 887 of 1000 passengers (short-circuit skips the rest)
  V2 audit-log entries = 1000 of 1000 passengers (every passenger logged)
  V4 audit-log entries = 1000 of 1000 passengers (every passenger logged)
```

## Task03/q3_register.c

- compile: `gcc -Wall -Wextra -o q3 q3_register.c`
- compiler warnings: 0
- exit status: 0

```text
00000101
00000110
AC is ON, PUMP is OFF
```

## Task03/q3_inquiry.c

- compile: `gcc -Wall -Wextra -O0 -o q3i q3_inquiry.c`
- compiler warnings: 1 (intentional - see report)
- exit status: 0

```text
=== Counting devices ON (bitwise only: reg &= reg - 1) ===
  register 00000110 (value 6) -> 2 devices ON ; register 11111111 -> 8 ; register 0 -> 0

=== Inquiry 1: reg & 1 << dev   vs   (reg & 1) << dev ===
Precedence: << binds tighter than &, so  reg & 1 << dev  ==  reg & (1 << dev)
reg=6 (00000110), dev=2
  reg & 1 << dev     = 4   (mask test: bit 2 of reg -> value 4 = ON, but not 1!)
  (reg & 1) << dev   = 0   (tests bit 0 (LIGHT) then shifts it -> WRONG device)
  (reg >> dev) & 1   = 1   (correct, returns exactly 0 or 1)

=== Inquiry 2: signed char with bit 7 set ===
  signed char  sc = 0x80 -> value -128 ; sc promoted to int = 0xFFFFFF80
  unsigned char uc = 0x80 -> value 128 ; uc promoted to int = 0x00000080
  sc >> 1 = -64  (sign extension: arithmetic shift, implementation-defined)
  uc >> 1 = 64  (logical: 01000000)
  (sc >> 7) & 1 = 1, but sc >> 7 = -1 (all ones) if the '& 1' is forgotten
  sc == 0x80 ? false   uc == 0x80 ? true   (-128 != 128 after promotion)

=== Alternative: char state[8] (1 byte/device) vs 1 byte register ===
  memory for 1000000 homes : bit-register = 1000000 bytes (1.0 MB), array = 8000000 bytes (8.0 MB)
  count devices ON (all homes): bit-register = 3998064 ON, 3998064 loop iterations, 0.0143 s
                                array        = 3998064 ON, 8000000 loop iterations, 0.0204 s
  single set/clear/toggle/test: O(1) in both; counting ON devices: O(k) (k=ON bits <= 8) vs O(8)
```

compiler diagnostics:

```text
q3_inquiry.c: In function ‘main’:
q3_inquiry.c:42:15: warning: comparison is always false due to limited range of data type [-Wtype-limits]
   42 |            sc == 0x80 ? "true" : "false", uc == 0x80 ? "true" : "false");
      |               ^~
```

## Task04/q4_grade.c

- compile: `gcc -Wall -Wextra -o q4 q4_grade.c`
- compiler warnings: 0
- exit status: 0

```text
100:S 95:S 83:A 50:D 49:F -5:?
```

## Task04/q4_compare.c

- compile: `gcc -Wall -Wextra -o q4c q4_compare.c`
- compiler warnings: 1 (intentional - see report)
- exit status: 0

```text
=== Required test values ===
marks | ladder switch table | switch(no range check) | comparisons in ladder
  100 |   S      S      S   |           S            | 3
   90 |   S      S      S   |           S            | 3
   89 |   A      A      A   |           A            | 4
    0 |   F      F      F   |           F            | 7
   -1 |   ?      ?      ?   |           F            | 2
  101 |   ?      ?      ?   |           S            | 2

=== Boundary-exposing test set (every grade edge +-1, both ends) ===
marks:   -1   0   1  49  50  51  59  60  61  69  70  71  79  80  81  89  90  91  99 100 101
ladder:   ?   F   F   F   D   D   D   C   C   C   B   B   B   A   A   A   S   S   S   S   ?
switch:   ?   F   F   F   D   D   D   C   C   C   B   B   B   A   A   A   S   S   S   S   ?
table :   ?   F   F   F   D   D   D   C   C   C   B   B   B   A   A   A   S   S   S   S   ?
nochk :   F   F   F   F   D   D   D   C   C   C   B   B   B   A   A   A   S   S   S   S   S
nobrk :   ?   F   F   F   D   D   D   C   C   C   B   B   B   B   B   B   S   S   S   S   ?

=== Exhaustive check: marks -20..120 (141 values), ladder is the reference ===
  switch mismatches: 0 | table mismatches: 0
  no-range-check switch mismatches: 40 of 141 (the values -20..-1 and 101..120)
  missing-break switch mismatches: 10 (marks 80..89 return 'B', first at 80)

=== Missing-break demo (the TODO program with 'case 8' break removed) ===
  expected      : 100:S 95:S 83:A 50:D 49:F -5:?
  without break : 100:S 95:S 83:B 50:D 49:F -5:? 
  -> 83 is now 'B' (A falls through into case 7)

=== Scholarship (grade x income band) via 2-D lookup table: % fee waiver ===
  grade | <2.5L  2.5-5L  >5L
    S   |  100%     75%    50%
    A   |   50%     25%     0%
    B   |   25%      0%     0%
    C   |    0%      0%     0%
    D   |    0%      0%     0%
    F   |    0%      0%     0%
  e.g. marks 83, income band 1 -> grade A -> 25% waiver
```

compiler diagnostics:

```text
q4_compare.c: In function ‘grade_switch_nobreak’:
q4_compare.c:63:19: warning: this statement may fall through [-Wimplicit-fallthrough=]
   63 |         case 8: g = 'A';                  /* <-- break removed: falls into case 7 */
      |                 ~~^~~~~
q4_compare.c:64:9: note: here
   64 |         case 7: g = 'B'; break;
      |         ^~~~
```

## Task05/q5_is_prime.c

- compile: `gcc -Wall -Wextra -o q5 q5_is_prime.c`
- compiler warnings: 0
- exit status: 0

```text
      97 prime     divisions = 8
     100 not prime divisions = 1
    7919 prime     divisions = 87
 1000003 prime     divisions = 999
```

## Task05/q5_variants.c

- compile: `gcc -Wall -Wextra -O0 -o q5v q5_variants.c`
- compiler warnings: 0
- exit status: 0

```text
=== Division counts (checks) for each version ===
        n result    | for 2..n-1  for i*i    while  do-while do-w (bad)
        2 prime     |          0        0        0         0          1
            ^ unguarded do-while says not prime for 2 : WRONG
        3 prime     |          1        0        0         0          1
       97 prime     |         95        8        8         8          8
      100 not prime |          1        1        1         1          1
     7919 prime     |       7917       87       87        87         87
  1000003 prime     |    1000001      999      999       999        999
   999983 prime     |     999981      998      998       998        998
  1000001 not prime |        100      100      100       100        100

=== Why do-while needs care for n = 2 and n = 3 ===
  n=2 unguarded: tests 2 % 2 == 0 first -> result NOT prime (WRONG, 2 is prime), checks=1
  n=3 unguarded: result prime but performs 1 useless division(s) although 2*2 > 3

=== Why i * i <= n can overflow ===
  32-bit: i=65535  i*i computed = 4294836225  (true 4294836225)  loop test computed=1 correct=1
  32-bit: i=65536  i*i computed = 0  (true 4294967296)  loop test computed=1 correct=0   <-- WRONG: loop would not stop
  32-bit: i=65537  i*i computed = 131073  (true 4295098369)  loop test computed=1 correct=0   <-- WRONG: loop would not stop
  64-bit: i=2^32 -> i*i = 0 (wraps to 0) so i*i <= n is true again for any n
  safe form: while (i <= n / i)   (no multiplication, cannot overflow)

=== Changing the condition to i < n (naive) -- tickets from the TODO program ===
      97 prime     divisions = 95
     100 not prime divisions = 1
    7919 prime     divisions = 7917
 1000003 prime     divisions = 1000001

=== Alternative: Sieve of Eratosthenes up to N = 1,000,003 ===
  trial division (i*i<=n), all n <= N : 67741504 divisions, primes found = 78499
  naive 2..n-1 for all n <= 20000 only: 21267570 divisions
  sieve, one pass                      : 2122051 marking operations, primes found = 78499, extra memory = 1000004 bytes
  per query afterwards: sieve = 1 array lookup, trial = up to 999 divisions
```

## Task06/q6_loan.c

- compile: `gcc -Wall -Wextra -o q6 q6_loan.c -lm`
- compiler warnings: 0
- exit status: 0

```text
=== Correctness check: Rs 10000 @ 2%/month, repay Rs 2000 ===
month   interest      bal+int       paid    closing
    1     200.00     10200.00    2000.00    8200.00
    2     164.00      8364.00    2000.00    6364.00
    3     127.28      6491.28    2000.00    4491.28
    4      89.83      4581.11    2000.00    2581.11
    5      51.62      2632.73    2000.00     632.73
    6      12.65       645.38     645.38       0.00
months = 6, total interest = 645.38, total paid = 10645.38
hand-calculated schedule vs program (6 rows, tolerance 0.006): ALL MATCH; hand total interest 645.38 vs 645.38

=== Why balance != 0 is dangerous (floating point) ===
1.0 minus 0.1 repeated: after exactly 10 subtractions balance = 1.3877787807814457e-16 (not 0)
so 'while (bal != 0)' keeps going: 12 iterations ran (stopped only by the k<12 guard), bal = -0.2

=== Growth investigation: months vs repayment (P=10000, r=2%, monthly interest at start = 200) ===
  repay E | predicted n=ceil(-ln(1-rP/E)/ln(1+r)) | measured months | total interest
  5000.00 |     2.06 -> 3                        | 3               |     310.08
  2000.00 |     5.32 -> 6                        | 6               |     645.38
  1000.00 |    11.27 -> 12                       | 12              |    1270.33
   500.00 |    25.80 -> 26                       | 26              |    2898.73
   300.00 |    55.48 -> 56                       | 56              |    6644.17
   250.00 |    81.27 -> 82                       | 82              |   10318.98
   210.00 |   153.74 -> 154                      | 154             |   22286.50
   205.00 |   187.53 -> 188                      | 188             |   28444.00
   201.00 |   267.81 -> 268                      | 268             |   43829.75
   200.50 |   302.69 -> 303                      | 303             |   50688.80
   200.01 |   500.11 -> 501                      | 501             |   90027.66
   200.00 | never (rP/E >= 1)                     | limit 5000 hit  | grows without bound
   190.00 | never (rP/E >= 1)                     | limit 5000 hit  | grows without bound

=== Deployment decision: safety limit of 360 months via break ===
  repay 2000.000 : repaid in 6 months, interest Rs 645.38
  repay 190.000 : REFUSED - repayment must exceed the first month's interest Rs 200.00
  repay 200.001 : STOPPED at 360 months, Rs 9937.67 still owed - show 'increase EMI / extend tenure, manual review'
```

## Task07/q7_redesign.c

- compile: `gcc -Wall -Wextra -o q7 q7_redesign.c`
- compiler warnings: 0
- exit status: 0

```text
=== A. Diagnosis (original program, evidence from Q5) ===
  large prime 1000003: 999 divisions, every one of them 'n % i' with i = 2..1000
  - the count grows as sqrt(n)  (97 -> 8, 7919 -> 87, 1000003 -> 999)
  - repeated work: every even i > 2 is tried although n % 2 already proved n odd;
    every multiple of 3 is tried although n % 3 was already tested
    => about 2/3 of the divisions can never find a divisor

=== E. Same inputs, same counts: Original -> Redesigned ===
        n result    |  original  redesign predicted | ratio
        5 prime     |         1         2         2 | 2.000
        7 prime     |         1         2         2 | 2.000
       25 not prime |         4         3         3 | 0.750
       97 prime     |         8         4         4 | 0.500
      100 not prime |         1         1         1 | 1.000
     7919 prime     |        87        30        30 | 0.345
   999983 prime     |       998       334       334 | 0.335
  1000001 not prime |       100        35        35 | 0.350
  1000003 prime     |       999       334       334 | 0.334

=== E. Batch validation: every n in 0 .. 1,000,003 ===
  answers that differ between the two programs : 0  (primes found: 78499)
  total divisions  original = 67741504 , redesign = 23739568 , ratio = 0.350 (65.0% fewer)
  CPU time (this run, varies)  original = 0.235 s , redesign = 0.080 s
  per-n comparison: redesign cheaper for 333328 values, equal for 666674, MORE expensive for 2

=== F. Where the original is still preferable (small n) ===
  n <= 100 : redesign needs MORE divisions for 2 values;  n <= 1000 : 2 values
  first such n: 5 7 (small primes: the two fixed tests 2 and 3 cost more than the loop saves)
```

## Task01/q1_more_precedence.c

- compile: `gcc -Wall -Wextra -o q1b q1_more_precedence.c`
- compiler warnings: 4 (intentional - see report)
- exit status: 0

```text
=== A. Precedence / associativity predictions vs observed ===
  2 + 3 * 4                  predicted  14  observed  14  OK
  10 - 4 - 3                 predicted   3  observed   3  OK
  100 / 10 * 5               predicted  50  observed  50  OK
  100 / (10 * 5)             predicted   2  observed   2  OK
  7 % 4 * 2                  predicted   6  observed   6  OK
  1 + 2 << 3                 predicted  24  observed  24  OK
  5 & 3 == 3                 predicted   1  observed   1  OK
  (5 & 3) == 3               predicted   0  observed   0  OK
  !0 && 0 || 1               predicted   1  observed   1  OK
  3 > 2 > 1                  predicted   0  observed   0  OK
  -2 * -3                    predicted   6  observed   6  OK
  ~0 & 0xF                   predicted  15  observed  15  OK
  1 ? 2 : 3 ? 4 : 5          predicted   2  observed   2  OK
  0 ? 2 : 0 ? 4 : 5          predicted   5  observed   5  OK
  a = b = c  (all were 4)    predicted   4  observed   4  OK
  15 of 15 predictions correct

=== B. Ten-bill audit: buggy expression vs integer-paise correct billing ===
  #  price qty sen | buggy net | correct net (Rs) | diff (Rs)
  1     12   5   0 |        63 |         63.00 |      +0.00
  2    250   4   1 |       900 |        892.50 |      +7.50
  3     45   7   0 |       330 |        330.75 |      +0.75
  4    333   3   1 |       899 |        891.61 |      +7.39
  5     99  10   1 |       891 |        883.58 |      +7.42
  6    480   2   0 |       958 |        958.00 |      +0.00
  7   1500   1   1 |      1300 |       1288.75 |     +11.25
  8     75  13   0 |       973 |        973.75 |      +0.75
  9     20  50   1 |       900 |        892.50 |      +7.50
 10    999   1   1 |       899 |        891.61 |      +7.39
  buggy bills that differ from the correct amount: 8 of 10 (net error over 10 bills = +46.95 Rs)
```

compiler diagnostics:

```text
q1_more_precedence.c: In function ‘main’:
q1_more_precedence.c:18:49: warning: suggest parentheses around ‘+’ inside ‘<<’ [-Wparentheses]
   18 |         {"1 + 2 << 3",               24,  1 + 2 << 3},
      |                                                 ^~
q1_more_precedence.c:19:45: warning: suggest parentheses around comparison in operand of ‘&’ [-Wparentheses]
   19 |         {"5 & 3 == 3",                1,  5 & 3 == 3},
      |                                             ^
q1_more_precedence.c:21:51: warning: suggest parentheses around ‘&&’ within ‘||’ [-Wparentheses]
   21 |         {"!0 && 0 || 1",              1,  !0 && 0 || 1},
      |                                                   ^~
q1_more_precedence.c:22:49: warning: comparisons like ‘X<=Y<=Z’ do not have their mathematical meaning [-Wparentheses]
   22 |         {"3 > 2 > 1",                 0,  3 > 2 > 1},
      |                                                 ^
```

## Task02/q2_three_conditions.c

- compile: `gcc -Wall -Wextra -o q2b q2_three_conditions.c`
- compiler warnings: 0
- exit status: 0

```text
order | calls A      calls B      calls C   | total cost  | cost/passenger | granted
 A,B,C |    20000        14018        12595 |     1419680 |          70.98 | 8037
 A,C,B |    20000        13318        14018 |     1554980 |          77.75 | 8037
 B,A,C |    17989        20000        12595 |     1477489 |          73.87 | 8037
 B,C,A |    17094        20000        17989 |     2015994 |         100.80 | 8037
 C,A,B |    19004        13318        20000 |     2152184 |         107.61 | 8037
 C,B,A |    17094        19004        20000 |     2207134 |         110.36 | 8037
best order  : A,B,C (cost/passenger 70.98; prediction 71.00 for A,B,C)
worst order : C,B,A (cost/passenger 110.36) -> 1.6x the best
granted is identical for every order: reordering a side-effect-free || never changes the answer, only the cost.
```

## Task03/q3_stress_test.c

- compile: `gcc -Wall -Wextra -o q3s q3_stress_test.c`
- compiler warnings: 0
- exit status: 0

```text
=== (a) Exhaustive: every register 0..255, every device 0..7 ===
  8192 checks, 0 failures; sum of popcounts over 0..255 = 1024 (predicted 1024)

=== (b) 1,000,000 random operations: register vs 8-element array ===
  mismatches after 1,000,000 operations: 0 ; final register = 00111100

=== (c) Longer predicted sequence incl. device 7 (bit 7, unsigned char) ===
  on(7)        predicted 10000000 observed 10000000
  on(0)        predicted 10000001 observed 10000001
  toggle(7)    predicted 00000001 observed 00000001
  toggle(4)    predicted 00010001 observed 00010001
  off(0)       predicted 00010000 observed 00010000
  on(7), on(3) predicted 10011000 observed 10011000
```

## Task04/q4_scholarship_full.c

- compile: `gcc -Wall -Wextra -o q4s q4_scholarship_full.c`
- compiler warnings: 0
- exit status: 0

```text
name    marks   income  grade band  waiver%  (nested/switch/table)
Asha       96   180000    S     0    100%     100/100/100
Bala       91   320000    S     1     75%     75/75/75
Chitra     89   150000    A     0     50%     50/50/50
Dev        83   620000    A     2      0%     0/0/0
Eswar      78   240000    B     0     25%     25/25/25
Farah      65    90000    C     0      0%     0/0/0
Gopal      50   480000    D     1      0%     0/0/0
Hari       49   100000    F     0      0%     0/0/0
Indu      100   500000    S     1     75%     75/75/75
Jai       101   200000   REJECTED (marks outside 0..100)
Kavi       -3   300000   REJECTED (marks outside 0..100)
Lata       90   250000    S     1     75%     75/75/75

exhaustive: 303 (marks, band) cases, 0 differences between the three structures
income boundary check (band 0 | 1 | 2 edges): 
  income       0 -> band 0
  income  249999 -> band 0
  income  250000 -> band 1
  income  500000 -> band 1
  income  500001 -> band 2
```

## Task05/q5_loops_extra.c

- compile: `gcc -Wall -Wextra -o q5x q5_loops_extra.c`
- compiler warnings: 0
- exit status: 0

```text
=== 1. break: first prime >= 1,000,000 ===
  found 1000003 (predicted 1000003), tried 4 candidates, 1101 divisions

=== 2. continue: count primes, skipping even candidates ===
  primes <=   100 :   25 (predicted 25), with continue   25 | divisions    236 ->    187 (79%)
  primes <=  1000 :  168 (predicted 168), with continue  168 | divisions   5288 ->   4789 (91%)
  primes <= 10000 : 1229 (predicted 1229), with continue 1229 | divisions 117527 -> 112528 (96%)
  note: my prediction (about 50%) was wrong. An even n already returns after one division (n % 2),
        so 'continue' only saves 1 division per even number; the saving shrinks as n grows (79% -> 96%).

=== 3. goto: leave two nested loops at once ===
  1000001 = 101 * 9901 (predicted 101 * 9901) after 4192191 inner iterations

=== 4. do-while: digit sum and reversal (body must run once, even for 0) ===
   987654 : digits=6  digit sum=39  reversed=456789
        0 : digits=1  digit sum=0  reversed=0
       70 : digits=2  digit sum=7  reversed=7
  (a while(v > 0) loop would report 0 digits for the input 0; do-while correctly reports 1)
```

## Task06/q6_more_loans.c

- compile: `gcc -Wall -Wextra -o q6b q6_more_loans.c -lm`
- compiler warnings: 0
- exit status: 0

```text
=== A. Scenarios: hand estimate vs double simulation vs integer-paise simulation ===
id    P        rate  repay  | hand | double months  total interest | paise months  total interest | paid-P-int
S1     50000  1.5%   3000 |   20 |       20          7971.75 |       20           7971.72 | -4.5e-12
S2      5000  3.0%    500 |   13 |       13          1033.77 |       13           1033.77 | +4.5e-13
S3     20000  1.0%   1000 |   23 |       23          2426.96 |       23           2426.96 | -3.2e-12
S4    100000  1.0%   1000 | never|  NO REPAYMENT (limit 2000 reached)   | NO REPAYMENT (limit 2000 reached)
S5    100000  1.0%   1100 |  241 |      241        165085.21 |      241         165085.28 | -2.9e-11

=== B. while vs do-while when the loan amount is 0 ===
  P = 0 : while reports 0 months (correct) ; do-while reports 1 month(s) (a phantom installment)
  => while (pre-test) is the right loop: a loan may already be fully repaid before the first month.

=== C. Last-payment rule: what if we always charge a full EMI? ===
  Rs 10000, 2%, EMI 2000 without the 'pay only the balance' rule: ends at month 6 with balance -1354.62 (overpaid Rs 1354.62)
```

## Task07/q7_scaling.c

- compile: `gcc -Wall -Wextra -o q7s q7_scaling.c`
- compiler warnings: 0
- exit status: 0

```text
=== Scaling: smallest prime >= 10^k ===
   k  prime n            original    6k+-1  wheel30 | ratio 6k+-1  ratio wheel30
   1  11                       2        2        3 |   1.000         1.500
   2  101                      9        4        4 |   0.444         0.444
   3  1009                    30       12       11 |   0.400         0.367
   4  10007                   99       34       28 |   0.343         0.283
   5  100003                 315      106       86 |   0.337         0.273
   6  1000003                999      334      268 |   0.334         0.268
   7  10000019              3161     1056      845 |   0.334         0.267
   8  100000007             9999     3334     2668 |   0.333         0.267
   9  1000000007           31621    10542     8435 |   0.333         0.267
  10  10000000019          99999    33334    26668 |   0.333         0.267
  11  100000000003        316226   105410    84329 |   0.333         0.267
  12  1000000000039       999999   333334   266668 |   0.333         0.267

=== Validation: all n <= 2,000,000 ===
  primes found: 148933 ; answer mismatches: 0
  total divisions: original 179492732 | 6k+-1 62149072 (0.346) | wheel30 50726788 (0.283)

  wheel30 uses about 20% fewer divisions than 6k+-1 (ratio 0.267 vs 0.333), a constant factor at every size,
  but needs a step table (8 ints) and 3 fixed tests. 6k+-1 is simpler and nearly as good.
  Both stay O(sqrt n): neither changes how the work GROWS, only the constant in front.
```
