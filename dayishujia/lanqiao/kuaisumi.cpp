#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define itn int
ll ans=1;
ll a,b,p;
void dig(){
    a%=p;
    while(b){
        if(b&1){
            ans=(ans*a)%p;
        }
        a=a*a%p;
        b>>=1;
    }
}
int main(){
    cin>>a>>b>>p;
    ll aa=a,bb=b;
    dig();
    printf("%lld^%lld mod %lld=%lld",aa,bb,p,ans);
}