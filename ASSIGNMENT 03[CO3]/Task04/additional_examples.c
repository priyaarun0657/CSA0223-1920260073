#include <stdio.h>
int main(void){
    int a[3][3]={{1,2,3},{4,5,6},{7,8,9}};
    puts("Matrix:");for(int i=0;i<3;i++){for(int j=0;j<3;j++)printf("%d ",a[i][j]);puts("");}
    puts("Transpose:");for(int j=0;j<3;j++){for(int i=0;i<3;i++)printf("%d ",a[i][j]);puts("");}
    int diagonal=0;for(int i=0;i<3;i++)diagonal+=a[i][i];printf("Main diagonal sum = %d\\n",diagonal);
}
