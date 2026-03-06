#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
int main(){
    vector<int>v={5,3,2,4,53,2,1,2,5};
    sort(v.begin(),v.end());
    auto it=unique(v.begin(),v.end());//unique把重复元素移到末尾，返回去重后最后一个元素的位置
    v.erase(it,v.end());//删除末尾的重复元素
    for(const auto&x:v)cout<<x<<" ";
}