#include<bits/stdc++.h>
#define itn int 
#define ll long long
using namespace std;
int ans[1005][1005];
ll n,m;
int ax,ay,bx,by;
itn main(){
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>ax>>ay>>bx>>by;
        ans[ax][ay]++;
        ans[bx+1][ay]--;
        ans[ax][by+1]--;
        ans[bx+1][by+1]++;
    }
    for (int i = 1; i <= n; ++i)for (int j = 1; j <= n; ++j)
        ans[i][j] += ans[i-1][j] + ans[i][j-1] - ans[i-1][j-1];

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }
}