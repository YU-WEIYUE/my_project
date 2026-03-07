#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> v;//定义
    v.push_back(1);
    v.push_back(23);
    v.push_back(3);//在末尾输入
    int n=v.size();//取大小
    for(int i=0;i<n;i++)cout<<v[i]<<endl;//输出
    v.pop_back();//删除末尾元素
    v.clear();//清空q

    vector<int>q={12,324,12,3,45};
    q.insert(q.begin()+1,3,4);
    q.erase(q.begin()+1,q.begin()+2);
    for(auto i:q){
        cout<<i<<" ";
    }//遍历q
    cout<<endl<<endl;
    cout<<q.front()<<endl;//起始于元素
    cout<<q.back()<<endl;//末尾元素
    q.clear();
}