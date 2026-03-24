#include<iostream>
#include<cstring>
using namespace std;
#define INF 0x3f3f3f3f
int m,n;
int x,y;
int max;
int map[21][21],visited[21];
int main(){
    cin>>n>>m;
    memset(map,INF,sizeof(map));
    for(int i=0;i<m;i++){
        cin>>x>>y;
        cin>>map[x][y];
    }

}