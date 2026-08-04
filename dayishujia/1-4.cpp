#include<bits/stdc++.h>
#define itn int 
#define ll long long
using namespace std;
vector<ll>a,deta;
int main(){
    deta.push_back(0);
    a.push_back(0);
    ll n,p;
    cin>>n>>p;
    for(int i=1;i<=n;i++){
        ll o;
        cin>>o;
        a.push_back(o);
        deta.push_back(o-a[i-1]);
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