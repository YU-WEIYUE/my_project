#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long
int s[100009];int top;

char ch;
int main(){
    int num=0;
    int flag=0;
    string sq;
    cin >> sq;
    for (int i = 0; i < (int)sq.length(); ++i) {
        ch = sq[i];
        if(ch>='0'&&ch<='9'){
            num=(num*10+ch-'0')%10000;
        }
        else{
            s[top++]=num;
            num=0;
            if(flag){
                int a=s[--top]%10000;
                int b=s[--top]%10000;
                s[top++]=(b*a)%10000;
                flag=0;
            }
            if(ch=='*')flag=1;
            
        }
    }
    s[top++]=num;
if(flag){int a=s[--top]%10000;
                int b=s[--top]%10000;
                s[top++]=(b*a)%10000;}
    int res=0;
    for(int i=0;i<top;i++){
        res+=s[i];
        res=res%10000;
    }
   
    cout<<res;
    return 0;
}