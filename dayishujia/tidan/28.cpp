#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define itn int
int c[500001],a[500001];
ll ans;ll n;

void dig(int l,int r){
    if(l==r)return;
    int mid=(l+r)/2,i=l,j=mid+1,k=l;
    dig(l,mid);dig(mid+1,r);
    while(i<=mid&&j<=r){
        if(a[i]<=a[j])c[k++]=a[i++];
        else c[k++]=a[j++],ans+=mid-i+1;
    }
    while(i<=mid)c[k++]=a[i++];
    while(j<=r)c[k++]=a[j++];
    for(int y=l;y<=r;y++)a[y]=c[y];
}


int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    dig(1,n);
    cout<<ans;
}
