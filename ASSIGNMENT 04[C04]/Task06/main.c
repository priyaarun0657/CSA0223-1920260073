#include <stdio.h>
#include <string.h>
#define MAX 5
enum item_type { PACKAGED, COOKED, COMBO };
struct date { int day, month, year; };
struct item {
    int id;
    char name[30];
    float price;
    int stock;
    enum item_type type;
    union {
        struct date expiry;
        struct date prepared;
        int combo_ids[3];
    } detail;
    float revenue;
};
int sell(struct item *it, int quantity) {
    if (!it || quantity <= 0 || quantity > it->stock) return 0;
    it->stock -= quantity;
    it->revenue += it->price * quantity;
    return 1;
}
void print_item(const struct item *it) {
    printf("%-12s stock=%d revenue=%.2f\n",it->name,it->stock,it->revenue);
}
int main(void) {
    struct item items[MAX] = {
        {1,"Milk",25.0f,10,PACKAGED,{{22,11,2026}},0},
        {2,"Sandwich",40.0f,8,COOKED,{{22,11,2026}},0},
        {3,"ComboMeal",90.0f,5,COMBO,{{1,2,3}},0},
        {4,"Juice",30.0f,12,PACKAGED,{{23,11,2026}},0},
        {5,"Tea",15.0f,20,COOKED,{{22,11,2026}},0}
    };
    printf("Sale Milk x2: %s\n",sell(&items[0],2)?"OK":"FAILED");
    printf("Sale Sandwich x99: %s\n",sell(&items[1],99)?"OK":"FAILED");
    for(int i=0;i<MAX;i++) print_item(&items[i]);
    return 0;
}
