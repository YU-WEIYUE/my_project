#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,p,a;
vector<ll>arr,deta;
int main(){
    cin>>n>>p;
    deta.push_back(0);
    arr.push_back(0);
    for(ll i=1;i<=n;i++){
        cin>>a;
        arr.push_back(a);
        deta.push_back(a-arr[i-1]);
    }
    deta.push_back(0);
    for(int i=0;i<p;i++){
        ll x,y,z;
        cin>>x>>y>>z;
        deta[x]+=z;
        deta[y+1]-=z;
    }
    ll ans=0x3f3f3f3f,cnt=0;
    for(int i=1;i<=n;i++){
        cnt+=deta[i];
        if(cnt<ans)ans=cnt;
    }
    cout<<ans;


}