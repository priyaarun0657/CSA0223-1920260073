#include <stdio.h>
#include <string.h>
int main(void){char name[16];printf("Enter donor name: ");if(!fgets(name,sizeof name,stdin)){perror("fgets");return 1;}name[strcspn(name,"\n")]=0;printf("Captured safely: %s\n",name);FILE *fp=fopen("missing_data.csv","r");if(!fp)perror("missing_data.csv");return 0;}
