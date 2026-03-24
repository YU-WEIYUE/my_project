#include<iostream>
#include<vector>
using namespace std;
int m,n,map[51][51],ans[51][51];
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
void dfs(int x,int y){
    ans[x][y]=1;
    for(int i=0;i<4;i++){
        int cx=x+dx[i],cy=y+dy[i];
        if(cx<1||cy<1||cx>m||cy>n||!map[cx][cy]||ans[cx][cy])continue;
        dfs(cx,cy);
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
        if (map[1][i] == 1 && !ans[1][i]) dfs(1, i);
        if (map[m][i] == 1 && !ans[m][i]) dfs(m, i);
    }
    for (int i = 1; i <= m; i++) {
        if (map[i][1] == 1 && !ans[i][1]) dfs(i, 1);
        if (map[i][n] == 1 && !ans[i][n]) dfs(i, n);
    }
    cout<<endl;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }
}
