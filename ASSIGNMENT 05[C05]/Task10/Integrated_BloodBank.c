#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{int id;char name[32],group[4];int age,days;}Donor;
int eligible(const Donor *d){return d->age>=18&&d->days>=90;}
int main(void){Donor d[]={{1001,"Arun","O+",25,120},{1002,"Bala","A-",31,45},{1003,"Charu","B+",19,180}};int count=0;for(int i=0;i<3;i++){printf("%d %s %s eligible=%s\n",d[i].id,d[i].name,d[i].group,eligible(&d[i])?"yes":"no");count+=eligible(&d[i]);}printf("eligible total=%d\n",count);return 0;}
