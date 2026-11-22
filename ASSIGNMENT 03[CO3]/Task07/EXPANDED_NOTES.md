# Task07 — Election Vote Counting: Expanded Notes

## Concept
Validate each vote before indexing a count array. Candidate number k maps to counts[k-1]. After one pass, sort candidate IDs by count and detect whether the maximum count is shared.

## Complexity
Counting votes O(v); sorting c candidates O(c²) in this implementation; extra space O(c). A count array avoids searching candidate records for every vote.

## Additional test plan
Test valid votes, invalid 0/negative/out-of-range values, no valid votes, one winner and a tie.

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
