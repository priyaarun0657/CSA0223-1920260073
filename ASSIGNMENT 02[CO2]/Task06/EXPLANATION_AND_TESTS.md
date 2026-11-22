## Task 06 — Condition-controlled loops and loan repayment

**Concepts:** a `while` loop is suitable when the number of iterations is unknown. Each month, add interest, then pay the smaller of EMI and remaining balance. Use a small tolerance for floating-point termination and a safety limit.

**Additional tests:** zero principal, normal repayment, EMI at or below monthly interest, and zero-interest loans.

**Experiment:** compare cases where the EMI is larger than interest (loan shrinks), equal to interest (no progress), or smaller than interest (balance grows). A guard prevents infinite loops.
