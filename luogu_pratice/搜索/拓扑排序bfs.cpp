#include<iostream>
#include<queue>
using namespace std;
queue<int>que;
queue<int>ans;
int m,n,vis;
vector<int>map[100000];
vector<int>indegree;
void init_map(){
    cin>>m>>n;//m文件n关系
    indegree.resize(m, 0);
    while(n--){
        int a,b;
        cin>>a>>b;
        map[a].push_back(b);
        indegree[b]++;
    }
}

void bfs(){
    for(int i =0;i<m;i++)if(!indegree[i])que.push(i);
    while(!que.empty()){
        int num=que.front();
        que.pop();
        ans.push(num);
        vis++;
        for (int i = 0; i < map[num].size(); i++) {
            int v = map[num][i];
            indegree[v]--;
            if (!indegree[v])que.push(v); 
        }
    }
}

void put() {
    if (vis != m) {
        cout << -1 << endl;
        return;
    } 
    while (!ans.empty()) {
        cout << ans.front() << " ";
        ans.pop();
    }
    cout << endl;
    
}
int main(){
    init_map();
    bfs();
    put();
    return 0;
}