#include <stdio.h>
union sensor { float temperature; int humidity; };
int main(void) {
    union sensor s;
    s.temperature = 31.5f;
    printf("Temperature stored: %.1f\n",s.temperature);
    printf("Reading another member is not a meaningful humidity value: %d\n",s.humidity);
    return 0;
}
