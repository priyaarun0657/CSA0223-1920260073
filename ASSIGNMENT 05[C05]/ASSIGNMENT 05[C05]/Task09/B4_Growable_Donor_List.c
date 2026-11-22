#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{int id;char group[4];}Donor;
typedef struct{Donor *data;int size,capacity;}List;
int add(List *l,int id,const char *g){if(l->size==l->capacity){int c=l->capacity?l->capacity*2:2;Donor *p=realloc(l->data,c*sizeof *p);if(!p)return 0;l->data=p;l->capacity=c;}l->data[l->size].id=id;strncpy(l->data[l->size].group,g,3);l->data[l->size].group[3]=0;l->size++;return 1;}
int main(void){List l={0};char *g[]={"O+","A+","B-","AB+","O-"};for(int i=0;i<5;i++){add(&l,7001+i,g[i]);printf("added %d (%s): size=%d capacity=%d\n",l.data[i].id,l.data[i].group,l.size,l.capacity);}printf("allocated bytes=%zu\n",l.capacity*sizeof(Donor));free(l.data);return 0;}
