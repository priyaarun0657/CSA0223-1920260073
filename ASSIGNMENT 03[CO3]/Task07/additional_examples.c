#include <stdio.h>
int main(void){
    int votes[]={1,1,2,2,3,3,0,4,5,9,-1},count[5]={0},valid=0,invalid=0;
    for(int i=0;i<11;i++){if(votes[i]>=1&&votes[i]<=5){count[votes[i]-1]++;valid++;}else invalid++;}
    printf("Valid=%d Invalid=%d\\n",valid,invalid);
    int max=0;for(int i=0;i<5;i++)if(count[i]>max)max=count[i];
    int winners=0;for(int i=0;i<5;i++)if(count[i]==max&&max>0){printf("Top candidate %d: %d votes\\n",i+1,max);winners++;}
    if(winners>1)puts("Election result: TIE");else if(winners==1)puts("Election result: winner identified");else puts("No valid votes");
}
