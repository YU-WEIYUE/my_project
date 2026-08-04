#include<iostream>
#include<cstdio>
#define MAXN 1000001       // 数组最大长度
#define ll long long        // 用 ll 代替 long long，写起来更方便
using namespace std;

ll a[MAXN],tag[MAXN<<2],ans[MAXN<<2];
ll n,m;

inline ll ls(ll x){
    return x<<1;
}

inline ll rs(ll x){
    return x<<1|1;
}

void scan(){
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
}

inline void push_up(ll p){
    ans[p]=ans[ls(p)]+ans[rs(p)];
}

inline void build(ll p,ll l,ll r){
    if(l==r){
        ans[p]=a[l];return;
    }
    ll mid=l+(r-l)/2;
    build(ls(p),l,mid);
    build(rs(p),mid+1,r);
    push_up(p);
}

inline void f(ll l,ll r,ll p,ll k){
    tag[p]+=k;
    ans[p]+=(r-l+1)*k;
}

void push_down(ll p,ll l,ll r){
    if(tag[p]){
        ll mid=l+(r-l)/2;
        f(l,mid,ls(p),tag[p]);
        f(mid+1,r,rs(p),tag[p]);
        tag[p]=0;
    }
}

void update(ll l,ll r,ll p,ll k,ll al,ll ar){//aimed left,aimed right
    if(al <= l && r <= ar){
        f(l,r,p,k);
        return;
    }
    push_down(p,l,r);
    ll mid=l+(r-l)/2;
    if(al<=mid)update(l,mid,ls(p),k,al,ar);
    if(mid<=ar)update(mid,r,rs(p),k,al,ar);
    push_up(p);
}

ll search(ll l,ll r,ll p,ll al,ll ar){
    if(l>=al&&r<=ar)return ans[p];
    ll mid=l+(r-l)/2;
    push_down(p,l,r);
    ll re=0;
    if(mid<=ar)re+=search(l ,mid,ls(p),al,ar);
    if(mid>=al)re+=search(mid,r,rs(p),al,ar);
    return re;
}

int main(){
    scan();
    build(1,1,n);
    ll q,a,b,c;
    while(m--){
        cin>>q;
        switch(q){
            case 1:{
                cin>>a>>b>>c;
                update(1,n,1,c,a,b);
                break;
            }
            case 2:{
                cin>>a>>b;
                cout<<search(1,n,1,a,b)<<endl;
            }
        }
    }
    return 0;
}