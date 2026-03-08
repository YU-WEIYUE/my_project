#include<iostream>

using namespace std;
int arr[1000002];int s[1000002];
int main()
{
    int n;cin>>n;
     for(int i=1;i<=n;i++){
        cin>>arr[i];
        while(s[arr[i]])arr[i]++;
        s[arr[i]]=1;
    }
    
    for(int i=1;i<=n;i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}