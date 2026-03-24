#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n,len,target,a[70],used[70],sum,num;

bool cmp(int a,int b){
    return a>b;
}

void dfs(int target,int biaohao,int finished,int start){//目标长度，在拼第几根，已经拼了多少
    if(biaohao>num){cout<<target;exit(0);}
    if(finished==target){dfs(target,biaohao+1,0,1);return;}
    for(int i=start;i<=n;i++){
        if(used[i]||finished+a[i]>target)continue;
        if(i>1&&a[i]==a[i-1]&&!used[i-1])continue;
        used[i]=1;dfs(target,biaohao,finished+a[i],i+1);used[i]=0;
        if(finished==0)return;
        if(finished+a[i]==target)return;
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];sum+=a[i];
        
    }
    sort(a+1,a+1+n,cmp);
    for(len=a[1];len<=sum;len++){
        if(sum%len)continue;
        num=sum/len;
        memset(used,0,sizeof(used));
        dfs(len,1,0,1);
    }
    return 0;
}