#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
int main(){
    priority_queue<int>q;//默认大顶堆
    q.push(5);
    q.push(23);
    q.push(9430);
    q.push(-23);
    cout<<"max:"<<q.top()<<endl;
    while(!q.empty()){//empty()判断是否为空
        cout<<q.top()<<" ";
        q.pop();
    }cout<<endl;
    int h=q.size();
    cout<<h<<endl;//此时堆为空

    priority_queue<int,vector<int>,greater<int>> m;//小顶堆
    m.push(5);
    m.push(23);
    m.push(9430);
    m.push(-23);
    cout<<"min:"<<m.top()<<endl;

}
//pop()不接收