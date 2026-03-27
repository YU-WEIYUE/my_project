#include<iostream>
#include<vector>
#include <climits>
using namespace std;
int ans;
int main(){
    int e,v;//V代表顶点数，E代表边数
    cin>>v>>e;
    vector<vector<int>>map(v+1,vector<int>(v+1,10001));
    while(e--){
        int a,b,weight;
        cin>>a>>b>>weight;
        map[a][b]=weight;
        map[b][a]=weight;
    }
    vector<bool>vis(v+1,0);
    vector<int>mindist(v+1,10001);
    mindist[1]=0;
    for(int i=1;i<v;i++){
        int cur=-1;
        int min=10001;
        for(int j=1;j<=v;j++){
            if(!vis[j]&&mindist[j]<min){
                min=mindist[j];
                cur=j;
            }
        }
        vis[cur]=true;
        for(int j=1;j<=v;j++){
            if(map[cur][j]<mindist[j]&&!vis[j])mindist[j]=map[cur][j];
        }
    }
    for(int i=2;i<=v;i++){
        ans+=mindist[i];
    }
    cout<<ans;
}