#include<iostream>
using namespace std;
int main(){//输出n个数中任意m个数组合
    int a[]={12,213,2,43,56,2356};
    int n=sizeof(a)/sizeof(int);
    int m;cin>>m;
    for(int i=0;i<(1<<n);i++){
        int num=0,k=i;
        while(k>0){//判断二进制k里面的1的个数
            k=k&(k-1);//消去最右边的1
            num++;
        }
        if(num==m){
            for(int j=0;j<n;j++){
                if(i&(1<<j)){
                    cout<<a[j]<<" ";
                }
            }
            cout<<"\n";
        }
    }
}