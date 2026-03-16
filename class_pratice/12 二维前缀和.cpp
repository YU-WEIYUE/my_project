//本题为P2004 领地选择
#include<iostream>
#include<cstdlib>
long long map[1001][1001],sum[1001][1001],ans=-200000000,x,y;
using namespace std;
int main(){
    long long n,m,c;cin>>n>>m>>c;
    for(long long i=1;i<=n;i++){
        for(long long j=1;j<=m;j++){
            cin>>map[i][j];
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + map[i][j];
        }
    }

    for(long long j=c;j<=m;j++){
        for(long long i=c;i<=n;i++){
            long long q=sum[i][j]-sum[i][j-c]-sum[i-c][j]+sum[i-c][j-c];
            if(q>ans){
                ans=q;x=i-c;y=j-c;
            }
        }
    }
    cout<<x+1<<" "<<y+1<<endl;

}