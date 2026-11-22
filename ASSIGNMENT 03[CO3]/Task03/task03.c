#include <stdio.h>
int merge(const int a[],int m,const int b[],int n,int out[]){int i=0,j=0,k=0;while(i<m&&j<n){if(a[i]>=b[j])out[k++]=a[i++];else out[k++]=b[j++];}while(i<m)out[k++]=a[i++];while(j<n)out[k++]=b[j++];return k;}
int main(){int a[]={98,91,85,72},b[]={95,91,80},out[7];int n=merge(a,4,b,3,out);printf("Merged descending: ");for(int i=0;i<n;i++)printf("%d ",out[i]);puts("");int empty[1],o[4];n=merge(a,4,empty,0,o);printf("Empty-list test: ");for(int i=0;i<n;i++)printf("%d ",o[i]);puts("");}
