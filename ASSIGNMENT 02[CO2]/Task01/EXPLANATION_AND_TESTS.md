## Task 01 — Operators, precedence and billing

**Concepts:** precedence decides which operator is evaluated first; associativity resolves operators of the same precedence; integer division truncates; explicit parentheses improve clarity. The billing case demonstrates how a misplaced expression can apply GST before a discount and how integer arithmetic loses fractional rupees.

**Additional tests:** zero quantity, non-senior customer, discount-bearing customer, and multiple bill values. Compare the buggy expression with a corrected calculation using intermediate variables and `double`.

**Expected lesson:** write and verify each intermediate value (`gross`, `discount`, `taxable`, `GST`, `final`) instead of relying on a long expression.
