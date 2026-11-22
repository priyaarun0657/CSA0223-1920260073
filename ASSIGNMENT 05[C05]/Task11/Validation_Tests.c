#include <stdio.h>
int eligible(int age,int days){return age>=18&&days>=90;}
int main(void){int ages[]={17,18,25,60};int days[]={90,89,90,365};for(int i=0;i<4;i++)printf("case%d: %s\n",i+1,eligible(ages[i],days[i])?"eligible":"not eligible");return 0;}
