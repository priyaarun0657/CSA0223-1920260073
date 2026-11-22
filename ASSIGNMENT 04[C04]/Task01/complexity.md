# Complexity
- Record creation: O(1)
- Access a patient: O(1)
- Sorting n patients by age: O(n log n) with a comparison sort.
- Array-of-structures keeps each record together; a swap moves one complete record.
- Parallel arrays may improve column-oriented processing, but sorting requires synchronized swaps across arrays.
- Space: O(n) records for either design; structure padding can increase per-record size.
