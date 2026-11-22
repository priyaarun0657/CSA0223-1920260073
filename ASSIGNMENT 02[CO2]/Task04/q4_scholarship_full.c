/* Q4 (extra) - Full classifier: marks + family income -> grade + scholarship
 * * Compares THREE structures for the scholarship rule on all 101 x 3 inputs:
 *   (1) nested if   (2) switch inside if   (3) 2-D lookup table
 * PREDICTION: all three agree on every input (0 differences); invalid marks -> 'X' / reject.
 * Income bands (annual): band 0 < 250000 ; band 1 250000..500000 ; band 2 > 500000
 */
#include <stdio.h>

static char grade(int m) { return m<0||m>100 ? '?' : m>=90?'S' : m>=80?'A' : m>=70?'B' : m>=60?'C' : m>=50?'D' : 'F'; }
static int band(long inc) { return inc < 250000 ? 0 : (inc <= 500000 ? 1 : 2); }

static int sch_nested(char g, int b)
{
    if (g == 'S') { if (b == 0) return 100; else if (b == 1) return 75; else return 50; }
    else if (g == 'A') { if (b == 0) return 50; else if (b == 1) return 25; else return 0; }
    else if (g == 'B') { if (b == 0) return 25; else return 0; }
    return 0;
}
static int sch_switch(char g, int b)
{
    switch (g) {
        case 'S': return b == 0 ? 100 : (b == 1 ? 75 : 50);
        case 'A': return b == 0 ? 50 : (b == 1 ? 25 : 0);
        case 'B': return b == 0 ? 25 : 0;
        default:  return 0;
    }
}
static int sch_table(char g, int b)
{
    static const int t[3][3] = {{100,75,50},{50,25,0},{25,0,0}};
    return (g == 'S') ? t[0][b] : (g == 'A') ? t[1][b] : (g == 'B') ? t[2][b] : 0;
}

int main(void)
{
    struct { const char *name; int marks; long income; } s[] = {
        {"Asha", 96, 180000}, {"Bala", 91, 320000}, {"Chitra", 89, 150000}, {"Dev", 83, 620000},
        {"Eswar", 78, 240000}, {"Farah", 65, 90000}, {"Gopal", 50, 480000}, {"Hari", 49, 100000},
        {"Indu", 100, 500000}, {"Jai", 101, 200000}, {"Kavi", -3, 300000}, {"Lata", 90, 250000}
    };
    puts("name    marks   income  grade band  waiver%  (nested/switch/table)");
    for (int i = 0; i < 12; i++) {
        char g = grade(s[i].marks);
        if (g == '?') { printf("%-7s %5d %8ld   REJECTED (marks outside 0..100)\n", s[i].name, s[i].marks, s[i].income); continue; }
        int b = band(s[i].income);
        int a = sch_nested(g, b), c = sch_switch(g, b), d = sch_table(g, b);
        printf("%-7s %5d %8ld    %c     %d    %3d%%     %d/%d/%d%s\n", s[i].name, s[i].marks, s[i].income, g, b, a, a, c, d,
               (a == c && c == d) ? "" : "  DIFFER");
    }
    long diffs = 0, cases = 0;
    for (int m = 0; m <= 100; m++) for (int b = 0; b < 3; b++) {
        char g = grade(m);
        cases++;
        if (sch_nested(g, b) != sch_switch(g, b) || sch_switch(g, b) != sch_table(g, b)) diffs++;
    }
    printf("\nexhaustive: %ld (marks, band) cases, %ld differences between the three structures\n", cases, diffs);
    puts("income boundary check (band 0 | 1 | 2 edges): ");
    long e[] = {0, 249999, 250000, 500000, 500001};
    for (int i = 0; i < 5; i++) printf("  income %7ld -> band %d\n", e[i], band(e[i]));
    return 0;
}
