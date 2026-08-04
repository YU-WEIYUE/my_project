#include<bits/stdc++.h>
#define itn int 
#define ll long long
using namespace std;
int t,n,f[1000007],book[1000007*3];
//t表示t组数据，n表示有n个操作，f[]是我们并查集的数字，book[]是离散化的数组 
struct node{
    int x,y,e;
}a[1000001];
bool cmp(node a,node b){
    return a.e>b.e;
}
void inti(int k){
    for(int i=1;i<=k;i++)f[i]=i;
}
int get(int x){
    if(f[x]==x)return x;
    return f[x]=get(f[x]);
}
int main(){
    cin>>t;
    while(t--){
        memset(book,0,sizeof(book));
        memset(a,0,sizeof(a));
        memset(f,0,sizeof(f));
        int flag=1,tot=-1;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i].x>>a[i].y>>a[i].e;
            book[++tot]=a[i].x;
            book[++tot]=a[i].y;
        }
        sort(book,book+tot);
        int reu=unique(book,book+tot)-book;
        for(int i=1;i<=n;++i){
           a[i].x=lower_bound(book,book+reu,a[i].x)-book;
           a[i].y=lower_bound(book,book+reu,a[i].y)-book;   
        }
        inti(reu);
        sort(a+1,a+1+n,cmp);
        for(int i=1;i<=n;i++){
            int r1=get(a[i].x);
            int r2=get(a[i].y);
            if(a[i].e){
                f[r1]=r2;  //就是我们的merge操作 
            }else if(r1==r2){
                printf("NO\n");
                flag=0;  //如果不满足条件，标记为否 
                break;
            }
        }
        if(flag)cout<<"YES"<<endl;
    }
    return 0;
}