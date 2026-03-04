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
    for(int i=0;i<q.size();i++){
        cout<<q[i]<<" ";
    }//遍历q
    q.clear();
}