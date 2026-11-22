#include <stdio.h>
int linear(const int a[], int n, int key, int *cmp) {
    *cmp = 0;
    for (int i=0; i<n; i++) { (*cmp)++; if (a[i]==key) return i; }
    return -1;
}
int main(void) {
    int a[]={12,7,19,7,25,3,30}, cmp, keys[]={7,30,99};
    for(int k=0;k<3;k++) {
        int p=linear(a,7,keys[k],&cmp);
        printf("Key %d: index=%d, comparisons=%d\\n",keys[k],p,cmp);
    }
    return 0;
}
