/* Q4 - else-if ladder vs switch vs lookup table; boundary tests; missing break;
 *      scholarship decision structure.
 * */
#include <stdio.h>

static int cmp_count;                      /* comparisons made by the ladder */

/* 1. else-if ladder (range tests, validation first) */
char grade_ladder(int m)
{
    cmp_count = 0;
    cmp_count += 2; if (m < 0 || m > 100) return '?';
    cmp_count++; if (m >= 90) return 'S';
    cmp_count++; if (m >= 80) return 'A';
    cmp_count++; if (m >= 70) return 'B';
    cmp_count++; if (m >= 60) return 'C';
    cmp_count++; if (m >= 50) return 'D';
    return 'F';
}

/* 2. switch on marks / 10 (validation first) */
char grade_switch(int m)
{
    if (m < 0 || m > 100) return '?';
    switch (m / 10) {
        case 10: case 9: return 'S';
        case 8: return 'A';
        case 7: return 'B';
        case 6: return 'C';
        case 5: return 'D';
        default: return 'F';
    }
}

/* 3. lookup table indexed by marks / 10 */
char grade_table(int m)
{
    static const char grades[11] = {'F','F','F','F','F','D','C','B','A','S','S'};
    if (m < 0 || m > 100) return '?';
    return grades[m / 10];
}

/* 4. BUG A: switch WITHOUT the range check */
char grade_switch_nocheck(int m)
{
    switch (m / 10) {
        case 10: case 9: return 'S';
        case 8: return 'A';
        case 7: return 'B';
        case 6: return 'C';
        case 5: return 'D';
        default: return 'F';
    }
}

/* 5. BUG B: switch with the break/return missing after case 8 (fallthrough) */
char grade_switch_nobreak(int m)
{
    char g = '?';
    if (m < 0 || m > 100) return '?';
    switch (m / 10) {
        case 10: case 9: g = 'S'; break;
        case 8: g = 'A';                  /* <-- break removed: falls into case 7 */
        case 7: g = 'B'; break;
        case 6: g = 'C'; break;
        case 5: g = 'D'; break;
        default: g = 'F'; break;
    }
    return g;
}

/* scholarship: grade x income band lookup (0: < 2.5L, 1: 2.5-5L, 2: > 5L) */
static const int sch[5][3] = {            /* percent fee waiver */
    /* S */ {100, 75, 50},
    /* A */ { 50, 25,  0},
    /* B */ { 25,  0,  0},
    /* C */ {  0,  0,  0},
    /* D */ {  0,  0,  0}
};
int scholarship(char g, int band)
{
    const char *order = "SABCD";
    for (int i = 0; i < 5; i++) if (order[i] == g) return sch[i][band];
    return 0;                             /* F or '?' : none */
}

int main(void)
{
    int t[] = {100, 90, 89, 0, -1, 101};
    puts("=== Required test values ===");
    puts("marks | ladder switch table | switch(no range check) | comparisons in ladder");
    for (int i = 0; i < 6; i++) {
        char l = grade_ladder(t[i]);
        int c = cmp_count;
        printf("%5d |   %c      %c      %c   |           %c            | %d\n",
               t[i], l, grade_switch(t[i]), grade_table(t[i]), grade_switch_nocheck(t[i]), c);
    }

    puts("\n=== Boundary-exposing test set (every grade edge +-1, both ends) ===");
    int b[] = {-1,0,1,49,50,51,59,60,61,69,70,71,79,80,81,89,90,91,99,100,101};
    int n = (int)(sizeof b / sizeof b[0]), bad_nocheck = 0, bad_nobreak = 0;
    printf("marks: ");
    for (int i = 0; i < n; i++) printf("%4d", b[i]);
    printf("\nladder:");
    for (int i = 0; i < n; i++) printf("%4c", grade_ladder(b[i]));
    printf("\nswitch:");
    for (int i = 0; i < n; i++) printf("%4c", grade_switch(b[i]));
    printf("\ntable :");
    for (int i = 0; i < n; i++) printf("%4c", grade_table(b[i]));
    printf("\nnochk :");
    for (int i = 0; i < n; i++) { char c = grade_switch_nocheck(b[i]); printf("%4c", c); if (c != grade_ladder(b[i])) bad_nocheck++; }
    printf("\nnobrk :");
    for (int i = 0; i < n; i++) { char c = grade_switch_nobreak(b[i]); printf("%4c", c); if (c != grade_ladder(b[i])) bad_nobreak++; }
    printf("\n\n");

    puts("=== Exhaustive check: marks -20..120 (141 values), ladder is the reference ===");
    int ds = 0, dt = 0, dn = 0, db = 0, total = 0, first_bad_nb = -1000;
    for (int m = -20; m <= 120; m++) {
        total++;
        char r = grade_ladder(m);
        if (grade_switch(m) != r) ds++;
        if (grade_table(m) != r) dt++;
        if (grade_switch_nocheck(m) != r) dn++;
        if (grade_switch_nobreak(m) != r) { db++; if (first_bad_nb == -1000) first_bad_nb = m; }
    }
    printf("  switch mismatches: %d | table mismatches: %d\n", ds, dt);
    printf("  no-range-check switch mismatches: %d of %d (the values -20..-1 and 101..120)\n", dn, total);
    printf("  missing-break switch mismatches: %d (marks 80..89 return 'B', first at %d)\n\n", db, first_bad_nb);

    puts("=== Missing-break demo (the TODO program with 'case 8' break removed) ===");
    int demo[] = {100, 95, 83, 50, 49, -5};
    printf("  expected      : 100:S 95:S 83:A 50:D 49:F -5:?\n  without break : ");
    for (int i = 0; i < 6; i++) printf("%d:%c ", demo[i], grade_switch_nobreak(demo[i]));
    puts("\n  -> 83 is now 'B' (A falls through into case 7)");

    puts("\n=== Scholarship (grade x income band) via 2-D lookup table: % fee waiver ===");
    puts("  grade | <2.5L  2.5-5L  >5L");
    for (char *g = "SABCDF"; *g; g++)
        printf("    %c   | %4d%% %6d%% %5d%%\n", *g, scholarship(*g, 0), scholarship(*g, 1), scholarship(*g, 2));
    printf("  e.g. marks 83, income band 1 -> grade %c -> %d%% waiver\n", grade_ladder(83), scholarship(grade_ladder(83), 1));
    return 0;
}
