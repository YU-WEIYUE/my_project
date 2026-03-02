#include<iostream>
using namespace std;
string a,b;
int an[10087],bn[10087],ans[10087];
bool flag=false;
int main(){
    cin>>a>>b;
    if(a.size()==b.size()&&a<b||a.size()<b.size()){
        flag=true;
        swap(a,b);
    }
    for(int i=a.size();i>0;i--)an[i]=a[a.size()-i]-'0';
    for(int i=b.size();i>0;i--)bn[i]=b[b.size()-i]-'0';
    if(a.size()>b.size()){
        for(int i=b.size()+1;i<=a.size();i++){
            bn[i]=0;
        }
    }
    else if(a.size()<b.size()){
        for(int i=a.size()+1;i<=b.size();i++){
            an[i]=0;
        }
    }
    int maxl=max(a.size(),b.size());
    for(int i=1;i<=maxl;i++){
        if(an[i]<bn[i]){
            an[i+1]--;
            an[i]+=10;
        }
        ans[i]=an[i]-bn[i];
    }
    while(ans[maxl]==0)maxl--;
    if(flag)cout<<"-";
    for(int i=maxl;i>0;i--){
        cout<<ans[i];
    }
    if(maxl<1)cout<<"0";
    return 0;
}   