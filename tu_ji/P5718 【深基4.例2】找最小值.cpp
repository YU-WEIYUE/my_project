#include<iostream>
#include<algorithm>
using namespace std;
int n,arr[100];
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    sort(arr,arr+n);
    cout<<arr[0];
}