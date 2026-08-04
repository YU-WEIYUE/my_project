#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long

ll shuzi[51];
int top;
char ch;
ll num;
int main(){
    while(cin>>ch&&ch!='@'){
        if(ch>='0'&&ch<='9'){
            num=num*10+ch-'0';
        }
        else if(ch=='.'){
            shuzi[top++]=num;
            num=0;
        }
        else{
            ll res=0;
           ll b=shuzi[--top];
           ll a=shuzi[--top];
           if (ch == '+') res = a + b;
            else if (ch == '-') res = a - b;
            else if (ch == '*') res = a * b;
            else res = a / b; 
            shuzi[top++]=res;
        }
    }
    cout<<shuzi[--top];

}