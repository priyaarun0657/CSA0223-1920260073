#include <stdio.h>
int *lowest_stock(int stock[],int n){if(n<=0)return NULL;int *p=&stock[0];for(int i=1;i<n;i++)if(stock[i]<*p)p=&stock[i];return p;}
int main(void){int stock[8]={40,25,12,8,30,15,9,22};int *p=stock;printf("p+3 points to index 3\n*(p+3)=%d p[3]=%d\n",*(p+3),p[3]);printf("*p=%d\n",*p);int *low=lowest_stock(stock,8);printf("lowest=%d\n",*low);*low+=5;printf("updated lowest=%d\n",*low);return 0;}
