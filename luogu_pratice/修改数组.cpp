#include<iostream>

using namespace std;
int arr[1000002];int s[1000002];

int find(int x){
    if(x!=s[x])s[x]=find(s[x]);
    return s[x];
}


int main()
{
    int n;cin>>n;
    for(int i=1;i<=1000002;i++)s[i]=i;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        int root=find(arr[i]);
        arr[i]=root;
        s[root]=find(root+1);
    }
    for(int i=1;i<=n;i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}