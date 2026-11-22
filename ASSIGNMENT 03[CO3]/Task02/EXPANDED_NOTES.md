# Task02 — Sorting Algorithms: Expanded Notes

## Concept
Bubble sort swaps adjacent out-of-order elements and can stop early. Selection sort selects the minimum for each position. Insertion sort inserts each new element into the sorted prefix.

## Complexity
Bubble: best O(n) with early exit, worst O(n²). Selection: O(n²) comparisons. Insertion: best O(n), worst O(n²). All use O(1) auxiliary space.

## Additional test plan
Test sorted, nearly sorted, reverse, duplicate and random values. Compare comparisons and swaps/shifts.

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
