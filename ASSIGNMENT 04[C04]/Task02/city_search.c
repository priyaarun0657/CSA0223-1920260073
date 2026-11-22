#include <stdio.h>
#include <string.h>
struct address { char city[20]; int pin; };
struct parcel { int id; float weight; struct address to; };
int main(void) {
    struct parcel p[] = {{1,2.0f,{"Chennai",600001}},
                         {2,4.0f,{"Madurai",625001}},
                         {3,1.5f,{"Chennai",600077}}};
    const char *city = "Chennai";
    for (int i=0;i<3;i++)
        if (strcmp(p[i].to.city, city)==0)
            printf("Parcel %d -> %s\n",p[i].id,p[i].to.city);
    return 0;
}
