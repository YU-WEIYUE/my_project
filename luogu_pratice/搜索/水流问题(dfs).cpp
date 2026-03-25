#include<iostream>
#include<queue>
using namespace std;
int m,n;
int map[51][51];
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
void init(){
    cin>>m>>n;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cin>>map[i][j];
        }
    }
}
void dfs(int x,int y,int visited[51][51]){//从边界逆流而上
    if(visited[x][y])return;
    visited[x][y]=1;
    for(int i=0;i<4;i++){
        int cx=x+dx[i],cy=y+dy[i];
        if(cx<1||cx>m||cy<1||cy>n)continue;
        if(map[x][y]>map[cx][cy])continue;
        dfs(cx,cy,visited);
    }
    return;
}
int main(){
    init();
    int visited2[51][51],visited1[51][51];
    memset(visited1,0,sizeof(visited1));
    memset(visited2,0,sizeof(visited2));
    for(int i=1;i<=m;i++) dfs(i,1,visited1);
    for(int i=1;i<=n;i++) dfs(1,i,visited1);
    for(int i=1;i<=m;i++) dfs(i,n,visited2);
    for(int i=1;i<=n;i++) dfs(m,i,visited2);
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(visited1[i][j]&&visited2[i][j])printf("%d %d\n",i,j);
        }
    }
}