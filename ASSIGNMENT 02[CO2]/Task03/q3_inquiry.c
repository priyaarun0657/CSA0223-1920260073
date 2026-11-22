/* Q3 Inquiry + Alternative concept (array of 8 bytes vs one byte)
 * */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define HOMES 1000000

/* count devices that are ON using only bitwise operators: reg &= reg - 1 clears the lowest set bit */
static int count_on(unsigned char reg)
{
    int n = 0;
    while (reg) { reg &= reg - 1; n++; }
    return n;
}

static void bin(unsigned char r) { for (int b = 7; b >= 0; b--) putchar(((r >> b) & 1u) ? '1' : '0'); }

int main(void)
{
    puts("=== Counting devices ON (bitwise only: reg &= reg - 1) ===");
    printf("  register 00000110 (value 6) -> %d devices ON ; register 11111111 -> %d ; register 0 -> %d\n\n",
           count_on(6), count_on(0xFF), count_on(0));

    puts("=== Inquiry 1: reg & 1 << dev   vs   (reg & 1) << dev ===");
    puts("Precedence: << binds tighter than &, so  reg & 1 << dev  ==  reg & (1 << dev)");
    unsigned char reg = 6;  int dev = 2;      /* reg = 00000110, test device 2 (AC) */
    printf("reg=%d (", reg); bin(reg); printf("), dev=%d\n", dev);
    printf("  reg & 1 << dev     = %d   (mask test: bit 2 of reg -> value 4 = ON, but not 1!)\n", reg & 1 << dev);
    printf("  (reg & 1) << dev   = %d   (tests bit 0 (LIGHT) then shifts it -> WRONG device)\n", (reg & 1) << dev);
    printf("  (reg >> dev) & 1   = %d   (correct, returns exactly 0 or 1)\n\n", (reg >> dev) & 1);

    puts("=== Inquiry 2: signed char with bit 7 set ===");
    signed char sc = (signed char)0x80;       /* implementation-defined conversion: -128 */
    unsigned char uc = 0x80;
    printf("  signed char  sc = 0x80 -> value %d ; sc promoted to int = 0x%08X\n", sc, (unsigned)(int)sc);
    printf("  unsigned char uc = 0x80 -> value %d ; uc promoted to int = 0x%08X\n", uc, (unsigned)(int)uc);
    printf("  sc >> 1 = %d  (sign extension: arithmetic shift, implementation-defined)\n", sc >> 1);
    printf("  uc >> 1 = %d  (logical: 01000000)\n", uc >> 1);
    printf("  (sc >> 7) & 1 = %d, but sc >> 7 = %d (all ones) if the '& 1' is forgotten\n", (sc >> 7) & 1, sc >> 7);
    printf("  sc == 0x80 ? %s   uc == 0x80 ? %s   (-128 != 128 after promotion)\n\n",
           sc == 0x80 ? "true" : "false", uc == 0x80 ? "true" : "false");

    puts("=== Alternative: char state[8] (1 byte/device) vs 1 byte register ===");
    unsigned char *bits  = malloc(HOMES);
    unsigned char *array = malloc((size_t)HOMES * 8);
    srand(7);
    for (int h = 0; h < HOMES; h++) {
        bits[h] = (unsigned char)(rand() & 0xFF);
        for (int d = 0; d < 8; d++) array[(size_t)h * 8 + d] = (bits[h] >> d) & 1;
    }
    printf("  memory for %d homes : bit-register = %d bytes (%.1f MB), array = %d bytes (%.1f MB)\n",
           HOMES, HOMES, HOMES / 1e6, HOMES * 8, HOMES * 8 / 1e6);

    long total_bits = 0, total_arr = 0, ops_bits = 0, ops_arr = 0;
    clock_t t0 = clock();
    for (int h = 0; h < HOMES; h++) { unsigned char r = bits[h]; while (r) { r &= r - 1; total_bits++; ops_bits++; } }
    double tb = (double)(clock() - t0) / CLOCKS_PER_SEC;
    t0 = clock();
    for (int h = 0; h < HOMES; h++) for (int d = 0; d < 8; d++) { total_arr += array[(size_t)h * 8 + d]; ops_arr++; }
    double ta = (double)(clock() - t0) / CLOCKS_PER_SEC;
    printf("  count devices ON (all homes): bit-register = %ld ON, %ld loop iterations, %.4f s\n", total_bits, ops_bits, tb);
    printf("                                array        = %ld ON, %ld loop iterations, %.4f s\n", total_arr, ops_arr, ta);
    puts("  single set/clear/toggle/test: O(1) in both; counting ON devices: O(k) (k=ON bits <= 8) vs O(8)");
    free(bits); free(array);
    return 0;
}
