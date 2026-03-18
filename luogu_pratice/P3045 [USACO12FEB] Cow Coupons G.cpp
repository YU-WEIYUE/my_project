#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
struct dat{
    long long p,c;
    long long deta;
}arr[50000];
long long n,k,idx,ans;long long m,sum;
priority_queue<long long>q;
bool cmp(dat a,dat b){return a.c<b.c;}
int main(){
    cin>>n>>k>>m;
    for(long long i=0;i<n;i++){
        cin>>arr[i].p>>arr[i].c;
        arr[i].deta=arr[i].p-arr[i].c;
    }
    sort(arr,arr+n,cmp);
    while(sum+arr[idx].c<=m&&k&&idx<n){
        sum+=arr[idx].c;
        q.push(arr[idx].deta);
        idx++;ans++;k--;
    }
    if(sum==0){cout<<0;return 0;}
    while(sum<=m&&idx<n){
        if(arr[idx].deta>q.top()){
            if(sum+q.top()+arr[idx].c<=m){
                sum=sum+q.top()+arr[idx].c;
                q.pop();
                q.push(arr[idx].deta);
                ans++;
            }
        }
        else {
            if(sum+arr[idx].p<=m){
                ans++;
                sum+=arr[idx].p;
            }
        }
        idx++;
    }
    cout<<ans<<endl;
}