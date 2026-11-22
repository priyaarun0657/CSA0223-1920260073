/* Q1 EXTRA: Arithmetic precedence and billing test cases */
#include <stdio.h>
int main(void) {
    struct Test { int price, qty, senior; } t[]={{120,10,1},{45,7,0},{333,3,1},{999,1,0},{250,4,1}};
    puts("CASE | gross | discount | GST | final");
    for(int i=0;i<5;i++){
        double gross=(double)t[i].price*t[i].qty;
        double discount=t[i].senior?gross*0.15:0.0;
        double taxable=gross-discount, gst=taxable*0.05, final=taxable+gst;
        printf("%4d | %6.2f | %8.2f | %6.2f | %7.2f\n",i+1,gross,discount,gst,final);
    }
    puts("\nTest: quantity=0 produces zero; senior=0 produces no discount.");
    return 0;
}