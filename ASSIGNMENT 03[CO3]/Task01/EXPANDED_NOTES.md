# Task01 — Searching Algorithms: Expanded Notes

## Concept
Linear search scans items one by one and works on unsorted data. Binary search repeatedly halves the search interval and requires sorted data.

## Complexity
Linear: best O(1), worst O(n), average O(n), space O(1). Binary: best O(1), worst/average O(log n), space O(1).

## Additional test plan
Test first, middle, last and absent keys. Include duplicate values and a one-element array.

## Additional example
Compile and run `additional_examples.c` in this folder:
```bash
gcc additional_examples.c -o example
./example
```

## Learning checkpoints
1. Explain the algorithm without reading the source line-by-line.
2. Identify the loop invariant or stopping condition.
3. Explain the edge case handled by the program.
4. Predict the output before executing it.
5. Compare the result with the main task program.
