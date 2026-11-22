# Design Review
- Parallel arrays can become misaligned when one array is updated but another is not.
- `char phone[10]` cannot safely hold ten digits plus the terminating null character.
- Blood pressure has two values; a single float is an unclear representation.
- A date stored as text is difficult to validate and compare.
- A missing capacity check can write beyond the arrays.
- Global `count` makes state harder to control and test.
- Sorting by age requires moving matching elements in every array.
## Repair
Use one `Patient` structure with nested `BloodPressure` and `Date`, and pass a pointer to the record.
