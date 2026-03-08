#include<iostream>
#include<stack>
using namespace std;
int main(){
    stack <int> s;
    s.push(2);
    s.push(3);
    s.push(32767);//压栈
    cout<<s.top()<<endl;//返回栈顶
    s.pop();//删除栈顶
    cout<<s.top()<<endl;
    cout<<s.size()<<endl;
    cout<<s.empty()<<endl;
}