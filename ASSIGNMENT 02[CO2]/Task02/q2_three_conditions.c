/* Q2 (extra) - Ordering THREE conditions joined by ||  (cost-aware short-circuit)
 * *
 * Conditions (grant concession if ANY is true):
 *   A  senior citizen on a valid class    cost  1   P(true) = 0.30
 *   B  disability card shown at counter   cost 10   P(true) = 0.10
 *   C  server verification (slow)         cost 100  P(true) = 0.05
 * Rule: for  X || Y || Z  evaluate in ascending cost/P(true).
 *   A: 1/0.30 = 3.3   B: 10/0.10 = 100   C: 100/0.05 = 2000
 * PREDICTION (before running): best order is A,B,C ; worst is C,B,A.
 *   expected cost per passenger of A,B,C = 1 + 0.7*10 + 0.7*0.9*100 = 71.0
 */
#include <stdio.h>

#define N 20000
static const double cost[3] = {1, 10, 100};
static const int    pct[3]  = {30, 10, 5};
static int val[N][3];
static unsigned long calls[3];

static unsigned long seed = 99;
static int rnd(void) { seed = seed * 6364136223846793005UL + 1442695040888963407UL; return (int)((seed >> 33) % 100); }

static int test(int i, int which) { calls[which]++; return val[i][which]; }

int main(void)
{
    for (int i = 0; i < N; i++) for (int k = 0; k < 3; k++) val[i][k] = rnd() < pct[k];
    int perm[6][3] = {{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}};
    const char *nm = "ABC";
    puts("order | calls A      calls B      calls C   | total cost  | cost/passenger | granted");
    double best = 1e18, worst = 0; int bi = 0, wi = 0;
    for (int p = 0; p < 6; p++) {
        calls[0] = calls[1] = calls[2] = 0; int granted = 0;
        for (int i = 0; i < N; i++)
            granted += test(i, perm[p][0]) || test(i, perm[p][1]) || test(i, perm[p][2]);
        double total = 0; for (int k = 0; k < 3; k++) total += calls[k] * cost[k];
        printf(" %c,%c,%c | %8lu %12lu %12lu | %11.0f | %14.2f | %d\n", nm[perm[p][0]], nm[perm[p][1]], nm[perm[p][2]],
               calls[0], calls[1], calls[2], total, total / N, granted);
        if (total < best) { best = total; bi = p; }
        if (total > worst) { worst = total; wi = p; }
    }
    printf("best order  : %c,%c,%c (cost/passenger %.2f; prediction 71.00 for A,B,C)\n", nm[perm[bi][0]], nm[perm[bi][1]], nm[perm[bi][2]], best / N);
    printf("worst order : %c,%c,%c (cost/passenger %.2f) -> %.1fx the best\n", nm[perm[wi][0]], nm[perm[wi][1]], nm[perm[wi][2]], worst / N, worst / best);
    puts("granted is identical for every order: reordering a side-effect-free || never changes the answer, only the cost.");
    return 0;
}
