#include<iostream>
#include<cmath> 
using namespace std;
int temp;
int main(){
    int n,ii=1;
    cin>>n;
    while(n){
        temp=n;
        for(int i=1;i<=temp;i++){
            if(ii<10)cout<<"0"<<ii;
            else cout<<ii;     
            ii++;
        }
        cout<<endl;
        n--;
    }
}