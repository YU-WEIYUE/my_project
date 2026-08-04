#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long
ll s[200002],m[200002];
int f,top1,top2;
ll q;
int main(){
    int n;cin>>n;
    while(n--){
        cin>>f;
        switch(f){
            case 0:{
                cin>>q;
                s[top1++]=q;
                if(top2==0){
                    m[top2++]=q;
                }
                else{
                    m[top2++]=max(q,m[top2-1]);
                }
                break;
            }
            case 1:{
                if(top1>0){
                    top1--;top2--;
                }
                break;
            }
            case 2:{
                if(top2)cout<<m[top2-1]<<endl;
                else cout<<"0"<<endl;
            }
        }
    }
    cin>>n;
}