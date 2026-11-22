#include <stdio.h>
struct account { int number; float balance; };
void addInterest(struct account a, float rate) {
    printf("Function copy address: %p\n",(void*)&a);
    a.balance += a.balance * rate / 100.0f;
}
int main(void) {
    struct account a={101,5000};
    printf("Caller address: %p\n",(void*)&a);
    addInterest(a,4);
    printf("Caller balance unchanged: %.2f\n",a.balance);
    return 0;
}
