# Task03 — Merging Sorted Arrays: Expanded Notes

## Concept
Merge two already sorted arrays by comparing their current elements and copying the smaller (ascending) or larger (descending) value. Once one list ends, copy the remainder.

## Complexity
Time O(m+n); output space O(m+n). Each input item is processed once. Re-sorting the combined list usually costs O((m+n) log(m+n)).

## Additional test plan
Test unequal lengths, one empty list, equal values, all-equal values, and both ascending and descending order.

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
