#include<iostream>
#include<queue>
using namespace std;
int m,n,ans;
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
int main(){
    init();
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(map[i][j]){
                for(int k=0;k<4;k++){
                    int cx=i+dx[k],cy=j+dy[k];
                    if(!map[cx][cy])ans++;
                }
            }
        }
    }
    printf("%d",ans);
}
