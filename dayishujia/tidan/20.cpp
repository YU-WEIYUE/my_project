#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,ans;
int c[2000002];
int ls(int x){
    return c[2*x-1];
}
int rs(int x){
    return c[2*x];
}
void dfs(int x,int d){
    if(!x)return;
    dfs(ls(x),d+1);
    dfs(rs(x),d+1);
    ans=max(ans,d);

}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>c[i*2-1];
        cin>>c[i*2];
    }
    dfs(1,1);
    cout<<ans;
}