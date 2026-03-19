#include<iostream>
#include<algorithm>
using namespace std;
struct dat{
    int start;
    int end;
}node[1000006];
int cnt;
bool cmp(dat a,dat b){return a.end<b.end;}
int main(){
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        cin>>node[i].start>>node[i].end;
    }
    sort(node+1,node+n+1,cmp);
    int temp=0;node[0].end=0;node[0].start=0;
    for(int i=1;i<=n;i++){
        if(node[i].start>=node[temp].end){
        ++cnt;
        temp=i;
        }
        else continue;
    }
    cout<<cnt;
    return 0;
}