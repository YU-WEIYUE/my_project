#include<iostream>
#include<cmath>
using namespace std;
long n,x,len,ti;
int main(){
    cin>>n>>x;
    for(long i=1;i<=n;i++){
        long temp = i;
        while(temp){
            if(temp%10==x)ti++;
            temp/=10;
        }
    }
    cout<<ti;
}
