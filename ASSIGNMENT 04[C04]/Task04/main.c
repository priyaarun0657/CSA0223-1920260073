#include <stdio.h>
struct account { int number; float balance; };
void addInterest(struct account *a, float rate) {
    if (!a) return;
    a->balance += a->balance * rate / 100.0f;
}
int main(void) {
    struct account list[3] = {{101,5000},{102,12000},{103,800}};
    struct account *p = list;
    printf("Address in main: %p\n",(void*)&list[0]);
    for (int i=0;i<3;i++) {
        printf("Before: %d %.2f\n",list[i].number,list[i].balance);
        addInterest(&list[i],4);
    }
    printf("First account through pointer: %d %.2f\n",p->number,p->balance);
    for (int i=0;i<3;i++) printf("%d %.2f\n",list[i].number,list[i].balance);
    return 0;
}
