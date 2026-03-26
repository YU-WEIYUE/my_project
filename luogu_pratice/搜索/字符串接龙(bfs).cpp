#include<iostream>
#include<queue>
#include<string>
#include<vector>
using namespace std;
string a,b,q;
int n;
vector<string>list;
queue<string>que;
int vis[500];
int judge(string a,string b){
    if(a.size()!=b.size())return 0;
    int o=0;
    for(int i=0;i<a.size();i++){
        if(a[i]!=b[i])o++;
    }
    if(o==1)return 1;
    else return 0;
}

void bfs(string a,string b){
    que.push(a);
    int ans=0;
    while(!que.empty()){
        ans++;
        string start=que.front();
        que.pop();
        for(auto i=0;i<list.size();i++){
            if(judge(start,list[i])&&!vis[i]){
                if(judge(list[i],b)){printf("%d",ans+1);return;}
                que.push(list[i]);
                cout<<list[i]<<endl;
                vis[i]=1;
            }
        }
    }
    printf("0");return;
}

int main(){
    cin>>n;  
    cin>>a>>b;
    for(int i=1;i<=n;i++){
        cin>>q;
        list.push_back(q);
    }
    cout<<endl;
    bfs(a,b);
    return 0;
}
