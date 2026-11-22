## Task 04 — Decision structures and grade classification

**Concepts:** `if-else`, `switch`, and lookup tables can implement classification rules. Validate the input domain before mapping marks to a grade. In `switch`, missing `break` causes fall-through.

**Additional tests:** every grade boundary (49/50, 59/60, 69/70, 79/80, 89/90), plus -1 and 101. These tests expose off-by-one and invalid-input bugs.

**Comparison:** an `else-if` ladder is natural for ranges; a `switch` is convenient for discrete values; a table is compact when mapping is stable.
