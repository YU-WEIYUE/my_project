#include<iostream>
#include<bits/stdc++.h>
using namespace std;
vector<long long>arr,deta;
int main(){
    long long a,b;
    long long l,r;
    arr.push_back(0);
    deta.push_back(0);
    cin>>a;
    for(long long i=1;i<=a;i++){
        cin>>b;
        arr.push_back(b);
        deta.push_back(b+deta[i-1]);
    }
    cin>>b;
    for(long long i=1;i<=b;i++){
        cin>>l>>r;
        cout<<deta[r]-deta[l-1]<<endl;
    }

}
