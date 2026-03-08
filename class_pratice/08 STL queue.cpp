#include<iostream>
#include<queue>
using namespace std;
//约瑟夫问题
int main(){
    queue<int>q;
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++)q.push(i);
    while(!q.empty()){
        for(int i=1;i<m;i++){
            q.push(q.back());//把队首元素复制到队尾
            q.pop();//删除队首元素
        }
        cout<<q.front()<<endl;
        q.pop();
    }
    cout<<endl;
    return 0;
}