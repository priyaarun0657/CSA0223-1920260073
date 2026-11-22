## Task 05 — Loops and prime-number testing

**Concepts:** `for`, `while`, and `do-while` differ in when their condition is tested. Prime testing needs no divisor beyond the square root of the number. Use `i <= n/i` to avoid overflow from `i*i`.

**Additional tests:** negative numbers, 0, 1, 2, even composites, odd composites, and primes such as 29 and 97. Count primes from 2 through 100.

**Experiment:** compare a basic divisor loop with the optimized 6k±1 candidate method. Both are O(sqrt(n)) but the optimized method skips divisors.
