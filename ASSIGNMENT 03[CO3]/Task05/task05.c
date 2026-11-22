#include <stdio.h>
#include <ctype.h>
int word_count(const char s[]){int n=0,in=0;for(int i=0;s[i];i++){if(!isspace((unsigned char)s[i])&&!in){n++;in=1;}else if(isspace((unsigned char)s[i]))in=0;}return n;}
int palindrome(const char s[]){int l=0,r=0;while(s[r])r++;r--;while(l<r){while(l<r&&!isalpha((unsigned char)s[l]))l++;while(l<r&&!isalpha((unsigned char)s[r]))r--;if(tolower((unsigned char)s[l])!=tolower((unsigned char)s[r]))return 0;l++;r--;}return 1;}
void reverse(char s[]){int n=0;while(s[n])n++;for(int i=0,j=n-1;i<j;i++,j--){char t=s[i];s[i]=s[j];s[j]=t;}}
int main(){char msg[]="Meet at the library at 5 PM";printf("Words: %d\n",word_count(" Meet at the library at 5 PM "));printf("Madam, I'm Adam palindrome: %s\n",palindrome("Madam, I'm Adam")?"Yes":"No");printf("Hello palindrome: %s\n",palindrome("Hello")?"Yes":"No");reverse(msg);printf("Reversed: %s\n",msg);}
