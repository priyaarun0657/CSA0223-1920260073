#include <stdio.h>
#include <string.h>
int main(void){
    char names[5][20]={"Ravi","Ajay","Meena","Ajay","Zara"},t[20];
    for(int i=0;i<4;i++)for(int j=0;j<4-i;j++)if(strcmp(names[j],names[j+1])>0){strcpy(t,names[j]);strcpy(names[j],names[j+1]);strcpy(names[j+1],t);}
    puts("Alphabetical list:");for(int i=0;i<5;i++)puts(names[i]);
    puts("Duplicate check:");for(int i=1;i<5;i++)if(strcmp(names[i],names[i-1])==0)printf("%s appears more than once\\n",names[i]);
}
