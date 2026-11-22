# Test Cases
| Case | Input | Expected |
|---|---|---|
| Normal | Arun, 24, BP 120/80 | Record prints correctly |
| Long phone | 10-digit phone | Phone retained |
| Boundary age | 0 | Validation should reject in a production version |
| Date | 22/11/2026 | Date fields print in dd/mm/yyyy |
