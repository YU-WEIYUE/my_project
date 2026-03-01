#include<iostream>
using namespace std;
int arr[101],n;
int main(){
    cin>>n;
    for(int i=n;i>=0;i--){
        cin>>arr[i];
    }
    for(int i=n;i>=1;i--){
        if(arr[i])cout<<arr[i]<<"x^"<<i<<"+";
    }
    cout<<arr[0];
    return 0;
}