#include <stdio.h>
#include <ctype.h>
int count_vowels(const char s[]){int n=0;for(int i=0;s[i];i++){char c=tolower((unsigned char)s[i]);if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u')n++;}return n;}
int count_digits(const char s[]){int n=0;for(int i=0;s[i];i++)if(isdigit((unsigned char)s[i]))n++;return n;}
int main(void){const char s[]="C Programming 2026";printf("Text: %s\\nVowels: %d\\nDigits: %d\\n",s,count_vowels(s),count_digits(s));}
