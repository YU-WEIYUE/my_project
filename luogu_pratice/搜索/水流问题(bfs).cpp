#include<iostream>
#include<queue>
using namespace std;
int m,n;
int map[51][51];
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
queue<pair<int,int>>que;
void init(){
    cin>>m>>n;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cin>>map[i][j];
        }
    }
}

void bfs(int x,int y,int vis[51][51]){
    if(vis[x][y])return;
    vis[x][y]=1;
    que.push(make_pair(x,y));
    while(!que.empty()){
        auto j=que.front();int nx=j.first,ny=j.second;
        que.pop();
        for(int i=0;i<4;i++){
            int cx=nx+dx[i],cy=ny+dy[i];
            if(vis[cx][cy]||cx<1||cx>m||cy<1||cy>n)continue;
            if(map[cx][cy]<map[nx][ny])continue;
            vis[cx][cy]=1;
            que.push(make_pair(cx,cy));
        }
    }
    return;
}
int main(){
    init();
    int vis1[51][51],vis2[51][51];
    memset(vis1,0,sizeof(vis1));
    memset(vis2,0,sizeof(vis2));
    for(int i=1;i<=m;i++) bfs(i,1,vis1);
    for(int i=1;i<=n;i++) bfs(1,i,vis1);
    for(int i=1;i<=m;i++) bfs(i,n,vis2);
    for(int i=1;i<=n;i++) bfs(m,i,vis2);
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(vis1[i][j]&&vis2[i][j])printf("%d %d\n",i,j);
        }
    }
}