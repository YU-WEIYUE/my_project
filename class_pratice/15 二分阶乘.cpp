#include<iostream>
using namespace std;
//求n！末尾有k个0，n的最小值
long long k;long long n;//5结尾+1个0，0结尾+1个0
long long check(long long n){
    long long cnt=0;
    while(n)cnt+=(n/=5);
    return cnt;
}

int main(){
    cin>>k;
    long long l=0,r=1e18,mid;
    while(l<r){
        mid=l+(r-l)/2;
        if(check(mid)>=k)r=mid;
        else l=mid+1;
    }
    if(check(r)==k)cout<<r;
    else cout<<-1;
    return 0;
}