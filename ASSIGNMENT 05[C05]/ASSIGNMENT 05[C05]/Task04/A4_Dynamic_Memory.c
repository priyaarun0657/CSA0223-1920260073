#include <stdio.h>
#include <stdlib.h>
typedef struct{int id;char group[4];}Donor;
typedef struct{Donor *data;size_t size,capacity;}DonorList;
int add(DonorList *l,int id,const char *g){if(l->size==l->capacity){size_t c=l->capacity?l->capacity*2:2;Donor *tmp=realloc(l->data,c*sizeof *tmp);if(!tmp)return 0;l->data=tmp;l->capacity=c;}l->data[l->size].id=id;snprintf(l->data[l->size].group,4,"%s",g);l->size++;return 1;}
int main(void){DonorList l={0};char *g[]={"O+","A+","B-","AB+","O-"};for(int i=0;i<5;i++){if(!add(&l,7001+i,g[i])){puts("allocation failed");free(l.data);return 1;}printf("added %d (%s): size=%zu capacity=%zu\n",l.data[i].id,l.data[i].group,l.size,l.capacity);}free(l.data);return 0;}
