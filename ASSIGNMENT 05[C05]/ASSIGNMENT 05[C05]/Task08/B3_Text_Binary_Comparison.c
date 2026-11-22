#include <stdio.h>
#include <time.h>
typedef struct{int id;char group[4];int age;}Donor;
int main(void){Donor d={1001,"O+",25},r={0};FILE *t=fopen("donor.txt","w");fprintf(t,"%d,%s,%d\n",d.id,d.group,d.age);fclose(t);t=fopen("donor.txt","r");fscanf(t,"%d,%3[^,],%d",&r.id,r.group,&r.age);fclose(t);printf("text roundtrip: %d %s %d\n",r.id,r.group,r.age);FILE *b=fopen("donor.bin","wb");fwrite(&d,sizeof d,1,b);fclose(b);b=fopen("donor.bin","rb");fread(&r,sizeof r,1,b);fclose(b);printf("binary roundtrip: %d %s %d\n",r.id,r.group,r.age);return 0;}
