#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll ans;
ll dig(ll x){
    char ch;
    while(cin>>ch){
        if(ch=='(')x=x+dig(0);
        if(ch=='a')x++;
        if(ch=='|')return max(x,dig(0));
        if(ch==')')return x;
    }
    return x;
}
int main(){
    ans=dig(0);
    cout<<ans;
}