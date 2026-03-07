#include<iostream>
#include<list>
using namespace std;
list<int>lst={1,2,3};
list <int>lst2(2,4);//2个4
int main(){
    lst.push_back(11);//加入末尾11
    lst.push_front(218);//加入头218
    auto it=lst.begin();
    for(int i=0;i<3;i++)++it;
    lst.insert(it,30);//在it位置插入30
    lst.erase(it);//删除it处元素
    lst.pop_back();//删除末尾
    lst.pop_front();//删除头
    cout<<lst.empty()<<endl<<lst.size()<<endl;
    lst.reverse();
    lst.sort();//升序排序
    lst.unique();//去掉连续重复元素
    
    lst.clear();//清空

}