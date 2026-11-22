/* Q7 - Day-4 Design Challenge: Diagnose, Redesign, Validate  (program chosen: Q5 prime test)
 * *
 * ---------------------------------------------------------------------------
 * D. PREDICTIONS (written BEFORE the redesigned program was ever run)
 *   Redesign = test 2 and 3 once, then only divisors of the form 6k-1 and 6k+1.
 *   Divisions predicted (orig -> redesign):
 *        97      :    8 ->   4        (2, 3, then 5, 7)
 *        7919    :   87 ->  30        (2 + 14 values of i * 2)
 *        999983  :  998 -> 334        (2 + 166 values of i * 2)
 *        1000003 :  999 -> 334        (2 + 166 values of i * 2)  => ratio ~ 0.334
 *        1000001 :  100 ->  35        (composite = 101 * 9901; 101 is 6*17-1)
 *        100     :    1 ->   1        (no gain, 100 % 2 == 0 found at once)
 *        5, 7    :    1 ->   2        (redesign is WORSE for tiny primes)
 *   Batch over every n <= 1,000,003: original total 67,741,504 divisions (measured in Q5).
 *   Primes (78,499 of them, ~700 divisions each) dominate that total, so predicted
 *   redesign total is about 0.37 - 0.42 of the original, i.e. 25M - 28M divisions.
 *   Results must be identical for every n (same prime / not-prime answer).
 * ---------------------------------------------------------------------------
 */
#include <stdio.h>
#include <time.h>

static unsigned long checks;

/* ORIGINAL (Q5): trial division by every i with i*i <= n */
int prime_original(unsigned long n)
{
    checks = 0; if (n < 2) return 0;
    for (unsigned long i = 2; i * i <= n; i++) { checks++; if (n % i == 0) return 0; }
    return 1;
}

/* REDESIGN: every prime > 3 is 6k-1 or 6k+1, so test 2, 3 and then only 5,7, 11,13, 17,19 ... */
int prime_6k(unsigned long n)
{
    checks = 0;
    if (n < 2) return 0;
    if (n < 4) return 1;                       /* 2 and 3 are prime, no division needed */
    checks++; if (n % 2 == 0) return 0;
    checks++; if (n % 3 == 0) return 0;
    for (unsigned long i = 5; i * i <= n; i += 6) {
        checks++; if (n % i == 0)       return 0;   /* 6k-1 */
        checks++; if (n % (i + 2) == 0) return 0;   /* 6k+1 */
    }
    return 1;
}

int main(void)
{
    puts("=== A. Diagnosis (original program, evidence from Q5) ===");
    prime_original(1000003);
    printf("  large prime 1000003: %lu divisions, every one of them 'n %% i' with i = 2..1000\n", checks);
    puts("  - the count grows as sqrt(n)  (97 -> 8, 7919 -> 87, 1000003 -> 999)");
    puts("  - repeated work: every even i > 2 is tried although n % 2 already proved n odd;");
    puts("    every multiple of 3 is tried although n % 3 was already tested");
    puts("    => about 2/3 of the divisions can never find a divisor\n");

    puts("=== E. Same inputs, same counts: Original -> Redesigned ===");
    printf("%9s %-9s | %9s %9s %9s | %s\n", "n", "result", "original", "redesign", "predicted", "ratio");
    unsigned long n[]    = {5, 7, 25, 97, 100, 7919, 999983, 1000001, 1000003};
    unsigned long pred[] = {2, 2, 3, 4, 1, 30, 334, 35, 334};
    for (int k = 0; k < 9; k++) {
        int a = prime_original(n[k]); unsigned long co = checks;
        int b = prime_6k(n[k]);       unsigned long cr = checks;
        printf("%9lu %-9s | %9lu %9lu %9lu | %.3f%s\n", n[k], a ? "prime" : "not prime",
               co, cr, pred[k], co ? (double)cr / co : 0.0, a != b ? "  MISMATCH!" : "");
    }

    puts("\n=== E. Batch validation: every n in 0 .. 1,000,003 ===");
    unsigned long N = 1000003, tot_o = 0, tot_r = 0, mism = 0, pc = 0, worse = 0, same = 0, better = 0;
    clock_t t0 = clock();
    for (unsigned long x = 0; x <= N; x++) { prime_original(x); tot_o += checks; }
    double to = (double)(clock() - t0) / CLOCKS_PER_SEC;
    t0 = clock();
    for (unsigned long x = 0; x <= N; x++) { prime_6k(x); tot_r += checks; }
    double tr = (double)(clock() - t0) / CLOCKS_PER_SEC;
    for (unsigned long x = 0; x <= N; x++) {
        int a = prime_original(x); unsigned long co = checks;
        int b = prime_6k(x);       unsigned long cr = checks;
        if (a != b) mism++;
        if (a) pc++;
        if (cr > co) worse++; else if (cr == co) same++; else better++;
    }
    printf("  answers that differ between the two programs : %lu  (primes found: %lu)\n", mism, pc);
    printf("  total divisions  original = %lu , redesign = %lu , ratio = %.3f (%.1f%% fewer)\n",
           tot_o, tot_r, (double)tot_r / tot_o, 100.0 * (1.0 - (double)tot_r / tot_o));
    printf("  CPU time (this run, varies)  original = %.3f s , redesign = %.3f s\n", to, tr);
    printf("  per-n comparison: redesign cheaper for %lu values, equal for %lu, MORE expensive for %lu\n", better, same, worse);

    puts("\n=== F. Where the original is still preferable (small n) ===");
    unsigned long w100 = 0, w1000 = 0, firstw[5], nf = 0;
    for (unsigned long x = 0; x <= 1000; x++) {
        prime_original(x); unsigned long co = checks;
        prime_6k(x);       unsigned long cr = checks;
        if (cr > co) { if (x <= 100) w100++; w1000++; if (nf < 5) firstw[nf++] = x; }
    }
    printf("  n <= 100 : redesign needs MORE divisions for %lu values;  n <= 1000 : %lu values\n", w100, w1000);
    printf("  first such n: ");
    for (unsigned long q = 0; q < nf; q++) printf("%lu ", firstw[q]);
    puts("(small primes: the two fixed tests 2 and 3 cost more than the loop saves)");
    return 0;
}
