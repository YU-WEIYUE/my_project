#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int xunzhaozichuan(char a[],char b[]){
    int i=0;
    while(a[i]!='\0'){
        int j=0;
        while(j<strlen(b)){
            if(a[i+j]!=b[j]){
                break;
            }
            j++;
        }
        if(b[j]=='\0'){
            return i;
        }
        i++;
    }
    return -1;
}


void find_next(char b[],int next[],int length){
    int i=0,j=-1;
    next[0]=-1;
    while(i<length){
        if(j==-1||b[i]==b[j]){
            i++;
            j++;
            next[i]=j;
        }else{
            j=next[j];
        }
    }
}


int KMP(char a[],char b[]){
    int next[100];
    find_next(b,next,strlen(b));
    int i=0,j=0;
    while(i<strlen(a)&&j<strlen(b)){
        if(j==-1||a[i]==b[j]){
            i++;
            j++;
        }else{
            j=next[j];
        }
    }
    if(j==strlen(b)){
        return i-j;
    }else{
        return -1;
    }
}


int main(){
    char a[100],b[100];
    printf("请输入主串：");
    scanf("%s",a);
    printf("请输入子串：");
    scanf("%s",b);
    int index=KMP(a,b);
    if(index!=-1){
        printf("子串在主串中的位置是：%d\n",index);
    }else{
        printf("子串不在主串中\n");
    }
    return 0;
}
