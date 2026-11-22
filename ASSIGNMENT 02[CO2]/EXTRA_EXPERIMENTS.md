# Assignment 2 (CO2) — Supplementary Experiments

This document extends the original task explanations without replacing the original programs or outputs.

## Testing approach
Each supplementary program was compiled with GCC using `-Wall -Wextra -std=c11 -O2` and executed. Outputs are included next to the source as text files and terminal-style screenshots. The test sets focus on ordinary values, boundaries, invalid values, and special cases.

## Task 01 — Operators, precedence and billing

**Concepts:** precedence decides which operator is evaluated first; associativity resolves operators of the same precedence; integer division truncates; explicit parentheses improve clarity. The billing case demonstrates how a misplaced expression can apply GST before a discount and how integer arithmetic loses fractional rupees.

**Additional tests:** zero quantity, non-senior customer, discount-bearing customer, and multiple bill values. Compare the buggy expression with a corrected calculation using intermediate variables and `double`.

**Expected lesson:** write and verify each intermediate value (`gross`, `discount`, `taxable`, `GST`, `final`) instead of relying on a long expression.

### Supplementary output
```text
CASE | gross | discount | GST | final
   1 | 1200.00 |   180.00 |  51.00 | 1071.00
   2 | 315.00 |     0.00 |  15.75 |  330.75
   3 | 999.00 |   149.85 |  42.46 |  891.61
   4 | 999.00 |     0.00 |  49.95 | 1048.95
   5 | 1000.00 |   150.00 |  42.50 |  892.50

Test: quantity=0 produces zero; senior=0 produces no discount.

```

## Task 02 — Logical operators and short-circuit evaluation

**Concepts:** `&&` and `||` evaluate left-to-right and may skip the right operand. This can reduce expensive function calls, but it also changes whether side effects such as logging happen.

**Additional tests:** all four truth-value combinations. The extra program counts function calls to show that `0 && RHS` skips RHS and `1 || RHS` skips RHS.

**Experiment:** compare logical `&&`/`||` with bitwise `&`/`|` only on integer truth values. Bitwise operators evaluate both operands; do not use them as replacements when side effects or non-boolean values matter.

### Supplementary output
```text
A B | A&&B calls | A||B calls
0 0 | 0 (1) | 0 (2)
0 1 | 0 (1) | 1 (2)
1 0 | 0 (2) | 1 (1)
1 1 | 1 (2) | 1 (1)
Observation: && skips RHS when A=0; || skips RHS when A=1.

```

## Task 03 — Bitwise operations and register control

**Concepts:** bits represent flags. `|` sets a bit, `& ~mask` clears it, `^` toggles it, and `& mask` tests it. Shift operations create masks.

**Additional tests:** begin with zero; set two bits; clear one; toggle another; test an unset bit. Display the register in binary and decimal after each operation.

**Experiment:** verify that setting an already-set bit does not change the value, clearing an already-clear bit remains zero, and toggling twice restores the original value.

### Supplementary output
```text
Initial:
00000000 (0)
Set bit 2:
00000100 (4)
Set bit 5:
00100100 (36)
Clear bit 2:
00100000 (32)
Toggle bit 5:
00000000 (0)
Test bit 0: OFF

```

## Task 04 — Decision structures and grade classification

**Concepts:** `if-else`, `switch`, and lookup tables can implement classification rules. Validate the input domain before mapping marks to a grade. In `switch`, missing `break` causes fall-through.

**Additional tests:** every grade boundary (49/50, 59/60, 69/70, 79/80, 89/90), plus -1 and 101. These tests expose off-by-one and invalid-input bugs.

**Comparison:** an `else-if` ladder is natural for ranges; a `switch` is convenient for discrete values; a table is compact when mapping is stable.

### Supplementary output
```text
Marks | Grade | Expected category
   -1 | ? | invalid
    0 | F | F
   49 | F | F
   50 | D | D
   59 | D | D
   60 | C | C
   69 | C | C
   70 | B | B
   79 | B | B
   80 | A | A
   89 | A | A
   90 | S | S
   99 | S | S
  100 | S | S
  101 | ? | invalid

```

## Task 05 — Loops and prime-number testing

**Concepts:** `for`, `while`, and `do-while` differ in when their condition is tested. Prime testing needs no divisor beyond the square root of the number. Use `i <= n/i` to avoid overflow from `i*i`.

**Additional tests:** negative numbers, 0, 1, 2, even composites, odd composites, and primes such as 29 and 97. Count primes from 2 through 100.

**Experiment:** compare a basic divisor loop with the optimized 6k±1 candidate method. Both are O(sqrt(n)) but the optimized method skips divisors.

### Supplementary output
```text
Number | Prime? | Explanation
    -5 | NO | less than 2
     0 | NO | less than 2
     1 | NO | less than 2
     2 | YES | no divisor found
     3 | YES | no divisor found
     4 | NO | composite/even
     9 | NO | composite/even
    25 | NO | composite/even
    29 | YES | no divisor found
    97 | YES | no divisor found
   100 | NO | composite/even
   101 | YES | no divisor found

Primes from 2 to 100: 25

```

## Task 06 — Condition-controlled loops and loan repayment

**Concepts:** a `while` loop is suitable when the number of iterations is unknown. Each month, add interest, then pay the smaller of EMI and remaining balance. Use a small tolerance for floating-point termination and a safety limit.

**Additional tests:** zero principal, normal repayment, EMI at or below monthly interest, and zero-interest loans.

**Experiment:** compare cases where the EMI is larger than interest (loan shrinks), equal to interest (no progress), or smaller than interest (balance grows). A guard prevents infinite loops.

### Supplementary output
```text
Loan | monthly rate | EMI | months | status
   0 |  2.00% | 1000 |  0 | already settled
10000 |  2.00% | 2000 |  6 | paid
10000 |  2.00% |  200 | -- | EMI <= interest; cannot repay
5000 |  0.00% | 1000 |  5 | paid

```

## Task 07 — Algorithm redesign and performance comparison

**Concepts:** prime checking can be improved by rejecting multiples of 2 and 3, then testing candidates of the form 6k±1. This reduces trial candidates while preserving the O(sqrt(n)) complexity.

**Additional tests:** small primes, small composites, and larger primes. Run both the basic method and optimized method on the same inputs and verify agreement.

**Experiment:** compare correctness and candidate counts/time across larger values. Performance claims should be measured on the same machine and compiler; avoid claiming a speedup from a single run.

### Supplementary output
```text
n | trial division | 6k+-1 method | agreement
    2 | 1 | 1 | YES
    3 | 1 | 1 | YES
    4 | 0 | 0 | YES
   25 | 0 | 0 | YES
   97 | 1 | 1 | YES
  997 | 1 | 1 | YES
10007 | 1 | 1 | YES
99991 | 1 | 1 | YES
The 6k+-1 method skips multiples of 2 and 3; both remain O(sqrt(n)).

```

## Overall comparison and conclusion

| Task | Main technique | Typical error exposed | Improved practice |
|---|---|---|---|
| Q1 | Operator precedence | Wrong order / integer truncation | Parentheses and intermediate values |
| Q2 | Short-circuit logic | Unnecessary calls or side effects | Place inexpensive/selective tests first |
| Q3 | Bitwise masks | Incorrect bit manipulation | Use named masks and verify binary state |
| Q4 | Decision structures | Boundary and fall-through errors | Validate input and test every boundary |
| Q5 | Loops | Inefficient divisor search / edge cases | Stop at square root and handle n<2 |
| Q6 | Condition-controlled loops | Infinite loop or overpayment | Progress checks, tolerance and last-payment rule |
| Q7 | Algorithm redesign | Unverified optimization | Compare correctness on identical inputs |

**Conclusion:** Supplementary tests help verify not only the normal output, but also boundary behavior, invalid input, and algorithmic assumptions. The original assignment files remain intact; these are additional practice and evidence files.
