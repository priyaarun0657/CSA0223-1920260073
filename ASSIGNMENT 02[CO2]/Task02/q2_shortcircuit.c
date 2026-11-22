/* Q2 - When does short-circuit evaluation matter? (Railway concession)
 * *
 * Concession rule:  (senior AND eligible_class)  OR  disability_card_valid
 * verify_card() is the SLOW server call; every call is counted and logged.
 *
 * PREDICTIONS (before running): for N = 1000 passengers
 *   V1  (senior && eligible) || verify()   -> verify() only when left side is false
 *   V2  verify() || (senior && eligible)   -> verify() for every passenger = 1000
 *   V3  nested if (same order as V1)       -> same count as V1
 *   V4  (senior & eligible) | verify()     -> non-short-circuit, 1000 calls
 */
#include <stdio.h>

#define N 1000

static unsigned long calls = 0;      /* number of slow calls */
static unsigned long audit_log = 0;  /* passengers recorded in the audit log */

struct pax { int senior, eligible, card; };

static unsigned long seed = 12345;
static int rnd_pct(void)             /* deterministic LCG so results repeat */
{
    seed = seed * 1103515245UL + 12345UL;
    return (int)((seed >> 16) % 100);
}

static int verify_card(const struct pax *p)   /* the slow server check */
{
    calls++;
    audit_log++;                              /* Changed Condition: audit logging */
    return p->card;
}

static int v1(const struct pax *p) { return (p->senior && p->eligible) || verify_card(p); }
static int v2(const struct pax *p) { return verify_card(p) || (p->senior && p->eligible); }
static int v3(const struct pax *p)
{
    if (p->senior) { if (p->eligible) return 1; }
    return verify_card(p) ? 1 : 0;
}
static int v4(const struct pax *p) { return ((p->senior & p->eligible) | verify_card(p)) != 0; }

/* helper with visible side effect for experiment 1 */
static int trace(const char *name, int value) { printf("    %s evaluated -> %d\n", name, value); return value; }

static void generate(struct pax *a, int pct_senior, int pct_elig, int pct_card)
{
    seed = 12345;
    for (int i = 0; i < N; i++) {
        a[i].senior   = rnd_pct() < pct_senior;
        a[i].eligible = rnd_pct() < pct_elig;
        a[i].card     = rnd_pct() < pct_card;
    }
}

static unsigned long run(int (*f)(const struct pax *), const struct pax *a, int *granted)
{
    calls = 0; audit_log = 0; *granted = 0;
    for (int i = 0; i < N; i++) *granted += f(&a[i]);
    return calls;
}

int main(void)
{
    puts("=== Experiment 1: is the second operand evaluated? ===");
    puts("  0 && f():");  int r = trace("A", 0) && trace("B", 1);   printf("    result=%d (B skipped)\n", r);
    puts("  1 && f():");  r = trace("A", 1) && trace("B", 1);       printf("    result=%d (B evaluated)\n", r);
    puts("  1 || f():");  r = trace("A", 1) || trace("B", 0);       printf("    result=%d (B skipped)\n", r);
    puts("  0 || f():");  r = trace("A", 0) || trace("B", 0);       printf("    result=%d (B evaluated)\n", r);
    puts("  0 & f()  (bitwise, NO short-circuit):"); r = trace("A", 0) & trace("B", 1);
    printf("    result=%d (B evaluated even though A is 0)\n", r);
    printf("  Value difference on non-boolean operands: 1 && 2 = %d , 1 & 2 = %d\n\n", 1 && 2, 1 & 2);

    static struct pax a[N];
    int g;

    puts("=== Experiment 2: slow-function calls for 1000 passengers ===");
    puts("  population: 20% senior, 50% eligible class, 10% card holders");
    generate(a, 20, 50, 10);
    /* NOTE: run() is called in its own statement; printf argument evaluation
       order is unspecified in C, so run(...) and g must not share one call. */
    const char *names[4] = {"V1 (senior&&elig)||verify", "V2 verify||(senior&&elig)",
                            "V3 nested if (V1 order)  ", "V4 (senior&elig)|verify   "};
    int (*fn[4])(const struct pax *) = {v1, v2, v3, v4};
    for (int k = 0; k < 4; k++) {
        unsigned long c = run(fn[k], a, &g);
        printf("  %s : calls=%4lu  granted=%d\n", names[k], c, g);
    }
    puts("");

    puts("=== Experiment 3: effect of how often the cheap test is true ===");
    puts("  %senior %elig | P(cheap true) | calls V1 | calls V2 | saved by order");
    int sen[] = {5, 20, 50, 90}, el[] = {50, 50, 50, 90};
    for (int k = 0; k < 4; k++) {
        generate(a, sen[k], el[k], 10);
        unsigned long c1 = run(v1, a, &g), c2 = run(v2, a, &g);
        printf("  %6d %5d | %12.2f%% | %8lu | %8lu | %lu\n", sen[k], el[k],
               sen[k] * el[k] / 100.0, c1, c2, c2 - c1);
    }

    puts("\n=== Changed condition: verify_card() now writes an audit log ===");
    generate(a, 20, 50, 10);
    run(v1, a, &g); printf("  V1 audit-log entries = %lu of %d passengers (short-circuit skips the rest)\n", audit_log, N);
    run(v2, a, &g); printf("  V2 audit-log entries = %lu of %d passengers (every passenger logged)\n", audit_log, N);
    run(v4, a, &g); printf("  V4 audit-log entries = %lu of %d passengers (every passenger logged)\n", audit_log, N);
    return 0;
}
