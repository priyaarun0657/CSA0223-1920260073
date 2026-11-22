#include <stdio.h>
#include <string.h>
#define N 6
void sort(char a[N][30]){char t[30];for(int i=0;i<N-1;i++)for(int j=0;j<N-i-1;j++)if(strcmp(a[j],a[j+1])>0){strcpy(t,a[j]);strcpy(a[j],a[j+1]);strcpy(a[j+1],t);}}
int search(char a[N][30],char key[]){int l=0,r=N-1;while(l<=r){int m=l+(r-l)/2,c=strcmp(a[m],key);if(!c)return m;if(c<0)l=m+1;else r=m-1;}return -1;}
int main(){char names[N][30]={"Ravi","Ajay","Meena","Karthik","Ajay","Zara"};sort(names);puts("Sorted names:");for(int i=0;i<N;i++)puts(names[i]);int p=search(names,"Meena");printf("Search Meena: %s index=%d\n",p>=0?"Found":"Not found",p);puts("Duplicates:");for(int i=1;i<N;i++)if(strcmp(names[i],names[i-1])==0)puts(names[i]);}
