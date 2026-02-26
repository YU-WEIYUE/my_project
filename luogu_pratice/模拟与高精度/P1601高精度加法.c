#include<stdio.h>
#include<string.h>
char a[501],b[501],sum[503];
void reverse(char*a){
    int len=strlen(a);
    for(int i=0;i<len/2;i++){
        char temp=a[i];
        a[i]=a[len-1-i];
        a[len-1-i]=temp;
    }
}
void origanize1(char*a,char*b){
    int lena=strlen(a),lenb=strlen(b);
    reverse(a);
    reverse(b);
    if(lena>lenb){
        for(int i=0;i<lena-lenb;i++){
            b[lenb+i]='0';
        }
    }
    else{
        for(int i=0;i<lenb-lena;i++){
            a[lena+i]='0';
        }
    }
}

void compute(char*a,char*b){
    int len=strlen(a);
    int flag=0;
    for(int i=0;i<len;i++){
        sum[i]=(a[i]+b[i]-'0'-'0'+flag)%10+'0';
        flag=(a[i]+b[i]-'0'-'0'+flag)/10;
    }
    if(flag>0){
        sum[len]=flag+'0';
        sum[len+1]='\0';
    }
    else{
        sum[len]='\0';
    }
    reverse(sum);
    printf("%s",sum);
}
int main(){
    scanf("%s",a);
    scanf("%s",b);
    origanize1(a,b);
    compute(a,b);
    return 0;
}