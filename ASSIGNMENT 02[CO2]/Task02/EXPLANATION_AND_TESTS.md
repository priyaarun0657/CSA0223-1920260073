## Task 02 — Logical operators and short-circuit evaluation

**Concepts:** `&&` and `||` evaluate left-to-right and may skip the right operand. This can reduce expensive function calls, but it also changes whether side effects such as logging happen.

**Additional tests:** all four truth-value combinations. The extra program counts function calls to show that `0 && RHS` skips RHS and `1 || RHS` skips RHS.

**Experiment:** compare logical `&&`/`||` with bitwise `&`/`|` only on integer truth values. Bitwise operators evaluate both operands; do not use them as replacements when side effects or non-boolean values matter.
