#include<iostream>
using namespace std;
int main(){
	int n; scanf("%d",&n);
	for(int i=n;i>=0;i--){
		int a; scanf("%d",&a);
		if(!a)continue;//系数为0直接跳过
		if(a>0&&i!=n)putchar('+');//第一步
		if(a<0)putchar('-');
		
		if(abs(a)!=1||!i)printf("%d",abs(a));//第二步
		
		if(i){//第三步
			putchar('x');
			if(i!=1)printf("^%d",i);
		}
	}
	return 0;
}
