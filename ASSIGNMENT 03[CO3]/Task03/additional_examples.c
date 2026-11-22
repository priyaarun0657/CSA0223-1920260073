#include <stdio.h>
void merge_ascending(const int a[],int m,const int b[],int n,int out[]){
    int i=0,j=0,k=0;while(i<m&&j<n){if(a[i]<=b[j])out[k++]=a[i++];else out[k++]=b[j++];}
    while(i<m)out[k++]=a[i++];while(j<n)out[k++]=b[j++];
}
int main(void){int a[]={2,5,8,12},b[]={1,5,7,10,15},out[9];merge_ascending(a,4,b,5,out);printf("Ascending merge: ");for(int i=0;i<9;i++)printf("%d ",out[i]);puts("");}
