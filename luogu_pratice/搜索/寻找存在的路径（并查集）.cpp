#include<iostream>
#include<vector>
using namespace std;
int m,n,a,b,father[1005];
void init(){
    for(int i=1;i<=m;i++){
        father[i]=i;
    }
}

int find(int u){
    return u==father[u]?u:find(father[u]);
}

int issame(int u,int v){
    u=find(u),v=find(v);
    return u==v;
}

void join(int u,int v){
    u=find(u),v=find(v);
    if(u==v)return;
    father[u]=v;
}

int main(){
    cin>>m>>n;
    init();
    while(n--){
        cin>>a>>b;
        join(a,b);
    }
    cin>>a>>b;
    if(issame(a,b))cout<<1<<endl;
    else cout<<0<<endl;
    return 0;
}