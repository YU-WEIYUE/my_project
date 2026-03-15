#include<iostream>
#include<algorithm>
using namespace std;
int a[10000],n,m;
int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<m;i++)next_permutation(a,a+n);
    for(int i=0;i<n;i++)cout<<a[i]<<" ";
}