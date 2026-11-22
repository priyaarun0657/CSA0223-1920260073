#include <stdio.h>
int linear(const int a[],int n,int key,int *c){*c=0;for(int i=0;i<n;i++){(*c)++;if(a[i]==key)return i;}return -1;}
int binary(const int a[],int n,int key,int *c){int l=0,r=n-1;*c=0;while(l<=r){int m=l+(r-l)/2;(*c)++;if(a[m]==key)return m;if(a[m]<key)l=m+1;else r=m-1;}return -1;}
int main(){int u[]={1533,1190,1021,1402,1305,1048,1460,1103,1377,1222},s[]={1021,1048,1103,1190,1222,1305,1377,1402,1460,1533},keys[]={1021,1305,1533,1400};for(int k=0;k<4;k++){int c1,c2,p1=linear(u,10,keys[k],&c1),p2=binary(s,10,keys[k],&c2);printf("Key %d | Linear index=%d comparisons=%d | Binary index=%d comparisons=%d\n",keys[k],p1,c1,p2,c2);}}
