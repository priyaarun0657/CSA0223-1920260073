# Task06 — Sorting and Searching Strings: Expanded Notes

## Concept
strcmp compares strings lexicographically. Sorting names allows binary search and makes duplicate values adjacent. Names can be moved directly or sorted indirectly through indices/pointers.

## Complexity
Bubble sort O(n²) comparisons; binary search O(log n) string comparisons, each comparison may inspect up to L characters. Sorting indices reduces large character-copy costs.

## Additional test plan
Test names with different case, duplicates, short and maximum-length strings, present and missing search keys.

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
