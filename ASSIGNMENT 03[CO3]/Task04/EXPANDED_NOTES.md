# Task04 — Two-Dimensional Arrays: Expanded Notes

## Concept
A 2-D array stores rows and columns in contiguous row-major memory in C. Nested loops compute row totals, column averages, maximum values and other matrix properties.

## Complexity
Access O(1). Full traversal O(rows×columns). A fixed 2-D array has no separate pointer-array overhead.

## Additional test plan
Test small hand-calculated matrices, negative values, all equal values, and boundary row/column indices.

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
