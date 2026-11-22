/* Q2 EXTRA: short-circuit truth table and function-call counting */
#include <stdio.h>
int calls;
int check(int x){calls++; return x;}
int main(void){
    puts("A B | A&&B calls | A||B calls");
    for(int a=0;a<=1;a++) for(int b=0;b<=1;b++){
        calls=0; int andv=check(a)&&check(b); int andcalls=calls;
        calls=0; int orv=check(a)||check(b); int orcalls=calls;
        printf("%d %d | %d (%d) | %d (%d)\n",a,b,andv,andcalls,orv,orcalls);
    }
    puts("Observation: && skips RHS when A=0; || skips RHS when A=1.");
    return 0;
}