/* Q6 (extra) - More loan scenarios, integer-paise version, while vs do-while, balance-sheet check
 * *
 * HAND ESTIMATES of months, n = ceil( -ln(1 - r*P/E) / ln(1+r) )   (written before running)
 *   S1  P=50000  r=1.5%  E=3000 : x=0.25    -> 0.2877/0.01489 = 19.3  -> 20 months
 *   S2  P=5000   r=3%    E=500  : x=0.30    -> 0.3567/0.02956 = 12.1  -> 13 months
 *   S3  P=20000  r=1%    E=1000 : x=0.20    -> 0.2231/0.00995 = 22.4  -> 23 months
 *   S4  P=100000 r=1%    E=1000 : E = interest of month 1 -> NEVER (balance stays 100000)
 *   S5  P=100000 r=1%    E=1100 : x=0.909   -> 2.398/0.00995  = 241.0 -> about 241 months
 * Integer-paise model: rate in basis points, interest rounded half-up to a paisa every month.
 */
#include <stdio.h>
#include <math.h>

#define EPS 0.005

static int sim_double(double P, double r, double E, int limit, double *tint, double *tpaid)
{
    double bal = P; int m = 0; *tint = 0; *tpaid = 0;
    while (bal > EPS && m < limit) {
        double i = bal * r; bal += i; *tint += i;
        double pay = bal < E ? bal : E; bal -= pay; *tpaid += pay; m++;
    }
    return bal > EPS ? -1 : m;
}

static int sim_paise(long P_p, long r_bp, long E_p, int limit, long *tint_p)
{
    long bal = P_p; int m = 0; *tint_p = 0;
    while (bal > 0 && m < limit) {
        long i = (bal * r_bp + 5000) / 10000;           /* round half up, all integers */
        bal += i; *tint_p += i;
        long pay = bal < E_p ? bal : E_p; bal -= pay; m++;
    }
    return bal > 0 ? -1 : m;
}

int main(void)
{
    struct { const char *id; double P, rpct, E; int hand; } s[] = {
        {"S1", 50000, 1.5, 3000, 20}, {"S2", 5000, 3.0, 500, 13}, {"S3", 20000, 1.0, 1000, 23},
        {"S4", 100000, 1.0, 1000, -1}, {"S5", 100000, 1.0, 1100, 241}
    };
    puts("=== A. Scenarios: hand estimate vs double simulation vs integer-paise simulation ===");
    puts("id    P        rate  repay  | hand | double months  total interest | paise months  total interest | paid-P-int");
    for (int k = 0; k < 5; k++) {
        double ti, tp; long tip;
        int md = sim_double(s[k].P, s[k].rpct / 100.0, s[k].E, 2000, &ti, &tp);
        int mp = sim_paise((long)(s[k].P * 100), (long)(s[k].rpct * 100 + 0.5), (long)(s[k].E * 100), 2000, &tip);
        if (md < 0) {
            printf("%-3s %8.0f %4.1f%% %6.0f | never|  NO REPAYMENT (limit 2000 reached)   | NO REPAYMENT (limit 2000 reached)\n",
                   s[k].id, s[k].P, s[k].rpct, s[k].E);
            continue;
        }
        printf("%-3s %8.0f %4.1f%% %6.0f | %4d | %8d %16.2f | %8d %17.2f | %+.1e%s\n", s[k].id, s[k].P, s[k].rpct, s[k].E,
               s[k].hand, md, ti, mp, tip / 100.0, tp - s[k].P - ti, md == s[k].hand ? "" : "  (hand estimate off)");
    }

    puts("\n=== B. while vs do-while when the loan amount is 0 ===");
    double P = 0, r = 0.02, E = 2000, bal;
    int mw = 0, md2 = 0;
    bal = P; while (bal > EPS) { bal += bal * r; double pay = bal < E ? bal : E; bal -= pay; mw++; }
    bal = P; do { bal += bal * r; double pay = bal < E ? bal : E; bal -= pay; md2++; } while (bal > EPS);
    printf("  P = 0 : while reports %d months (correct) ; do-while reports %d month(s) (a phantom installment)\n", mw, md2);
    puts("  => while (pre-test) is the right loop: a loan may already be fully repaid before the first month.");

    puts("\n=== C. Last-payment rule: what if we always charge a full EMI? ===");
    double b = 10000, tot_over = 0; int m = 0;
    while (b > EPS && m < 360) { b += b * 0.02; b -= 2000; m++; if (b < 0) { tot_over = -b; break; } }
    printf("  Rs 10000, 2%%, EMI 2000 without the 'pay only the balance' rule: ends at month %d with balance %.2f (overpaid Rs %.2f)\n", m, b, tot_over);
    return 0;
}
