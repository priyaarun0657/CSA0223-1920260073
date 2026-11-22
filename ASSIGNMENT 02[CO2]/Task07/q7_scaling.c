/* Q7 (extra) - Scaling study and a second candidate redesign (wheel mod 30)
 * *
 * PREDICTIONS (before running):
 *   6k+-1 : tests 2,3 + 2 of every 6 numbers  -> ratio to original -> 2/6 = 0.333 for large primes
 *   wheel30: tests 2,3,5 + the 8 residues {1,7,11,13,17,19,23,29} of every 30 -> 8/30 = 0.267
 *            e.g. n ~ 1,000,003 : about 3 + 266 = 269 divisions (original 999)
 *   Both ratios stay constant as n grows (all are O(sqrt n)); wheel30 loses on tiny n because of its 3 fixed tests.
 */
#include <stdio.h>

typedef unsigned long long u64;
static unsigned long long checks;

static int p_orig(u64 n) { checks = 0; if (n < 2) return 0; for (u64 i = 2; i * i <= n; i++) { checks++; if (n % i == 0) return 0; } return 1; }

static int p_6k(u64 n)
{
    checks = 0; if (n < 2) return 0; if (n < 4) return 1;
    checks++; if (n % 2 == 0) return 0;
    checks++; if (n % 3 == 0) return 0;
    for (u64 i = 5; i * i <= n; i += 6) { checks++; if (n % i == 0) return 0; checks++; if (n % (i + 2) == 0) return 0; }
    return 1;
}

static int p_w30(u64 n)
{
    static const int step[8] = {4, 2, 4, 2, 4, 6, 2, 6};     /* 7 -> 11 -> 13 -> 17 -> 19 -> 23 -> 29 -> 31 -> 37 */
    checks = 0; if (n < 2) return 0;
    if (n == 2 || n == 3 || n == 5) return 1;
    checks++; if (n % 2 == 0) return 0;
    checks++; if (n % 3 == 0) return 0;
    checks++; if (n % 5 == 0) return 0;
    u64 i = 7; int k = 0;
    while (i * i <= n) { checks++; if (n % i == 0) return 0; i += step[k]; k = (k + 1) & 7; }
    return 1;
}

int main(void)
{
    puts("=== Scaling: smallest prime >= 10^k ===");
    puts("   k  prime n            original    6k+-1  wheel30 | ratio 6k+-1  ratio wheel30");
    u64 pw = 1;
    for (int k = 1; k <= 12; k++) {
        pw *= 10;
        u64 n = pw; while (!p_6k(n)) n++;
        p_orig(n); u64 co = checks; p_6k(n); u64 c6 = checks; p_w30(n); u64 c3 = checks;
        printf(" %3d  %-16llu %9llu %8llu %8llu |   %.3f         %.3f\n", k, n, co, c6, c3, (double)c6 / co, (double)c3 / co);
    }

    puts("\n=== Validation: all n <= 2,000,000 ===");
    u64 to = 0, t6 = 0, t3 = 0, mism = 0, primes = 0;
    for (u64 n = 0; n <= 2000000; n++) {
        int a = p_orig(n); to += checks;
        int b = p_6k(n);   t6 += checks;
        int c = p_w30(n);  t3 += checks;
        if (a != b || a != c) mism++;
        primes += a;
    }
    printf("  primes found: %llu ; answer mismatches: %llu\n", primes, mism);
    printf("  total divisions: original %llu | 6k+-1 %llu (%.3f) | wheel30 %llu (%.3f)\n", to, t6, (double)t6 / to, t3, (double)t3 / to);
    puts("\n  wheel30 uses about 20% fewer divisions than 6k+-1 (ratio 0.267 vs 0.333), a constant factor at every size,");
    puts("  but needs a step table (8 ints) and 3 fixed tests. 6k+-1 is simpler and nearly as good.");
    puts("  Both stay O(sqrt n): neither changes how the work GROWS, only the constant in front.");
    return 0;
}
