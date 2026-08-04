#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,arr[31][31],flag[31][31];
int vx[4]={0,1,0,-1},vy[4]={1,0,-1,0};
void dfs(int x,int y){
    if(!x||!y||x>n||y>n)return;
    if(flag[x][y])return;
    flag[x][y]=1;
    for(int i=0;i<4;i++)dfs(x+vx[i],y+vy[i]);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){cin>>arr[i][j];if(arr[i][j])flag[i][j]=1;}
    for(int i=1;i<=n;i++){
        dfs(1,i);
        dfs(i,1);
        dfs(i,n);
        dfs(n,i);
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
        if(!flag[i][j])printf("2 ");
        else printf("%d ",arr[i][j]);
        if(j==n)printf("\n");
    }
    cin>>n;
}