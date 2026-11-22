#include <stdio.h>
void bubble(int a[],int n,int *c,int *s){*c=*s=0;for(int i=0;i<n-1;i++){int flag=0;for(int j=0;j<n-i-1;j++){(*c)++;if(a[j]>a[j+1]){int t=a[j];a[j]=a[j+1];a[j+1]=t;(*s)++;flag=1;}}if(!flag)break;}}
void selection(int a[],int n,int *c,int *s){*c=*s=0;for(int i=0;i<n-1;i++){int m=i;for(int j=i+1;j<n;j++){(*c)++;if(a[j]<a[m])m=j;}if(m!=i){int t=a[i];a[i]=a[m];a[m]=t;(*s)++;}}}
void insertion(int a[],int n,int *c,int *sh){*c=*sh=0;for(int i=1;i<n;i++){int x=a[i],j=i-1;while(j>=0){(*c)++;if(a[j]>x){a[j+1]=a[j];(*sh)++;j--;}else break;}a[j+1]=x;}}
void show(char *name,int a[],int c,int s){printf("%s: ",name);for(int i=0;i<6;i++)printf("%d ",a[i]);printf("\nComparisons=%d operations=%d\n",c,s);}
int main(){int src[]={42,17,8,33,25,12},a[6],c,s;for(int i=0;i<6;i++)a[i]=src[i];bubble(a,6,&c,&s);show("Bubble",a,c,s);for(int i=0;i<6;i++)a[i]=src[i];selection(a,6,&c,&s);show("Selection",a,c,s);for(int i=0;i<6;i++)a[i]=src[i];insertion(a,6,&c,&s);show("Insertion",a,c,s);}
