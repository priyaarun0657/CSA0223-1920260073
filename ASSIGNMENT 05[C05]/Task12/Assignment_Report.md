# Assignment 5 – CO5 Report
## Objective
Design modular C programs using functions, recursion, pointers, dynamic memory and persistent file handling.
## Design findings
Functions with explicit parameters improve reuse. Recursive halving power reduces calls from O(n) to O(log n). Pointers enable in-place updates; dynamic arrays use doubling for amortized O(1) insertion. Text donor records are readable; binary stock records support fixed-size updates.
## Experimental summary
See `experimental_summary.csv`. Actual timings depend on compiler, OS, storage and hardware; fill measurements from your machine before final submission.
## Conclusion
A growable array is suitable for moderate district data. For very large donor collections, consider batching or a sorted index. Validate inputs, check file operations and free allocations.
