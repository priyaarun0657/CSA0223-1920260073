#include <stdio.h>
#define MAX 3
int main(void) {
    char names[MAX][20] = {"Arun", "Bala", "Charu"};
    int ages[MAX] = {24, 31, 19};
    for (int i = 0; i < MAX; ++i)
        printf("%s %d\n", names[i], ages[i]);
    return 0;
}
