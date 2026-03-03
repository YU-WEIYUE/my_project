#include<iostream>
#include<algorithm>
using namespace std;
long long n,temp=0;
long tree[1000001];
long long m;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>tree[i];
    sort(tree+1,tree+n+1);
    long long j=n;
    while(temp<m)temp+=((tree[j]-tree[--j])*(n-j));
    long long ans=tree[j]+(temp-m)/(n-j);
    cout<<ans;
    return 0;
}            