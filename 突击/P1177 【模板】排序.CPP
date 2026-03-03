#include<iostream>
#include<algorithm>
using namespace std;
long x;
long long arr[100000];
int main(){
    cin>>x;
    for(long i=0;i<x;i++){
        cin>>arr[i];
    }
    sort(arr,arr+x);
    for(long i=0;i<x;i++)cout<<arr[i]<<' ';
    return 0;
}