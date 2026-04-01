#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
int ans;
int father[1000];
queue<int>ans;
int e,v;//e边，v点
struct edge{
    int l;
    int r;
    int val;
};
vector<edge>edges;
int cmp(edge a,edge b){
    return a.val<b.val;
}

void init(){
    for(int i=1;i<=v;i++)father[i]=i;
}

int find(int u){
    return father[u]==u?u:find(father[u]);
}
void join(int u,int v){
    u=find(u),v=find(v);
    if(u==v)return;
    father[v]=u;
}
int main(){
    cin>>v>>e;
    while(e--){
        int a,b,w;
        cin>>a>>b>>w;
        edges.push_back({a,b,w});
    }
    sort(edges.begin(),edges.end(),cmp);
    init();
    for(edge i:edges){
        int x=find(i.l);
        int y=find(i.r);
        if(x!=y){
            ans+=i.val;
            join(x,y);
        }
    }
    cout<<ans<<endl;
    return 0;
}