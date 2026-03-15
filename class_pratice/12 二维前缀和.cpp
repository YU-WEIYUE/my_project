//本题为P2004 领地选择
#include<iostream>
#include<cstdlib>
int map[1001][1001],sum[1001][1001],ans=-200000000,x,y;
using namespace std;
int main(){
    int n,m,c;cin>>n>>m>>c;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>map[i][j];
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + map[i][j];
        }
    }

    for(int j=c;j<=m;j++){
        for(int i=c;i<=n;i++){
            int q=sum[i][j]-sum[i][j-c]-sum[i-c][j]+sum[i-c][j-c];
            if(q>ans){
                ans=q;x=i-c;y=j-c;
            }
        }
    }
    cout<<x+1<<" "<<y+1<<endl;

}