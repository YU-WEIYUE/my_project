#include<iostream>
#include<queue>
using namespace std;
int m,n,cnt=2,ans;
int map[51][51],vis[51][51];
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
int s[2][1252];
void init(){
    cin>>m>>n;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cin>>map[i][j];
        }
    }
}
void dfs(int x,int y){
    if(!map[x][y])return;
    map[x][y]=cnt;s[0][cnt]++;vis[x][y]=1;
    for(int i=0;i<4;i++){
        int cx=x+dx[i],cy=y+dy[i];
        if(cx<1||cx>m||cy<1||cy>n)continue;
        if(vis[cx][cy])continue;
        dfs(cx,cy);
    }
}

int main(){
    init();
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(map[i][j]==1){
                dfs(i,j);
                cnt++;
            }
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(!map[i][j]){
                int now=0;
                memset(s[1],0,sizeof(s[1]));
                for(int k=0;k<4;k++){
                    int cx=i+dx[k],cy=j+dy[k];
                    if(map[cx][cy]>1&&!s[1][map[cx][cy]]){
                        s[1][map[cx][cy]]=1;
                        now+=s[0][map[cx][cy]];
                    }
                }
                ans=max(ans,now);
            }
        }
    }
    printf("%d",ans+1);
}