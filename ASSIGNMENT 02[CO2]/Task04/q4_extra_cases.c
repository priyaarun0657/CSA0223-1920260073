/* Q4 EXTRA: grade boundary and invalid-input test suite */
#include <stdio.h>
char grade(int m){if(m<0||m>100)return '?';switch(m/10){case 10:case 9:return 'S';case 8:return 'A';case 7:return 'B';case 6:return 'C';case 5:return 'D';default:return 'F';}}
int main(void){
    int marks[]={-1,0,49,50,59,60,69,70,79,80,89,90,99,100,101};
    puts("Marks | Grade | Expected category");
    for(int i=0;i<15;i++)printf("%5d | %c | %s\n",marks[i],grade(marks[i]),(marks[i]<0||marks[i]>100)?"invalid":marks[i]>=90?"S":marks[i]>=80?"A":marks[i]>=70?"B":marks[i]>=60?"C":marks[i]>=50?"D":"F");
    return 0;
}