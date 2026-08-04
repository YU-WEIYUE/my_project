#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long

typedef struct node {
    ll id;
    node* left;
    node* right;
} node;

ll n;
vector<ll> delList;
vector<node*> pos;   // pos[id] = 指向该 id 节点的指针

node* init() {
    node* head = (node*)malloc(sizeof(node));
    head->left = NULL;
    head->right = NULL;
    cin >> n;
    return head;
}

int main() {
    node* head = init();
    head->id = 1;
    pos.resize(n + 1);      // 下标从 1 开始
    pos[1] = head;

    // ---------- 构建双向链表 ----------
    for (ll i = 2; i <= n; i++) {
        ll x, f;
        cin >> x >> f;

        node* p = pos[x];   // O(1) 定位到已存在的节点
        node* next = (node*)malloc(sizeof(node));
        next->id = i;
        next->left = next->right = NULL;   // 必须初始化！

        if (f) {  // 插入到 p 的右侧
            next->left = p;
            next->right = p->right;
            if (p->right != NULL)
                p->right->left = next;
            p->right = next;
        } else {  // 插入到 p 的左侧
            next->right = p;
            next->left = p->left;
            if (p->left != NULL)
                p->left->right = next;
            else
                head = next;   // 更新头节点
            p->left = next;
        }
        pos[i] = next;   // 记录新节点位置
    }

    // ---------- 读取待删除的 ID ----------
    ll m;
    cin >> m;
    for (ll i = 0; i < m; i++) {
        ll k;
        cin >> k;
        delList.push_back(k);
    }

    // ---------- 去重 ----------
    sort(delList.begin(), delList.end());
    delList.erase(unique(delList.begin(), delList.end()), delList.end());

    // ---------- 删除节点 ----------
    for (ll id : delList) {
        if (id < 1 || id > n) continue;
        node* p = pos[id];
        if (p == NULL) continue;   // 可能已被删除

        // 安全地断开前后链接
        if (p->left != NULL)
            p->left->right = p->right;
        else
            head = p->right;       // 删除的是头节点

        if (p->right != NULL)
            p->right->left = p->left;

        free(p);
        pos[id] = NULL;            // 标记为已删除
    }

    // ---------- 输出剩余节点 ----------
    node* p = head;
    while (p != NULL) {
        cout << p->id << " ";
        p = p->right;
    }

    return 0;
}