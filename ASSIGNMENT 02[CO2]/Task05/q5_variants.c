/* Q5 - Loop versions, counts, do-while care, overflow, sieve alternative
 * *
 * Student-derived condition: if n = a*b with a <= b then a*a <= a*b = n, so the
 * smaller factor is always <= sqrt(n).  Hence loop only while i*i <= n  (no sqrt()).
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static unsigned long checks;

int prime_naive(unsigned long n)          /* for, 2 .. n-1 */
{
    checks = 0; if (n < 2) return 0;
    for (unsigned long i = 2; i < n; i++) { checks++; if (n % i == 0) return 0; }
    return 1;
}
int prime_for(unsigned long n)            /* for, i*i <= n */
{
    checks = 0; if (n < 2) return 0;
    for (unsigned long i = 2; i * i <= n; i++) { checks++; if (n % i == 0) return 0; }
    return 1;
}
int prime_while(unsigned long n)          /* while, i*i <= n */
{
    checks = 0; if (n < 2) return 0;
    unsigned long i = 2;
    while (i * i <= n) { checks++; if (n % i == 0) return 0; i++; }
    return 1;
}
int prime_dowhile_bad(unsigned long n)    /* do-while WITHOUT guard: body runs once before the test */
{
    checks = 0; if (n < 2) return 0;
    unsigned long i = 2;
    do { checks++; if (n % i == 0) return 0; i++; } while (i * i <= n);
    return 1;
}
int prime_dowhile(unsigned long n)        /* do-while WITH guard for n = 2, 3 */
{
    checks = 0; if (n < 2) return 0;
    if (n < 4) return 1;                  /* 2 and 3: 2*2 > n, loop must not run at all */
    unsigned long i = 2;
    do { checks++; if (n % i == 0) return 0; i++; } while (i * i <= n);
    return 1;
}

int main(void)
{
    puts("=== Division counts (checks) for each version ===");
    printf("%9s %-9s | %10s %8s %8s %9s %10s\n", "n", "result", "for 2..n-1", "for i*i", "while", "do-while", "do-w (bad)");
    unsigned long t[] = {2, 3, 97, 100, 7919, 1000003, 999983, 1000001};
    for (int k = 0; k < 8; k++) {
        unsigned long n = t[k];
        int p = prime_naive(n);            unsigned long c0 = checks;
        int p1 = prime_for(n);             unsigned long c1 = checks;
        int p2 = prime_while(n);           unsigned long c2 = checks;
        int p3 = prime_dowhile(n);         unsigned long c3 = checks;
        int p4 = prime_dowhile_bad(n);     unsigned long c4 = checks;
        printf("%9lu %-9s | %10lu %8lu %8lu %9lu %10lu%s\n", n, p ? "prime" : "not prime",
               c0, c1, c2, c3, c4, (p1 == p && p2 == p && p3 == p) ? "" : "  MISMATCH");
        if (p4 != p) printf("%9s   ^ unguarded do-while says %s for %lu : WRONG\n", "", p4 ? "prime" : "not prime", n);
    }

    puts("\n=== Why do-while needs care for n = 2 and n = 3 ===");
    int r2 = prime_dowhile_bad(2); unsigned long c2b = checks;
    printf("  n=2 unguarded: tests 2 %% 2 == 0 first -> result %s (WRONG, 2 is prime), checks=%lu\n",
           r2 ? "prime" : "NOT prime", c2b);
    int r3 = prime_dowhile_bad(3); unsigned long c3b = checks;
    printf("  n=3 unguarded: result %s but performs %lu useless division(s) although 2*2 > 3\n",
           r3 ? "prime" : "not prime", c3b);

    puts("\n=== Why i * i <= n can overflow ===");
    uint32_t n32 = 4294967291u;            /* largest 32-bit prime */
    for (uint32_t i32 = 65535; i32 <= 65537; i32++) {
        uint32_t sq = i32 * i32;           /* wraps modulo 2^32 */
        int computed = (sq <= n32);
        int correct  = ((unsigned long long)i32 * i32 <= n32);
        printf("  32-bit: i=%u  i*i computed = %u  (true %llu)  loop test computed=%d correct=%d%s\n",
               i32, sq, (unsigned long long)i32 * i32, computed, correct,
               computed != correct ? "   <-- WRONG: loop would not stop" : "");
    }
    unsigned long i64 = 4294967296UL;     /* 2^32 */
    printf("  64-bit: i=2^32 -> i*i = %lu (wraps to 0) so i*i <= n is true again for any n\n", i64 * i64);
    puts("  safe form: while (i <= n / i)   (no multiplication, cannot overflow)");

    puts("\n=== Changing the condition to i < n (naive) -- tickets from the TODO program ===");
    unsigned long tk[] = {97, 100, 7919, 1000003};
    for (int k = 0; k < 4; k++) {
        int p = prime_naive(tk[k]);
        printf("%8lu %-9s divisions = %lu\n", tk[k], p ? "prime" : "not prime", checks);
    }

    puts("\n=== Alternative: Sieve of Eratosthenes up to N = 1,000,003 ===");
    unsigned long N = 1000003, trial_total = 0, naive_total = 0, primes_trial = 0;
    for (unsigned long n = 0; n <= N; n++) {
        if (prime_for(n)) primes_trial++;
        trial_total += checks;
    }
    for (unsigned long n = 0; n <= 20000; n++) { prime_naive(n); naive_total += checks; }
    unsigned char *composite = calloc(N + 1, 1);
    unsigned long sieve_ops = 0, primes_sieve = 0;
    for (unsigned long p = 2; p * p <= N; p++)
        if (!composite[p])
            for (unsigned long m = p * p; m <= N; m += p) { composite[m] = 1; sieve_ops++; }
    for (unsigned long n = 2; n <= N; n++) if (!composite[n]) primes_sieve++;
    printf("  trial division (i*i<=n), all n <= N : %lu divisions, primes found = %lu\n", trial_total, primes_trial);
    printf("  naive 2..n-1 for all n <= 20000 only: %lu divisions\n", naive_total);
    printf("  sieve, one pass                      : %lu marking operations, primes found = %lu, extra memory = %lu bytes\n",
           sieve_ops, primes_sieve, N + 1);
    printf("  per query afterwards: sieve = 1 array lookup, trial = up to %lu divisions\n", 999UL);
    free(composite);
    return 0;
}
