#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define itn int
const itn N =1e6+5;
int n,k,a[N];
int q[N],head,tail=-1;
int main(){
    scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
    for(int i=0;i<n;i++){
        while(head<=tail&&a[q[tail]]>=a[i])tail--;
        q[++tail]=i;
        if (q[head] < i - k + 1)head++;
        if(i>=k-1)cout<<a[q[head]]<<" ";
    }
    cout << endl;
    head=0;tail=-1;
    for(int i=0;i<n;i++){
        while(head<=tail&&a[q[tail]]<=a[i])tail--;
        q[++tail]=i;
        if (q[head] < i - k + 1)head++;
        if(i>=k-1)cout<<a[q[head]]<<" ";
    }
}