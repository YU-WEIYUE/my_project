#include<iostream>
#include<queue>
using namespace std;
int n,m,ans;
int map[51][51],visited[51][51];
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
queue<pair<int,int>>que;
void bfs(int x,int y){
    if(x<1||x>m||y<1||y>n||!map[x][y])return;
    if(visited[x][y])return;
    que.push(make_pair(x,y));
    while(!que.empty()){
        auto now=que.front();
        que.pop();
        int x=now.first,y=now.second;
        for(int i=0;i<4;i++){
            int cx=x+dx[i],cy=y+dy[i];
            if(cx>=1&&cy>=1&&cx<=m&&cy<=n){
                if(map[cx][cy]&&!visited[cx][cy]){
                    visited[cx][cy]=1;
                    que.push(make_pair(cx,cy));
                }
            }
        }
    }
}

int main(){
    cin>>n>>m;
    for (int i=1;i<=m;i++) {
        for (int j=1;j<=n;j++) {
            cin>>map[i][j];
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(!visited[i][j]&&map[i][j]){
                ans++;
                bfs(i,j);
            }
        }
    }
    cout<<ans;
}