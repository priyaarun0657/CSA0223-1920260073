#include <stdio.h>
long long calls;
long long linear(long long b,int n){calls++;if(n==0)return 1;return b*linear(b,n-1);}
long long fast(long long b,int n){calls++;if(n==0)return 1;long long h=fast(b,n/2);return n%2?b*h*h:h*h;}
int main(void){calls=0;printf("linear 2^10=%lld calls=%lld\n",linear(2,10),calls);calls=0;long long x=fast(2,10);printf("fast 2^10=%lld calls=%lld\n",x,calls);return 0;}
