#include <stdio.h>
#define R 3
#define C 4
int main(){int rain[R][C]={{10,20,30,40},{15,25,35,45},{5,30,40,50}};for(int i=0;i<R;i++){int sum=0;for(int j=0;j<C;j++)sum+=rain[i][j];printf("Row %d total=%d\n",i+1,sum);}for(int j=0;j<C;j++){int sum=0;for(int i=0;i<R;i++)sum+=rain[i][j];printf("Column %d average=%.2f\n",j+1,(double)sum/R);}int max=rain[0][0],ri=0,rj=0;for(int i=0;i<R;i++)for(int j=0;j<C;j++)if(rain[i][j]>max){max=rain[i][j];ri=i;rj=j;}printf("Maximum=%d at row %d column %d\n",max,ri+1,rj+1);}
