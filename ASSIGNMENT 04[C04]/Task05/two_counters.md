# Independent Counters
Use separate static variables or caller-owned counters. A function taking `int *counter` can support independent counters by passing different addresses.
