#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int n,m;
int x,y;
const int N = 1e5 + 5;
vector<int> G[N];
int v1[N],v2[N];

void bfs(int x){
    queue<int>q;
    q.push(x);v1[x]=1;
    while(!q.empty()){
        int t=q.front();
        for(int i=0;i<(int)G[t].size();i++){
            if(!v1[G[t][i]]){
                q.push(G[t][i]);
                v1[G[t][i]]=1;
            }
        }
        q.pop();
        printf("%d ",t);
    }
}

void dfs(int x){
    if(v2[x])return;
    printf("%d ",x);v2[x]=1;
    for(int i=0;i<(int)G[x].size();i++){
        dfs(G[x][i]);
    }
}

int main(){
    cin>>n>>m;//n文章，m关系
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        G[x].push_back(y);
    }
    for(int i=1;i<=n;i++)sort(G[i].begin(),G[i].end());
    dfs(1);
    cout<<endl;
    bfs(1);
}