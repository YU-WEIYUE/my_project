#include<iostream>
#include<vector>
using namespace std;
int n,a,b;
int an1,an2;
int father[1005];
void init(){
    for(int i=1;i<=n;i++)father[i]=i;
}

int find(int u){
    return u==father[u]?u:find(father[u]);
}

int same(int u,int v){
    u=find(u),v=find(v);
    return u==v;
}

void join(int u,int v){
    u=find(u),v=find(v);
    if(u==v)return;
    father[u]=v;
}

int main(){
    cin>>n;
    init();
    while(n--){
        cin>>a>>b;
        if(same(a,b)){
            an1=a,an2=b;
        }
        join(a,b);
    }
    cout<<an1<<" "<<an2;
}