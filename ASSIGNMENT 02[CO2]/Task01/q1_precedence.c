/* Q1 - Precedence, associativity and the discount bug (Jan Aushadhi billing)
 * *
 * PREDICTIONS (written BEFORE running; ints, left-to-right for * and /):
 *   Bill A: price=120 qty=10 senior=1
 *     ((120*10)*15)/100 = 18000/100 = 180 ; *senior -> 180 ; (1200*5)/100 = 60
 *     total = 1200 - 180 + 60 = 1080  -> net = 1080 > 1000 ? 1030
 *   Bill B: price=45 qty=7 senior=0
 *     315*15/100*0 = 0 ; 315*5/100 = 1575/100 = 15 (15.75 truncated)
 *     total = 315 - 0 + 15 = 330      -> net = 330
 *   Bill C: price=333 qty=3 senior=1
 *     999*15/100 = 14985/100 = 149 (149.85 truncated) ; 999*5/100 = 49 (49.95)
 *     total = 999 - 149 + 49 = 899    -> net = 899
 * INTENDED (pharmacist) = (gross - 15% senior discount) then +5% GST on the
 *   discounted amount, then Rs 50 off if the final bill is above Rs 1000:
 *     A: 1200 -> 1020 -> 1071.00 -> 1021.00
 *     B: 315  -> 315  -> 330.75   -> 330.75
 *     C: 999  -> 849.15 -> 891.6075 -> 891.61
 */
#include <stdio.h>

struct bill { int price, qty, senior; int pred_total, pred_net; };

int main(void)
{
    struct bill b[3] = {
        {120, 10, 1, 1080, 1030},
        { 45,  7, 0,  330,  330},
        {333,  3, 1,  899,  899}
    };

    printf("%-6s %5s %3s %3s | %-24s | %-27s | %s\n", "Bill", "price", "qty",
           "sen", "BUGGY total/net (pred)", "BUGGY total/net (observed)",
           "INTENDED total / net");
    for (int i = 0; i < 3; i++) {
        int price = b[i].price, qty = b[i].qty, senior = b[i].senior;
        int total, net;

        /* ---- original buggy statements, exactly as given ---- */
        total = price * qty - price * qty * 15 / 100 * senior + price * qty * 5 / 100;
        net = total > 1000 ? total - 50 : total;

        /* ---- corrected: intermediate variables + double ---- */
        double gross    = (double)price * qty;
        double discount = senior ? gross * 15.0 / 100.0 : 0.0;
        double taxable  = gross - discount;
        double gst      = taxable * 5.0 / 100.0;
        double payable  = taxable + gst;
        double fnet     = payable > 1000.0 ? payable - 50.0 : payable;

        printf("%-6c %5d %3d %3d | pred %4d / %-4d          | obs %4d / %-4d %-12s | %8.2f / %8.2f\n",
               'A' + i, price, qty, senior, b[i].pred_total, b[i].pred_net,
               total, net,
               (total == b[i].pred_total && net == b[i].pred_net) ? "[MATCH]" : "[MISMATCH]",
               payable, fnet);
        printf("       gross=%.2f discount=%.2f taxable=%.2f gst=%.2f | error of buggy total = %+.2f\n",
               gross, discount, taxable, gst, total - payable);
    }

    /* ---- third statement: count = count++ + 1;  (undefined behaviour) ---- */
    int count = 5;
    count = count++ + 1;      /* modifies 'count' twice without a sequence point */
    printf("\ncount = 5; count = count++ + 1;  ->  count = %d   (UB: any value is allowed;\n"
           "this compiler happens to give 6, a different compiler could give 7 or crash)\n", count);
    return 0;
}
