#include<stdio.h>
#include<string.h>
char a[2001],b[2001];
int a1[2001],a2[2001],res[4001];
int main(){
    scanf("%s %s",a,b);
    int lena=strlen(a),lenb=strlen(b);
    for(int i=lena-1;i>=0;i--)a1[i]=a[lena-i-1]-'0';
    for(int i=lenb-1;i>=0;i--)a2[i]=b[lenb-i-1]-'0';
    for(int i=0;i<lena;i++){
        for(int j=0;j<lenb;j++){
            res[i+j]+=a1[i]*a2[j];
        }
    }
    for(int i=0;i<lena+lenb;i++){
        if(res[i]>=10){
            res[i+1]+=res[i]/10;
            res[i]%=10;
        }
    }
    int len=lena+lenb;
    while(res[len-1]==0&&len>1)len--;
    for(int i=len-1;i>=0;i--)printf("%d",res[i]);
}