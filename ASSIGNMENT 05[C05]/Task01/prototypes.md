# A1.2 Interfaces
- `int check_eligibility(int age, int days_since_last);` values are read-only scalar inputs.
- `int find_eligible(const int ages[], const int days[], const int ids[], int n, EligibleSummary *summary);` arrays are const; summary is a pointer because two outputs are updated.
- `int update_stock(int stock[], int group, int delta);` stock pointer permits mutation; group and delta are values.
- `int add_donor(DonorList *list, const Donor *donor);` list is mutable; donor is const.
- `int save_donors(const Donor *data, size_t n, const char *path);` records and path are read-only.

Multiple outputs: pointer parameters (`count`, `youngest_id`) or a returned structure. The structure groups outputs and is easier to extend; pointers avoid returning a potentially large object.
