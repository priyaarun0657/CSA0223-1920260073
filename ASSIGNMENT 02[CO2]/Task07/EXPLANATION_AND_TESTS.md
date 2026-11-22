## Task 07 — Algorithm redesign and performance comparison

**Concepts:** prime checking can be improved by rejecting multiples of 2 and 3, then testing candidates of the form 6k±1. This reduces trial candidates while preserving the O(sqrt(n)) complexity.

**Additional tests:** small primes, small composites, and larger primes. Run both the basic method and optimized method on the same inputs and verify agreement.

**Experiment:** compare correctness and candidate counts/time across larger values. Performance claims should be measured on the same machine and compiler; avoid claiming a speedup from a single run.
