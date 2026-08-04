#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
string s;
char def(int l,int r){
    int q=0;
    for(int i=l;i<=r;i++)if(s[i]=='1')q++;
    if(q==0)return 'B';
    else if(q==r-l+1)return 'I';
    else return 'F';
}

void dig(int l,int r){
    if(l>r)return;   
    if(l==r){cout<<def(l,r);return;}
    int mid=(l+r)/2;
    dig(l,mid);
    dig(mid+1,r);
    cout<<def(l,r);
}
int main(){
    int k;cin>>k;
    cin>>s;
    dig(0,s.size()-1);
    cin>>s;
}