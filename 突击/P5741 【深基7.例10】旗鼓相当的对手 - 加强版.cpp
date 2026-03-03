#include <iostream>
#include<cmath>
using namespace std;
typedef struct{
    string name;
    int a,b,c;
    int tol;
} data1;

data1 init(){
    data1 a;
    cin>>a.name>>a.a>>a.b>>a.c;
    a.tol=a.a+a.b+a.c;
    return a;
}
void compare(data1 a,data1 b){
    if(abs(a.a-b.a)<=5&&abs(a.b-b.b)<=5&&abs(a.c-b.c)<=5&&abs(a.tol-b.tol)<=10){
        cout<<a.name<<' '<<b.name<<endl;
    }
}
data1 arr[1000];
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        arr[i]=init();
    }
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            compare(arr[i],arr[j]);
        }
    }
    return 0;
}