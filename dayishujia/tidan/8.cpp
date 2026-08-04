#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define for(x) for(ll i=1;i<=x;i++)
ll arr[3000002],s[3000002],res[3000002];ll top;
int main(){
    ll n;cin>>n;
    for(n)cin>>arr[i];
    for(n){
        while(top&&arr[i]>arr[s[top]]){
            res[s[top]]=i;top--;
        }
        s[++top]=i;
    }
    for(n)printf("%lld ",res[i]);
    cin>>n;
    return 0;
}