#include<iostream>
#include<vector>
using namespace std;
int k,n;
int vis[101];//2000jiyishangtiaobian
vector<int>adj[101];
void dfs(int x){
    if(vis[x])return;
    vis[x]=1;
    for(int i=0;i<adj[x].size();i++){
        dfs(adj[x][i]);
    }
}
int main(){
    cin>>n>>k;
    int s,d;
    for(int i=0;i<k;i++){
        cin>>s>>d;s--;d--;
        adj[s].push_back(d);
    }
    dfs(0);
    for(int i=0;i<n;i++){
        if(!vis[i]){
            printf("0");return 0;
        }
    }
    printf("1");
    return 0;
}