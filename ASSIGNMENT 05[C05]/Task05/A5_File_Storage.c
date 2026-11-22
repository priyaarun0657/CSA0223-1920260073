#include <stdio.h>
typedef struct{int group_code;int units;}Stock;
int update_units(FILE *fp,int index,int units){Stock s;if(index<0||fseek(fp,(long)index*sizeof s,SEEK_SET)!=0||fread(&s,sizeof s,1,fp)!=1)return 0;s.units=units;if(fseek(fp,-(long)sizeof s,SEEK_CUR)!=0||fwrite(&s,sizeof s,1,fp)!=1)return 0;return 1;}
int main(void){FILE *fp=tmpfile();Stock a[5]={{1,40},{2,25},{3,12},{4,8},{5,30}};fwrite(a,sizeof a,1,fp);printf("update record 3: %s\n",update_units(fp,3,20)?"done":"failed");printf("update record 9: %s\n",update_units(fp,9,20)?"done":"failed");rewind(fp);Stock s;while(fread(&s,sizeof s,1,fp)==1)printf("%d:%d ",s.group_code,s.units);puts("");fclose(fp);return 0;}
