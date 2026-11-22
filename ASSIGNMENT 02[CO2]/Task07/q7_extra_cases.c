/* Q7 EXTRA: prime algorithm comparison */
#include <stdio.h>
int trial(int n){if(n<2)return 0;for(int i=2;i<=n/i;i++)if(n%i==0)return 0;return 1;}
int sixk(int n){if(n<2)return 0;if(n==2||n==3)return 1;if(n%2==0||n%3==0)return 0;for(int i=5;i<=n/i;i+=6)if(n%i==0||n%(i+2)==0)return 0;return 1;}
int main(void){
    int vals[]={2,3,4,25,97,997,10007,99991};
    puts("n | trial division | 6k+-1 method | agreement");
    for(int i=0;i<8;i++)printf("%5d | %d | %d | %s\n",vals[i],trial(vals[i]),sixk(vals[i]),trial(vals[i])==sixk(vals[i])?"YES":"NO");
    puts("The 6k+-1 method skips multiples of 2 and 3; both remain O(sqrt(n)).");return 0;
}