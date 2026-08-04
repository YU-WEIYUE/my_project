#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define itn int
int f[200001];
int n,m;


itn root(itn x){
    if(f[x]!=x)f[x]=root(f[x]);
    return f[x];
}
void merge(int x,int y){
    int rx = root(x);
    int ry = root(y);
    if (rx != ry)f[ry] = rx;
}
    

void find(int x,int y){
    if(root(x)==root(y))printf("Y\n");
    else printf("N\n");
}
int main(){
    cin>>n>>m;
    int x,y,z;
    for(int i=1;i<=n;i++)f[i]=i;
    for(int i=0;i<m;i++){
        cin>>z>>x>>y;
        if(z==1){
            merge(x,y);
        }
        else find(x,y);
    }
}