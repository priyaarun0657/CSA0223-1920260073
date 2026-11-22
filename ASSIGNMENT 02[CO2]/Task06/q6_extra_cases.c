/* Q6 EXTRA: loan repayment edge cases */
#include <stdio.h>
#define EPS 0.005
int main(void){
    struct Loan{double p,r,emi;};
    struct Loan t[]={{0,0.02,1000},{10000,0.02,2000},{10000,0.02,200},{5000,0,1000}};
    puts("Loan | monthly rate | EMI | months | status");
    for(int k=0;k<4;k++){
        double b=t[k].p;int m=0;
        if(b<=EPS){printf("%4.0f | %5.2f%% | %4.0f | %2d | already settled\n",t[k].p,t[k].r*100,t[k].emi,0);continue;}
        if(t[k].emi<=b*t[k].r){printf("%4.0f | %5.2f%% | %4.0f | -- | EMI <= interest; cannot repay\n",t[k].p,t[k].r*100,t[k].emi);continue;}
        while(b>EPS&&m<1000){b+=b*t[k].r;double pay=b<t[k].emi?b:t[k].emi;b-=pay;m++;}
        printf("%4.0f | %5.2f%% | %4.0f | %2d | %s\n",t[k].p,t[k].r*100,t[k].emi,m,b<=EPS?"paid":"limit");
    }return 0;
}