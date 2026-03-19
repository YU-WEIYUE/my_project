#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
int n,m;
int parent[100009];
int find(int x){
    if(parent[x]!=x){
        parent[x]=find(parent[x]);
    }
    return parent[x];
}

void unite(int x,int y){
    int root1=find(x),root2=find(y);
    if(root1!=root2){
        parent[root2]=root1;
    }

}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)parent[i]=i;
    for(int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;
        unite(a,b);
    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(find(i)==i)cnt++;
    }
    cout<<cnt-1<<endl;
    return 0;
    
}