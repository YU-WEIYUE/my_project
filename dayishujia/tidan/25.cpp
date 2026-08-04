#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define itn int
int n,m;
typedef struct{
    int x,y,l;
}r;
ll ans;
int x,y,z;
int f[5001];
int c;
vector<r>arr;

bool cmp(r a,r b){
    return a.l<b.l;
}

int root(int x){
    if(x!=f[x])f[x]=root(f[x]);
    return f[x];
}

void merge(int x,int y){
    int rx=root(x);
    int ry=root(y);
    if(rx!=ry)f[rx]=ry;
}
int main(){
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>x>>y>>z;
        r n;n.x=x;n.y=y;n.l=z;
        arr.push_back(n);
    }
    for(int i=1;i<=n;i++)f[i]=i;
    sort(arr.begin(),arr.end(),cmp);
    for(int i=0;i<(int)arr.size();i++){
        r q=arr[i];
        if(root(q.x)==root(q.y))continue;
        merge(q.x,q.y);
        ans+=q.l;
    }
    for(int i=1;i<=n;i++){
        if(f[i]==i)c++;
        if(c>1){
            printf("orz");return 0;
        }
    }
    printf("%lld",ans);
    return 0;
}