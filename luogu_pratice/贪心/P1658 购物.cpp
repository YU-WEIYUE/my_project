#include<iostream>
#include<algorithm>
using namespace std;
int val[10];
int main(){
    int x,n;cin>>x>>n;
    for(int i=0;i<n;i++)cin>>val[i];
    sort(val,val+n);
    if(val[0]!=1){cout<<-1;return 0;}
    int sum=0,ans=0;
    while(sum<x){
        for(int v=n-1;v>=0;v--){
            if(val[v]<=sum+1){
                sum+=val[v];
                ans++;
                break;
            }
        }
    }
    cout<<ans;
}