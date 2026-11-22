/* Q1 (extra) - Precedence quiz with predictions + 10-bill audit, integer-paise billing
 * * Part A predictions were written by hand BEFORE running (expected[] below).
 */
#include <stdio.h>

int main(void)
{
    puts("=== A. Precedence / associativity predictions vs observed ===");
    int a, b, c;
    a = b = c = 4;                                 /* '=' is right-to-left */
    struct { const char *expr; int expected, observed; } t[] = {
        {"2 + 3 * 4",                14,  2 + 3 * 4},
        {"10 - 4 - 3",                3,  10 - 4 - 3},
        {"100 / 10 * 5",             50,  100 / 10 * 5},
        {"100 / (10 * 5)",            2,  100 / (10 * 5)},
        {"7 % 4 * 2",                 6,  7 % 4 * 2},
        {"1 + 2 << 3",               24,  1 + 2 << 3},
        {"5 & 3 == 3",                1,  5 & 3 == 3},
        {"(5 & 3) == 3",              0,  (5 & 3) == 3},
        {"!0 && 0 || 1",              1,  !0 && 0 || 1},
        {"3 > 2 > 1",                 0,  3 > 2 > 1},
        {"-2 * -3",                   6,  -2 * -3},
        {"~0 & 0xF",                 15,  ~0 & 0xF},
        {"1 ? 2 : 3 ? 4 : 5",         2,  1 ? 2 : 3 ? 4 : 5},
        {"0 ? 2 : 0 ? 4 : 5",         5,  0 ? 2 : 0 ? 4 : 5},
        {"a = b = c  (all were 4)", 4,  a},
    };
    int n = (int)(sizeof t / sizeof t[0]), ok = 0;
    for (int i = 0; i < n; i++) {
        printf("  %-26s predicted %3d  observed %3d  %s\n", t[i].expr, t[i].expected, t[i].observed,
               t[i].expected == t[i].observed ? "OK" : "MISMATCH");
        ok += t[i].expected == t[i].observed;
    }
    printf("  %d of %d predictions correct\n\n", ok, n);

    puts("=== B. Ten-bill audit: buggy expression vs integer-paise correct billing ===");
    int price[10] = {  12, 250,  45, 333,  99, 480, 1500,  75,  20, 999 };
    int qty[10]   = {   5,   4,   7,   3,  10,   2,    1,  13,  50,   1 };
    int sen[10]   = {   0,   1,   0,   1,   1,   0,    1,   0,   1,   1 };
    puts("  #  price qty sen | buggy net | correct net (Rs) | diff (Rs)");
    int wrong = 0; long diff_total = 0;
    for (int i = 0; i < 10; i++) {
        int total = price[i] * qty[i] - price[i] * qty[i] * 15 / 100 * sen[i] + price[i] * qty[i] * 5 / 100;
        int net = total > 1000 ? total - 50 : total;           /* original statements */

        long gross_p   = (long)price[i] * qty[i] * 100;        /* everything in paise */
        long taxable_p = (gross_p * (100 - 15 * sen[i]) + 50) / 100;
        long gst_p     = (taxable_p * 5 + 50) / 100;
        long total_p   = taxable_p + gst_p;
        long net_p     = total_p > 100000 ? total_p - 5000 : total_p;
        long diff_p    = net * 100L - net_p;
        if (diff_p != 0) { wrong++; diff_total += diff_p; }
        printf(" %2d  %5d %3d %3d | %9d | %10ld.%02ld | %+7ld.%02ld\n", i + 1, price[i], qty[i], sen[i], net,
               net_p / 100, net_p % 100, diff_p / 100, (diff_p < 0 ? -diff_p : diff_p) % 100);
    }
    printf("  buggy bills that differ from the correct amount: %d of 10 (net error over 10 bills = %+.2f Rs)\n",
           wrong, diff_total / 100.0);
    return 0;
}
