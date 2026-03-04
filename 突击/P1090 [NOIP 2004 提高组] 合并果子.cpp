#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int arr[20001],n,ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>arr[i];
    sort(arr+1,arr+n+1);
    int j=1;
    while(j!=n){
        arr[j+1]+=arr[j];
        ans+=arr[j+1];
        j++;
        sort(arr+j,arr+n+1);
    }
    cout<<ans;
    return 0;
}