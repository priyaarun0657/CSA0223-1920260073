#include <stdio.h>
int digital_root(int n){if(n<10)return n;int sum=0;while(n){sum+=n%10;n/=10;}return digital_root(sum);}
long long power_linear(long long b,int n){if(n==0)return 1;return b*power_linear(b,n-1);}
long long power_fast(long long b,int n){if(n==0)return 1;long long h=power_fast(b,n/2);return (n%2)?b*h*h:h*h;}
int main(void){printf("digital root 9875 = %d\n",digital_root(9875));printf("2^10 linear = %lld\n",power_linear(2,10));printf("2^10 fast = %lld\n",power_fast(2,10));return 0;}
