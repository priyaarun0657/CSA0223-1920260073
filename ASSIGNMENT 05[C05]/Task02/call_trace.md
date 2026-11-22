# A2 Call traces
Digital root 9875 → 29 → 11 → 2. Base case is a single digit; recursive case sums digits and calls again.
Fast power 2^10: 10→5→2→1→0, then results unwind. Base case n=0. Linear power calls n+1 times; halving power calls O(log n) times.
