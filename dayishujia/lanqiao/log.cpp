#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define itn int
int m,a,f;
vector<int>arr;
itn main(){
    cin>>m;
    while(m--){
        cin>>f;
        if(f==1){
            cin>>a;
            arr.push_back(a);
            sort(arr.begin(),arr.end());
        }
        else{
            cin>>a;
            int length=arr.size();
            int l=0,r=length;
            while(l!=r){
                int mid=(l+r)/2;
                if(arr[mid]>a)r=mid;
                else if(arr[mid]<a)l=mid;
                else break;
            }
            if(arr[l]==a)
        }
    }
}