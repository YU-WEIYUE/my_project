#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define itn int
int main(){
    ll n;
    cin>>n;
    vector<ll>arr;
    for(ll i=0;i<n;i++){
        ll o;cin>>o;arr.push_back(o);
    }
    sort(arr.begin(),arr.end());
    for(ll i=0;i<n;i++)cout<<arr[i]<<" ";
}