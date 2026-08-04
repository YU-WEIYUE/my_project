#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int dg()
{
    string s;
    char c;
    int k,l=0,v;
    while (cin>>c)//回车+^z自动结束输入.
    {
        if (c==']') break;//特判像"REPEAT 1[] BK 1"这样的情况,不然只有90.
        cin>>s>>k;
        if (c=='R') 
        {
            v=getchar();//读'['.
            l+=k*dg();
            v=getchar();//读']'后' '.
        }
        if (c=='B') v=getchar(),l-=k;
    	if (c=='F') v=getchar(),l+=k;
    	if (v==int(']')) break;//如果v==int(' ')就一直读
    }
    return l;//这里就不必多说了
}
int main()
{
    cout<<abs(dg());//巨短主函数
    return 0;
}