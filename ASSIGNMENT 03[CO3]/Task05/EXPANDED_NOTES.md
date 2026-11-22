# Task05 — Character Arrays and Strings: Expanded Notes

## Concept
A C string is a character array terminated by '\0'. String loops should stop at the terminator. Character functions should receive unsigned-char values to avoid undefined behaviour for negative char values.

## Complexity
Most one-pass operations are O(n) time and O(1) extra space. Repeated strlen inside a loop can make a loop O(n²).

## Additional test plan
Test empty strings, multiple spaces, punctuation, tabs, mixed case, digits and palindrome/non-palindrome strings.

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
