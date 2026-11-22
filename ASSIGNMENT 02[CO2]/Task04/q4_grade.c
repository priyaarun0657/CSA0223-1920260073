/* Q4 - Complete the Code: grade() with switch on marks / 10
 * * Grade rules: 90-100 S, 80-89 A, 70-79 B, 60-69 C, 50-59 D, below 50 F, invalid '?'
 * Expected: 100:S 95:S 83:A 50:D 49:F -5:?
 */
#include <stdio.h>

char grade(int marks)
{
    if (marks < 0 || marks > 100) return '?';
    switch (marks / 10) {                 /* TODO 1 */
        case 10:                          /* 100 */
        case 9:  return 'S';              /* 90-99  (cases combined with 10) */
        case 8:  return 'A';
        case 7:  return 'B';
        case 6:  return 'C';
        case 5:  return 'D';
        default: return 'F';              /* 0-49 : cases 0..4 combined */
    }
}

int main(void)
{
    int marks[] = {100, 95, 83, 50, 49, -5};
    for (int i = 0; i < 6; i++) printf("%d:%c ", marks[i], grade(marks[i]));
    printf("\n");
    return 0;
}
