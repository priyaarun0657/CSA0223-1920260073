#include <stdio.h>
struct packet_all { float temperature; int humidity; char status[8]; };
int main(void) {
    struct packet_all p = {31.5f,68,"OK"};
    printf("Temp %.1f, Humidity %d, Status %s\n",p.temperature,p.humidity,p.status);
    printf("Size = %zu bytes\n",sizeof p);
    return 0;
}
