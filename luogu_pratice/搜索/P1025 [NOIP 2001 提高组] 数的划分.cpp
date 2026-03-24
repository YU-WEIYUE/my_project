#include<iostream>
#include<vector>
using namespace std;
int cnt;
int n,k;
void dfs(int x,int sum,int u){//x--上次的数，sum--前u-1数字和，u--已经分了u个数
    if(u==k){
        if(sum==n)cnt++;
        return;
    }
    for(int i=x;sum+i*(k-u)<=n;i++)dfs(i,sum+i,u+1);
}
int main(){
    cin>>n>>k;
    dfs(1,0,0);
    cout<<cnt;
}