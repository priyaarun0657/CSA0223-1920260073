/* Q6 - Loops that must terminate: self-help-group micro-loan schedule
 * *
 * Loop choice: while.  A loan of 0 needs zero iterations, and the number of months is
 * not known in advance, so a pre-tested, condition-controlled loop (while) fits.
 * Termination: balance > EPS (half a paisa) -- NOT balance != 0 (floating point).
 * Last month: if balance (after interest) < EMI, pay only the balance.
 * Repayment <= interest: balance never falls -> refuse up front, plus a safety limit.
 *
 * HAND CALCULATION (Rs 10000, 2%/month, repay 2000):
 *  month interest   balance+int  paid    closing
 *    1   200.00     10200.00     2000    8200.00
 *    2   164.00      8364.00     2000    6364.00
 *    3   127.28      6491.28     2000    4491.28
 *    4    89.83      4581.11     2000    2581.11   (89.8256)
 *    5    51.62      2632.73     2000     632.73   (51.6221)
 *    6    12.65       645.38      645.38     0.00   (12.6546)  total interest = 645.38
 * Formula prediction: n = -ln(1 - 0.02*10000/2000) / ln(1.02) = 5.32 -> 6 months
 */
#include <stdio.h>
#include <math.h>

#define EPS 0.005

/* returns months taken, or -1 if the limit was reached; interest total via pointer */
int simulate(double P, double r, double E, int limit, int show, double *tot_int)
{
    double balance = P, total_interest = 0.0;
    int months = 0;
    if (show) printf("%5s %10s %12s %10s %10s\n", "month", "interest", "bal+int", "paid", "closing");
    while (balance > EPS && months < limit) {          /* termination condition */
        double interest = balance * r;
        balance += interest;
        total_interest += interest;
        double pay = (balance < E) ? balance : E;      /* last month: pay only what is left */
        balance -= pay;
        months++;
        if (show) printf("%5d %10.2f %12.2f %10.2f %10.2f\n", months, interest, balance + pay, pay, balance);
    }
    *tot_int = total_interest;
    return (balance > EPS) ? -1 : months;
}

int main(void)
{
    double P = 10000.0, r = 0.02, E = 2000.0, ti;

    puts("=== Correctness check: Rs 10000 @ 2%/month, repay Rs 2000 ===");
    int m = simulate(P, r, E, 360, 1, &ti);
    printf("months = %d, total interest = %.2f, total paid = %.2f\n", m, ti, P + ti);
    double hand_close[6] = {8200.00, 6364.00, 4491.28, 2581.11, 632.73, 0.00};
    double hand_int[6]   = {200.00, 164.00, 127.28, 89.83, 51.62, 12.65};
    double b = P, ok = 1; int mm = 0;
    while (b > EPS && mm < 6) {
        double i = b * r; b += i; double pay = b < E ? b : E; b -= pay;
        if (fabs(b - hand_close[mm]) > 0.006 || fabs(i - hand_int[mm]) > 0.006) ok = 0;
        mm++;
    }
    printf("hand-calculated schedule vs program (6 rows, tolerance 0.006): %s; hand total interest 645.38 vs %.2f\n",
           ok ? "ALL MATCH" : "MISMATCH", ti);

    puts("\n=== Why balance != 0 is dangerous (floating point) ===");
    double bal = 1.0, bal_at_10 = 0.0; int k = 0;
    while (bal != 0.0 && k < 12) {          /* the dangerous test; k<12 is only MY guard for the demo */
        bal -= 0.1; k++;
        if (k == 10) bal_at_10 = bal;
    }
    printf("1.0 minus 0.1 repeated: after exactly 10 subtractions balance = %.17g (not 0)\n", bal_at_10);
    printf("so 'while (bal != 0)' keeps going: %d iterations ran (stopped only by the k<12 guard), bal = %.3g\n", k, bal);

    puts("\n=== Growth investigation: months vs repayment (P=10000, r=2%, monthly interest at start = 200) ===");
    puts("  repay E | predicted n=ceil(-ln(1-rP/E)/ln(1+r)) | measured months | total interest");
    double Es[] = {5000, 2000, 1000, 500, 300, 250, 210, 205, 201, 200.5, 200.01, 200.0, 190.0};
    for (int j = 0; j < 13; j++) {
        double x = r * P / Es[j];
        int measured = simulate(P, r, Es[j], 5000, 0, &ti);
        if (x >= 1.0) {
            printf("  %7.2f | %-37s | %-15s | %s\n", Es[j], "never (rP/E >= 1)",
                   measured < 0 ? "limit 5000 hit" : "?", "grows without bound");
        } else {
            double pn = -log(1.0 - x) / log(1.0 + r);
            printf("  %7.2f | %8.2f -> %-24d | %-15d | %10.2f\n", Es[j], pn, (int)ceil(pn), measured, ti);
        }
    }

    puts("\n=== Deployment decision: safety limit of 360 months via break ===");
    double Ed[] = {2000.0, 190.0, 200.001};
    for (int j = 0; j < 3; j++) {
        double balance = P, tot = 0; int mo = 0, hit = 0;
        if (Ed[j] <= P * r) {          /* up-front test: repayment cannot even cover month-1 interest */
            printf("  repay %.3f : REFUSED - repayment must exceed the first month's interest Rs %.2f\n", Ed[j], P * r);
            continue;
        }
        for (;;) {
            if (balance <= EPS) break;
            if (mo >= 360) { hit = 1; break; }              /* safety limit */
            double interest = balance * r; balance += interest; tot += interest;
            double pay = balance < Ed[j] ? balance : Ed[j]; balance -= pay; mo++;
        }
        if (hit) printf("  repay %.3f : STOPPED at 360 months, Rs %.2f still owed - show 'increase EMI / extend tenure, manual review'\n", Ed[j], balance);
        else     printf("  repay %.3f : repaid in %d months, interest Rs %.2f\n", Ed[j], mo, tot);
    }
    return 0;
}
