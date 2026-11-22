# Growth strategy
Doubling yields O(n) total relocation over n appends and amortized O(1) insertion. Fixed increments of 10 can cause O(n²) total copying. Doubling may leave up to nearly capacity/2 slots unused; fixed growth wastes at most 9 slots but performs more reallocations.
