/* Q3 EXTRA: bit register operations and validation */
#include <stdio.h>
#define BIT(n) (1u<<(n))
void show(unsigned x){for(int i=7;i>=0;i--)printf("%u",(x>>i)&1u);printf(" (%u)\n",x);}
int main(void){
    unsigned r=0;
    puts("Initial:");show(r);
    r|=BIT(2); puts("Set bit 2:");show(r);
    r|=BIT(5); puts("Set bit 5:");show(r);
    r&=~BIT(2); puts("Clear bit 2:");show(r);
    r^=BIT(5); puts("Toggle bit 5:");show(r);
    printf("Test bit 0: %s\n",(r&BIT(0))?"ON":"OFF");
    return 0;
}