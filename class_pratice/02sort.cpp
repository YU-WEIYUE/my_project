#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
typedef struct{
    string str;
    int num;
} dat;

bool compare(const dat& a,const dat& b){//自定义比较规则
    return a.num<b.num;
}

vector<dat> q;

int main(){
    vector<int> v={3,4,4354,323,56,6};
    sort(v.begin(),v.end());//默认升序排序
    sort(v.begin(),v.end(),greater<int>());//降序排序
    v.clear();

//接下来是自定义结构体排序

    q.push_back({"qq",3});
    q.push_back({"qww",43});
    q.push_back({"qrtw",65});
    sort(q.begin(),q.end(),compare);
    for(auto&d:q){//c++11开始支持的vector循环，即遍历q，把每个元素暂时命名为d，没有&就不能修改q
                  //auto避免书写复杂类型名  
        cout<<d.str<<" "<<d.num<<endl;
    }
}