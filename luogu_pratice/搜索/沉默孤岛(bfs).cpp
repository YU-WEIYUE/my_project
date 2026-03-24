#include<iostream>
#include<queue>
#include<vector>
using namespace std;
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
int map[51][51],visited[51][51];
int m,n;
queue<pair<int,int>>que;
void bfs(int x,int y){
    que.push(make_pair(x,y));
    visited[x][y]=1;
    while(!que.empty()){
        int nx=que.front().first,ny=que.front().second;
        que.pop();
        for(int i=0;i<4;i++){
            int cx=nx+dx[i],cy=ny+dy[i];
            if(cx<1||cy<1||cx>m||cy>n||visited[cx][cy]||!map[cx][cy])continue;
            visited[cx][cy]=1;
            que.push(make_pair(cx,cy));
        }
    }
}
int main(){
    cin>>m>>n;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cin>>map[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        if (map[1][i] == 1 && !visited[1][i]) bfs(1, i);
        if (map[m][i] == 1 && !visited[m][i]) bfs(m, i);
    }
    for (int i = 1; i <= m; i++) {
        if (map[i][1] == 1 && !visited[i][1]) bfs(i, 1);
        if (map[i][n] == 1 && !visited[i][n]) bfs(i, n);
    }
    cout<<endl;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cout<<visited[i][j]<<" ";
        }
        cout<<endl;
    }
}