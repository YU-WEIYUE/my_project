#include<iostream>
#include<cstdio>
using namespace std;
int vis[11],a[11],b[11],n;

void dfs(int step){
    if(step==n+1){
        for(int i=1;i<=n;i++)printf("%5d",b[i]);
        cout<<endl;
        return;
    }
    for(int i=1;i<=n;i++){
        if(vis[i]==0){
            b[step]=a[i];
            vis[i]=1;
            dfs(step+1);
            vis[i]=0;
        }
    }
    return;

}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++)a[i]=i;
    dfs(1);
    return 0;
}