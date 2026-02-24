#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int *getnext(char*s){
    int len=strlen(s);
    int*next=(int*)malloc(sizeof(int)*len);
    next[0]=0;
    for(int i=1;i<len;i++){
        int j=next[i-1];
        while(j>0&&s[i]!=s[j]){
            j=next[j-1];
        }
        if(s[i]==s[j]){
            j++;
        }
        next[i]=j;
    }
    return next;
}

int KMP(char*s,char*t){
    int*next=getnext(t);
    int i=0,j=0;
    int slen=strlen(s);
    int tlen=strlen(t);
    while(i<slen&&j<tlen){
        if(j==0||s[i]==t[j]){
            i++;
            j++;
        }else{
            j=next[j-1];
        }
    }
    free(next);
    if(j==tlen){
        return i-j;
    }else{
        return -1;
    }
}

int main(){
    char s[100],t[100];
    scanf("%s",s);
    scanf("%s",t);
    int pos=KMP(s,t);
    if(pos==-1){
        printf("未找到模式串\n");
    }else{
        printf("模式串在主串中的位置为：%d\n",pos+1);
    }
    return 0;
}