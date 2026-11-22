/* Q3 (extra) - Verify the bit-register functions against a reference array model
 * * PREDICTION: 0 mismatches in (a) all 256 registers x 8 devices x 4 operations (8192 checks)
 *             and (b) 1,000,000 random operations; popcount of 0..255 sums to 1024 (8 * 128).
 */
#include <stdio.h>

unsigned char switch_on (unsigned char r, int d) { return r | (1u << d); }
unsigned char switch_off(unsigned char r, int d) { return r & ~(1u << d); }
unsigned char toggle    (unsigned char r, int d) { return r ^ (1u << d); }
int           is_on     (unsigned char r, int d) { return (r >> d) & 1u; }
int           count_on  (unsigned char r) { int n = 0; while (r) { r &= r - 1; n++; } return n; }

static void bin(unsigned char r) { for (int b = 7; b >= 0; b--) putchar(((r >> b) & 1u) ? '1' : '0'); }

int main(void)
{
    puts("=== (a) Exhaustive: every register 0..255, every device 0..7 ===");
    long checks = 0, bad = 0, popsum = 0;
    for (int r = 0; r < 256; r++) {
        int ref[8]; for (int d = 0; d < 8; d++) ref[d] = (r >> d) & 1;      /* array model */
        int pc = 0; for (int d = 0; d < 8; d++) pc += ref[d];
        if (count_on((unsigned char)r) != pc) bad++;
        popsum += pc;
        for (int d = 0; d < 8; d++) {
            int on_ok  = is_on(switch_on((unsigned char)r, d), d) == 1;
            int off_ok = is_on(switch_off((unsigned char)r, d), d) == 0;
            int tog_ok = is_on(toggle((unsigned char)r, d), d) == !ref[d];
            int test_ok = is_on((unsigned char)r, d) == ref[d];
            /* other bits must be untouched */
            int keep = 1;
            for (int e = 0; e < 8; e++) if (e != d) {
                if (is_on(switch_on((unsigned char)r, d), e) != ref[e]) keep = 0;
                if (is_on(switch_off((unsigned char)r, d), e) != ref[e]) keep = 0;
                if (is_on(toggle((unsigned char)r, d), e) != ref[e]) keep = 0;
            }
            checks += 4; bad += !on_ok + !off_ok + !tog_ok + !test_ok + !keep;
        }
    }
    printf("  %ld checks, %ld failures; sum of popcounts over 0..255 = %ld (predicted 1024)\n\n", checks, bad, popsum);

    puts("=== (b) 1,000,000 random operations: register vs 8-element array ===");
    unsigned char reg = 0; int arr[8] = {0};
    unsigned long s = 2024; long mism = 0;
    for (long i = 0; i < 1000000; i++) {
        s = s * 6364136223846793005UL + 1442695040888963407UL;
        int op = (int)((s >> 33) & 3), d = (int)((s >> 40) & 7);
        if (op == 0) { reg = switch_on(reg, d);  arr[d] = 1; }
        if (op == 1) { reg = switch_off(reg, d); arr[d] = 0; }
        if (op == 2) { reg = toggle(reg, d);     arr[d] = !arr[d]; }
        int n = 0; for (int e = 0; e < 8; e++) { if (is_on(reg, e) != arr[e]) mism++; n += arr[e]; }
        if (count_on(reg) != n) mism++;
    }
    printf("  mismatches after 1,000,000 operations: %ld ; final register = ", mism); bin(reg); puts("");

    puts("\n=== (c) Longer predicted sequence incl. device 7 (bit 7, unsigned char) ===");
    struct { const char *step; const char *pred; } plan[] = {
        {"on(7)",        "10000000"}, {"on(0)", "10000001"}, {"toggle(7)", "00000001"},
        {"toggle(4)",    "00010001"}, {"off(0)", "00010000"}, {"on(7), on(3)", "10011000"} };
    reg = 0; int okc = 0;
    reg = switch_on(reg, 7);                         printf("  %-12s predicted %s observed ", plan[0].step, plan[0].pred); bin(reg); okc += 1; puts("");
    reg = switch_on(reg, 0);                         printf("  %-12s predicted %s observed ", plan[1].step, plan[1].pred); bin(reg); puts("");
    reg = toggle(reg, 7);                            printf("  %-12s predicted %s observed ", plan[2].step, plan[2].pred); bin(reg); puts("");
    reg = toggle(reg, 4);                            printf("  %-12s predicted %s observed ", plan[3].step, plan[3].pred); bin(reg); puts("");
    reg = switch_off(reg, 0);                        printf("  %-12s predicted %s observed ", plan[4].step, plan[4].pred); bin(reg); puts("");
    reg = switch_on(switch_on(reg, 7), 3);           printf("  %-12s predicted %s observed ", plan[5].step, plan[5].pred); bin(reg); puts("");
    (void)okc;
    return 0;
}
