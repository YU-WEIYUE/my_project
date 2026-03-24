#include<iostream>
#include<vector>
using namespace std;
int n,m,ans;
int map[51][51],visited[51][51];
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
void dfs(int x,int y){
    for(int i=0;i<4;i++){
        int cx=x+dx[i],cy=y+dy[i];
        if(cx<1||cy<1||cx>m||cy>n||visited[cx][cy])continue;
        if(!visited[cx][cy]&&map[cx][cy]){
            visited[cx][cy]=1;
            dfs(cx,cy);
        }
    }
}
int main(){
    cin>>n>>m;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> map[i][j];
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(!visited[i][j]&&map[i][j]){
                ans++;
                dfs(i,j);
            }
        }
    }
    cout<<ans;
}