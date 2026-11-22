#include <stdio.h>
void insertion(int a[], int n, int *cmp, int *shift) {
    *cmp=*shift=0;
    for(int i=1;i<n;i++){int key=a[i],j=i-1;while(j>=0){(*cmp)++;if(a[j]>key){a[j+1]=a[j];(*shift)++;j--;}else break;}a[j+1]=key;}
}
void print(int a[],int n){for(int i=0;i<n;i++)printf("%d ",a[i]);puts("");}
int main(void){
    int sorted[]={1,2,3,4,5,6}, nearly[]={1,2,3,5,4,6}, reverse[]={6,5,4,3,2,1};
    int *cases[]={sorted,nearly,reverse}; const char *names[]={"Sorted","Nearly sorted","Reverse"};
    for(int c=0;c<3;c++){int a[6],cmp,sh;for(int i=0;i<6;i++)a[i]=cases[c][i];insertion(a,6,&cmp,&sh);printf("%s -> ",names[c]);print(a,6);printf("comparisons=%d shifts=%d\\n",cmp,sh);}
}
