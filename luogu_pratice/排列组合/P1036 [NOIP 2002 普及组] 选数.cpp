#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,k,a[30],b[30],sum;
bool isprime(int x){
    if(x<=1)return false;
    for(int i=2;i<=sqrt(x);i++){
        if(x%i==0)return false;
    }
    return true;
}

int main(){
    cin>>n>>k;//从n个数字里面选k个数字相加
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<k;i++)b[i]=1;
    sort(b,b+n);
    do{
        int ans=0;
        for(int i=0;i<n;i++)if(b[i])ans+=a[i];
        if(isprime(ans))sum++;
    }while(next_permutation(b,b+n));
    cout<<sum;
    return 0;
}