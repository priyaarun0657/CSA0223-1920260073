# CSA02--Assignment2

| | |
|---|---|
| | | **Course** | CSA02 – C Programming (Saveetha Institute of Medical and Technical Sciences) |
| **Assignment** | Assignment 2 – CO2 (operators, decision-making, looping), 50 marks |
| **Compiler / version** | GCC 13.3.0 (Ubuntu 13.3.0-6ubuntu2~24.04.1), C default standard (gnu17) |
| **GitHub repository link** | `https://github.com/<your-username>/CSA02--Assignment2`  ← fill in after pushing |

## Compile command (exact)

Every program is compiled the same way (only the `-lm` / `-O0` differ where noted in the table):

```bash
gcc -Wall -Wextra -o <exe> <file>.c            # Q6 additionally needs: -lm
```

## Repository layout

```
Task01/  q1_precedence.c            Q1  precedence, associativity, discount bug, count++ UB
         q1_more_precedence.c       Q1  extra: 15-expression precedence quiz + 10-bill audit (integer paise)
Task02/  q2_shortcircuit.c          Q2  short-circuit evaluation, call counting, audit-log change
         q2_three_conditions.c      Q2  extra: all 6 orders of three conditions (cost-aware ordering)
Task03/  q3_register.c              Q3  Complete the Code (TODO 1-4) – bit register
         q3_inquiry.c               Q3  precedence / signed-char inquiry + array alternative
         q3_stress_test.c           Q3  extra: exhaustive + 1,000,000 random-operation verification
Task04/  q4_grade.c                 Q4  Complete the Code (TODO 1) – switch grade()
         q4_compare.c               Q4  ladder vs switch vs table, boundary tests, fallthrough
         q4_scholarship_full.c      Q4  extra: 12 students, nested-if vs switch vs table scholarship
Task05/  q5_is_prime.c              Q5  Complete the Code (TODO 1) – i*i <= n
         q5_variants.c              Q5  for / while / do-while, overflow, sieve alternative
         q5_loops_extra.c           Q5  extra: break, continue, goto, do-while digit loops
Task06/  q6_loan.c                  Q6  loan schedule, termination, growth, safety limit
         q6_more_loans.c           Q6  extra: 5 more loans, integer-paise model, while vs do-while
Task07/  q7_redesign.c              Q7  Day-4: diagnose, redesign (6k±1), validate
         q7_scaling.c               Q7  extra: scaling 10^1..10^12 and a second candidate (wheel mod 30)
tools/   screenshot.py, make_charts.py, build_results.py   (regenerate screenshots / charts / BUILD_RESULTS.md)
BUILD_RESULTS.md                    raw output of every program
REPORT_DRAFT.md                     evidence for Q1–Q7 (predictions, analysis, tables, defences)
```

Each `TaskNN/` folder holds the C source, the output screenshots (`output_*.png`) and, where the
question asks for graphs, a chart (`*_chart.png`). No input files are needed – every program is self-contained.

## How to run

```bash
cd Task01 && gcc -Wall -Wextra -o q1 q1_precedence.c && ./q1
cd ../Task02 && gcc -Wall -Wextra -o q2 q2_shortcircuit.c && ./q2
cd ../Task03 && gcc -Wall -Wextra -o q3 q3_register.c && ./q3
             && gcc -Wall -Wextra -o q3i q3_inquiry.c && ./q3i
cd ../Task04 && gcc -Wall -Wextra -o q4 q4_grade.c && ./q4
             && gcc -Wall -Wextra -o q4c q4_compare.c && ./q4c
cd ../Task05 && gcc -Wall -Wextra -o q5 q5_is_prime.c && ./q5
             && gcc -Wall -Wextra -o q5v q5_variants.c && ./q5v
cd ../Task06 && gcc -Wall -Wextra -o q6 q6_loan.c -lm && ./q6
cd ../Task07 && gcc -Wall -Wextra -o q7 q7_redesign.c && ./q7

# extra experiments (one per task)
cd ../Task01 && gcc -Wall -Wextra -o q1b q1_more_precedence.c && ./q1b
cd ../Task02 && gcc -Wall -Wextra -o q2b q2_three_conditions.c && ./q2b
cd ../Task03 && gcc -Wall -Wextra -o q3s q3_stress_test.c && ./q3s
cd ../Task04 && gcc -Wall -Wextra -o q4s q4_scholarship_full.c && ./q4s
cd ../Task05 && gcc -Wall -Wextra -o q5x q5_loops_extra.c && ./q5x
cd ../Task06 && gcc -Wall -Wextra -o q6b q6_more_loans.c -lm && ./q6b
cd ../Task07 && gcc -Wall -Wextra -o q7s q7_scaling.c && ./q7s
```

## Result of each task

| Task | Result |
|---|---|
| **Q1** | The three predicted bills match the observed buggy output exactly (1080/1030, 330/330, 899/899). Intended amounts are 1021.00, 330.75, 891.61. Two real bugs found: GST is charged on the *undiscounted* amount, and integer division truncates paise. `count = count++ + 1;` is undefined behaviour; `-Wall` reports `-Wsequence-point`. Corrected version uses intermediate variables (`gross, discount, taxable, gst`). |
| **Q2** | For 1000 passengers: `(senior&&elig)\|\|verify` = 887 slow calls, `verify\|\|(senior&&elig)` = 1000, nested-if = 887, non-short-circuit `&`/`\|` = 1000. All four grant the same 185 passengers. With the audit log, the short-circuit order logs only 887 passengers, the others log all 1000. |
| **Q3** | TODO 1-4 completed with bitwise operators only; output `00000101`, `00000110`, `AC is ON, PUMP is OFF` equals the expected output. Register values predicted before running all matched. `reg & 1 << dev` ≠ `(reg & 1) << dev` demonstrated (4 vs 0); signed `char` 0x80 promotes to -128. Array alternative: 8 MB vs 1 MB for 1,000,000 homes. |
| **Q4** | TODO 1 completed (`100:S 95:S 83:A 50:D 49:F -5:?` matches). Ladder, switch and table agree on all 141 values tested (-20..120). Switch without range check gets 40 of them wrong (-1 → F, 101 → S). Removing one `break` turns every mark 80–89 into `B`. Scholarship rule uses a 2-D lookup table. |
| **Q5** | TODO 1 completed; divisions 8 / 1 / 87 / 999 match expected. Changing to `i < n` gives 95 / 1 / 7917 / 1000001. `for`, `while`, guarded `do-while` all agree; unguarded `do-while` wrongly reports 2 as not prime. Sieve: 2,122,051 marking ops for N = 1,000,003 vs 67,741,504 trial divisions for all n ≤ N. |
| **Q6** | Rs 10,000 at 2 %/month, repay Rs 2,000 → 6 months, total interest Rs 645.38; hand calculation matches all 6 rows. Repayment ≤ Rs 200 is refused (never terminates); a 360-month limit stops near-miss cases. Closed formula agrees with the loop for every repayable case. |
| **Q7** | Chosen program: Q5 prime test. Redesign tests 2, 3, then only 6k±1. 1000003: 999 → 334 divisions (ratio 0.334); all n ≤ 1,000,003: 67,741,504 → 23,739,568 (65 % fewer); 0 answer mismatches. Slightly worse only for tiny primes 5 and 7. |

## Extra experiments (result of each)

| Task | Extra result |
|---|---|
| **Q1** | 15 of 15 precedence predictions correct (e.g. `5 & 3 == 3` = 1). In a 10-bill audit the buggy expression was wrong on 8 bills; net error +Rs 46.95. |
| **Q2** | All 6 orders of three `\|\|` conditions: best A,B,C = 70.98 cost/passenger (predicted 71.00), worst C,B,A = 110.36 (1.6x); granted count identical (8037). |
| **Q3** | 8,192 exhaustive checks and 1,000,000 random operations against an array model: 0 mismatches; predicted sequence using bit 7 all matched. |
| **Q4** | 12-student classifier (2 rejected); nested-if, switch and table agree on all 303 (marks, band) cases; income band edges checked. |
| **Q5** | `break`: next prime ≥ 1,000,000 is 1000003; prime counts 25/168/1229 as predicted; `goto` finds 101 × 9901; do-while handles input 0. One prediction was wrong (see report). |
| **Q6** | 5 more loans: hand estimates 20/13/23/never/241 months all matched; integer-paise model agrees with double to a few paise. |
| **Q7** | Ratios stay constant from 10^1 to 10^12: 6k±1 ≈ 0.333, wheel-30 ≈ 0.267; 0 mismatches over 2,000,000 values. |

## Notes

* Output screenshots are terminal transcripts rendered by `tools/screenshot.py`, which compiles and runs the
  program in the task folder and draws the real `$ command` + output. You can re-take them in your own terminal.
* Commit progressively (one commit per task) – see `commit_progressively.sh`.


## Expanded Edition (additional examples and experiments)

This ZIP now includes **one supplementary C program for every task (Q1–Q7)**, with extra edge cases, comparisons, and output evidence.

### Added files
| Task | Supplementary program | Focus |
|---|---|---|
| Q1 | `q1_extra_cases.c` | Multi-case billing calculations and intermediate values |
| Q2 | `q2_extra_cases.c` | Logical truth table and short-circuit function-call counts |
| Q3 | `q3_extra_cases.c` | Set, clear, toggle, and test register bits |
| Q4 | `q4_extra_cases.c` | Grade boundaries and invalid marks |
| Q5 | `q5_extra_cases.c` | Prime edge cases and prime count from 2–100 |
| Q6 | `q6_extra_cases.c` | Zero loan, repayment, no-progress and zero-interest cases |
| Q7 | `q7_extra_cases.c` | Basic trial division vs 6k±1 optimization |

Every supplementary program includes:
- C source code
- A captured text output (`*_OUTPUT.txt`)
- A terminal-style output screenshot (`*_output_screenshot.png`)
- Task-specific concept notes and test cases (`EXPLANATION_AND_TESTS.md`)

### Run supplementary programs
From each task folder:
```bash
gcc -Wall -Wextra -std=c11 -O2 q1_extra_cases.c -o q1_extra_cases
./q1_extra_cases
```
Replace the source/executable names for the relevant task. Q6's original loan program may require `-lm` for math functions.

### Expanded test coverage
- **Q1:** zero quantity, senior/non-senior cases, multiple prices, intermediate calculations.
- **Q2:** all four logical input combinations and call-count comparison.
- **Q3:** bit set/clear/toggle/test behavior.
- **Q4:** grade boundaries and invalid marks.
- **Q5:** negative, 0, 1, 2, composite and prime values.
- **Q6:** zero principal, normal EMI, EMI not exceeding interest, zero-interest repayment.
- **Q7:** cross-check algorithm agreement for small and larger values.

## Supplementary Experiment Report
See `EXTRA_EXPERIMENTS.md` for the consolidated explanations, observations, comparison tables, and test strategy.
