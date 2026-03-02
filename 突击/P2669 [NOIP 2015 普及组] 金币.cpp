#include<iostream>
using namespace std;
int n;
long long ans;
int main(){
    cin>>n;
    int perid=1;
    while((perid+1)*perid/2<n)perid++;
    int lastperid=n-perid*(perid-1)/2;
    for(int i=1;i<perid;i++){
        ans+=i*i;
    }
    ans+=lastperid*perid;
    cout<<ans;
}