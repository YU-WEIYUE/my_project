#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,m;
int danger[101][101];
int road[10001];
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++)cin>>road[i];
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>danger[i][j];
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                danger[i][j] = min(danger[i][j], danger[i][k] + danger[k][j]);
            }
        }
    }
    int q=0;
    for(int i=1;i<m;i++){
        q+=danger[road[i]][road[i+1]];
    }
    cout<<q;
}