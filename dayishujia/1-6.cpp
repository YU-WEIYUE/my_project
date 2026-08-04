#include<bits/stdc++.h>
#define itn int 
#define ll long long
using namespace std;
int n;
typedef struct{
    ll start;
    ll end;
} boat;
vector<boat>arr;
bool cmp(boat &a,boat &b){
    return a.start<b.start;
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        boat a;
        cin>>a.start>>a.end;
        arr.push_back(a);
    }
    sort(arr.begin(), arr.end(), cmp);
    ll qi=arr[0].start,zh=arr[0].end;
    ll all=0;
    for(int i=1;i<n;i++){
        if(arr[i].start<=zh){
            zh=max(zh,arr[i].end);
        }
        else {
            all+=(zh-qi);
            qi=arr[i].start;
            zh=arr[i].end;
        }
    }
    ll ans=all+zh-qi;
    cout<<ans;

}