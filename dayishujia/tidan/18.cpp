#include <bits/stdc++.h>
using namespace std;

vector<int> child[101];
int f[101];          // 父节点
int dep[101];        // 深度
int cnt[101];        // 每层结点数

int main() {
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        child[u].push_back(v);
        f[v] = u;               // 记录父节点
    }

    // BFS 计算深度、宽度，并填充 dep 数组
    queue<int> q;
    q.push(1);
    dep[1] = 1;
    f[1] = 0;
    int maxDep = 0, maxWidth = 0;

    while (!q.empty()) {
        int sz = q.size();          // 当前层的结点数
        maxWidth = max(maxWidth, sz);
        for (int i = 0; i < sz; ++i) {
            int t = q.front(); q.pop();
            maxDep = max(maxDep, dep[t]);
            for (int v : child[t]) {
                dep[v] = dep[t] + 1;
                q.push(v);
            }
        }
    }

    int x, y;
    cin >> x >> y;

    // 向上标记法求 LCA
    int vis[101] = {0};
    // 标记 x 到根的所有结点（包括 x 和根）
    for (int cur = x; cur != 0; cur = f[cur]) {
        vis[cur] = 1;
    }
    int lca = 1;  // 至少是根
    for (int cur = y; cur != 0; cur = f[cur]) {
        if (vis[cur]) {
            lca = cur;
            break;
        }
    }

    // 距离 = 2*(x到lca的向上边数) + (lca到y的向下边数)
    int dist = 2 * (dep[x] - dep[lca]) + (dep[y] - dep[lca]);

    cout << maxDep << "\n";
    cout << maxWidth << "\n";
    cout << dist << "\n";

    return 0;
}