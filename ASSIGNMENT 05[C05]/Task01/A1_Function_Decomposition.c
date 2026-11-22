#include <stdio.h>
typedef struct { int count; int youngest_id; } EligibleSummary;
int check_eligibility(int age, int days_since_last);
int find_eligible(const int ages[], const int days[], const int ids[], int n, EligibleSummary *summary);
int update_stock(int stock[], int group, int delta);
void print_menu(void);
int main(void){ int ages[]={25,31,19,44}, days[]={120,90,180,40}, ids[]={101,102,103,104}; EligibleSummary s={0,-1}; find_eligible(ages,days,ids,4,&s); printf("Eligible donors: %d\\nYoungest eligible ID: %d\\n",s.count,s.youngest_id); print_menu(); return 0; }
int check_eligibility(int age,int days_since_last){return age>=18 && days_since_last>=90;}
int find_eligible(const int ages[],const int days[],const int ids[],int n,EligibleSummary *s){int min=999; for(int i=0;i<n;i++) if(check_eligibility(ages[i],days[i])){s->count++;if(ages[i]<min){min=ages[i];s->youngest_id=ids[i];}} return s->count;}
int update_stock(int stock[],int group,int delta){if(group<0||group>=8||stock[group]+delta<0)return 0;stock[group]+=delta;return 1;}
void print_menu(void){puts("Menu: register | find | issue | stock | save | exit");}
