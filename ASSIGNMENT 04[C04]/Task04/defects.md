# Defects
1. Passing a structure by value modifies only a copy.
2. `p.number` and `p.balance` are invalid because p is a pointer; use `p->number` and `p->balance`.
