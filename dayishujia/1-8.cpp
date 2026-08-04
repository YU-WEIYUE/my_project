#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 2005;
int n, tot; // tot 用来记录边的数量

// 1. 边的结构体，保持不变
struct Edge {
    ll x, y1, y2;
    int val;
    bool operator <(const Edge e){
        return x<e.x;
    }
};
// 2. 线段树节点结构体，需要你补充
struct SegTree {
    ll len;
    int cnt;
    ll l,r;
} tree[MAXN << 3]; // 数组大小 4 * 2N 足够了

vector<Edge> edges; // 全局声明，但不在这里指定大小

vector<ll> ys;      // 用于离散化 y 坐标

inline ll ls(ll p){
    return p<<1;
}
inline ll rs(ll p){
    return p<<1|1;
}
// 线段树基本操作函数声明
void build(int p, int l, int r) {
    tree[p].l=l;
    tree[p].r=r;
    tree[p].cnt = 0;
    tree[p].len = 0;
    if(l==r)return;
    ll mid=(l+r)>>1;
    build(ls(p),l,mid);
    build(rs(p),mid+1,r);
}

void push_up(int p) {
    
}

void update(int p, int l, int r, int L, int R, int val) {
    // 待你实现
}

int main() {
    cin >> n;
    // 读入矩形，拆解成边，存入 edges 和 ys
    // edges 可以用 push_back，ys 也用 push_back
    
    // 离散化 ys：排序 + 去重

    // 按 x 排序所有边

    // 扫描过程，累加面积

    return 0;
}