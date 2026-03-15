#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    string s="abc";
    do{
        cout<<s<<" ";
    }while(next_permutation(s.begin(),s.end()));
    //按字典序输出这三个字母的组合，若s为bac则只输出4个结果
    //如果为了全排列，要先sort(s.begin(),s.end())再使用next_permutation
    cout<<endl;
    

    int a[]={2,1,3};
    next_permutation(a,a+3);
    for(int &i:a)cout<<i<<" ";
    //直接输出213的下一个排列组合231
    cout<<endl;

    prev_permutation(a,a+3);
    for(int &i:a)cout<<i<<" ";//输出231的前一个排列组合213

    return 0;
}