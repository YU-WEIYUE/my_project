#include<iostream>
#include<set>
using namespace std;
int main(){
    set<int> s;
    s.insert(43);
    s.insert(2);
    s.insert(2);//默认升序排列并去重
    for(const auto&x:s)cout<<x<<endl;
    cout<<endl;


    set<string>arr;//字符串也能用
    arr.insert("aw4js");
    arr.insert("23ajs");
    arr.insert("ajqs");
    arr.insert("ajswe");
    arr.insert("ajs");
    arr.insert("ajs");
    for(const auto&x:arr)cout<<x<<endl;
}  