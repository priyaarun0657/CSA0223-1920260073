#include <stdio.h>
extern int token_counter;
void issue(void);
int main(void){issue();issue();printf("counter=%d\n",token_counter);return 0;}
