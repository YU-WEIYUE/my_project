//P2240 【深基12.例1】部分背包问题
#include<iostream>
#include<algorithm>
using namespace std;
struct gold{
    double w,v,p;
}a[105];
bool cmp(gold a,gold b){return a.p>b.p;}
int main(){
    int n,c;
    cin>>n>>c;
    for(int i=1;i<=n;i++){
        cin>>a[i].w>>a[i].v;
        a[i].p=a[i].v/a[i].w;
    }
    sort(a+1,a+n+1,cmp);
    double sum=0.0;
    for(int i=1;i<=n;i++){
        if(c>=a[i].w){
            c-=a[i].w;
            sum+=a[i].w;
        }
        else{
            sum+=c*a[i].p;
            break;
        }
    }
    printf("%.2f",sum);
    return 0;

}