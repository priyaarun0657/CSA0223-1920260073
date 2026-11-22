/* Q5 (extra) - break, continue, goto and do-while in loop design
 * * PREDICTIONS (by hand / known values, before running):
 *   next prime >= 1,000,000          = 1000003
 *   primes <= 100 = 25 ; <= 1000 = 168 ; <= 10000 = 1229
 *   digit sum of 987654              = 39 ; digit reversal = 456789
 *   smallest a*b = 1000001 (2<=a<=b) = 101 * 9901
 *   skipping evens with 'continue' roughly halves the trial divisions   <-- WRONG PREDICTION (see note
 *     printed under section 2: evens already exit after ONE division, so continue saves only 1 per even)
 */
#include <stdio.h>

static unsigned long divs;
static int is_prime(unsigned long n)
{
    if (n < 2) return 0;
    for (unsigned long i = 2; i * i <= n; i++) { divs++; if (n % i == 0) return 0; }
    return 1;
}

int main(void)
{
    puts("=== 1. break: first prime >= 1,000,000 ===");
    unsigned long n; divs = 0;
    for (n = 1000000; ; n++) if (is_prime(n)) break;
    printf("  found %lu (predicted 1000003), tried %lu candidates, %lu divisions\n\n", n, n - 1000000 + 1, divs);

    puts("=== 2. continue: count primes, skipping even candidates ===");
    unsigned long limits[] = {100, 1000, 10000};
    unsigned long pred[]   = {25, 168, 1229};
    for (int k = 0; k < 3; k++) {
        unsigned long cnt, d_all, d_skip;
        divs = 0; cnt = 0; for (unsigned long x = 1; x <= limits[k]; x++) if (is_prime(x)) cnt++;
        d_all = divs;
        divs = 0; unsigned long cnt2 = 1;                 /* the prime 2 counted separately */
        for (unsigned long x = 3; x <= limits[k]; x++) { if (x % 2 == 0) continue; if (is_prime(x)) cnt2++; }
        d_skip = divs;
        printf("  primes <= %5lu : %4lu (predicted %lu), with continue %4lu | divisions %6lu -> %6lu (%.0f%%)%s\n",
               limits[k], cnt, pred[k], cnt2, d_all, d_skip, 100.0 * d_skip / d_all, cnt == cnt2 ? "" : " MISMATCH");
    }

    puts("  note: my prediction (about 50%) was wrong. An even n already returns after one division (n % 2),");
    puts("        so 'continue' only saves 1 division per even number; the saving shrinks as n grows (79% -> 96%).");

    puts("\n=== 3. goto: leave two nested loops at once ===");
    unsigned long N = 1000001, tries = 0, fa = 0, fb = 0;
    for (unsigned long a = 2; a * a <= N; a++)
        for (unsigned long b = a; a * b <= N; b++) {
            tries++;
            if (a * b == N) { fa = a; fb = b; goto found; }
        }
    found:
    printf("  %lu = %lu * %lu (predicted 101 * 9901) after %lu inner iterations\n", N, fa, fb, tries);

    puts("\n=== 4. do-while: digit sum and reversal (body must run once, even for 0) ===");
    unsigned long vals[] = {987654, 0, 70};
    for (int k = 0; k < 3; k++) {
        unsigned long v = vals[k], sum = 0, rev = 0; int digits = 0;
        do { sum += v % 10; rev = rev * 10 + v % 10; v /= 10; digits++; } while (v > 0);
        printf("  %7lu : digits=%d  digit sum=%lu  reversed=%lu\n", vals[k], digits, sum, rev);
    }
    puts("  (a while(v > 0) loop would report 0 digits for the input 0; do-while correctly reports 1)");
    return 0;
}
