#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define itn int
int arr[200005];
int n,c;ll ans;
int main(){
    cin>>n>>c;
    for(int i=1;i<=n;i++)cin>>arr[i];
    sort(arr+1,arr+n+1);
    int l=1,r=2;
    while(r<=n){
        if(arr[r]-arr[l]<c){r++;}
        else if(arr[r]-arr[l]==c){
            int y=l;
            while(arr[y]==arr[y+1]){
                ans++;y++;
            }
            ans++;r++;
        }
        else{l++;if(l>r)r=l;}
    }
    printf("%lld",ans);
}