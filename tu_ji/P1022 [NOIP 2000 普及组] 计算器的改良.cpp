#include <iostream>
#include <cstdio>
using namespace std;
char c,a;//c用来读入,a是未知数名
int f=1,now=1,k,b,x;//f初始化为正，now初始为左，k、b、x意义如上
bool r;//用来判是否有数字读入
int main()
{
	while(cin>>c)//各种处理上面已经解释的很清楚了……（吧）
	{
		if(c=='-') {b+=now*f*x;x=0;f=-1;r=0;}
		if(c=='+') {b+=now*f*x;x=0;f=1;r=0;}
		if(c=='=') {b+=now*f*x;x=0;f=1;now=-1;r=0;}
		if(c>='a'&&c<='z')
		{
			if(r)
			{
				k+=now*f*x;x=0;
			}
			else k+=now*f;
			a=c;r=0;
		}
		if(c>='0'&&c<='9') {x=x*10+c-'0';r=1;}
	}
	b+=now*f*x;//加上最后一项常数（若最后一项是未知数则会加0）
    double ans=double(-b*1.0/k);
	if(ans==-0.0) ans=0;//特判，将-0.0改为0
	printf("%c=%.3lf",a,ans);//保留三位小数输出
	return 0;
}
