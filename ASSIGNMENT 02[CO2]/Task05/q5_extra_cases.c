/* Q5 EXTRA: prime tests, edge cases and count */
#include <stdio.h>
int is_prime(int n){if(n<2)return 0;if(n==2)return 1;if(n%2==0)return 0;for(int i=3;i<=n/i;i+=2)if(n%i==0)return 0;return 1;}
int main(void){
    int values[]={-5,0,1,2,3,4,9,25,29,97,100,101};
    puts("Number | Prime? | Explanation");
    for(int i=0;i<12;i++)printf("%6d | %s | %s\n",values[i],is_prime(values[i])?"YES":"NO",values[i]<2?"less than 2":is_prime(values[i])?"no divisor found":"composite/even");
    int count=0;for(int n=2;n<=100;n++)count+=is_prime(n);
    printf("\nPrimes from 2 to 100: %d\n",count);return 0;
}