#include<iostream>
#include<map>
using namespace std;
map<int,string>mp;//前一个值为key，后一个为value，map会自己按key升序排序，若key重复会导致覆盖
int main(){
    mp[0]="qs";
    mp.insert({1,"hi"});
    mp.erase(0);//去除key值为0的数据

    for(auto i:mp)cout<<i.first<<"  "<<i.second<<endl;

  


    map<int,string>a{{1,"ds"},{23,"hiou"},{2432,"ws"}};
    auto it=a.begin();
    for(;it!=a.end();++it){
        cout<<it->first<<" "<<it->second<<endl;
    }
    cout<<a.count(22)<<endl;//查找key值为1的数字  
    
    a[23]="hello";
    for(auto it=a.begin();it!=a.end();++it){
        cout<<it->first<<" "<<it->second<<endl;
    }
}