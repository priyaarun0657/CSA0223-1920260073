#include <stdio.h>
#include <string.h>

typedef struct { int day, month, year; } Date;
typedef struct { int systolic, diastolic; } BloodPressure;
typedef struct {
    char name[50];
    int age;
    char phone[16];
    BloodPressure bp;
    Date visit;
} Patient;

void addPatient(Patient *p, const char *name, int age, const char *phone,
                int systolic, int diastolic, Date date) {
    if (!p) return;
    snprintf(p->name, sizeof p->name, "%s", name);
    p->age = age;
    snprintf(p->phone, sizeof p->phone, "%s", phone);
    p->bp.systolic = systolic;
    p->bp.diastolic = diastolic;
    p->visit = date;
}

void printPatient(const Patient *p) {
    printf("%s | Age %d | Phone %s | BP %d/%d | %02d/%02d/%04d\n",
           p->name, p->age, p->phone, p->bp.systolic, p->bp.diastolic,
           p->visit.day, p->visit.month, p->visit.year);
}

int main(void) {
    Patient p;
    Date d = {22, 11, 2026};
    addPatient(&p, "Arun", 24, "9876543210", 120, 80, d);
    printPatient(&p);
    return 0;
}
