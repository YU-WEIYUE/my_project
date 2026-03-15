#include<iostream>
using namespace std;
int main(){
    int a[]={1,2,3,5,765,43};
    int n=sizeof(a)/sizeof(int);
    for(int i=0;i<(1<<n);i++){//有n个元素，按选或不选共有2**n种情况
        cout<<'{';
        for(int j=0;j<n;j++)
            if(i&(1<<j))//非0说明i二进制的第j位是1，选择a[j]
                cout<<a[j]<<" ";
            cout<<"}\n";
    }
    return 0;
}