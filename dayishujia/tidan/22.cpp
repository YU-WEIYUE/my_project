#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int N = 10005;
const int INF = 0x3f3f3f3f;

int n, m, s;
vector<pair<int, int>> G[N]; // 邻接表
int dis[N];

void dijkstra() {
    fill(dis, dis + N, INF);
    dis[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second;
        pq.pop();
        if (d != dis[u]) continue; // 懒惰删除
        for (auto &e : G[u]) {
            int v = e.first, w = e.second;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pq.push({dis[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> s;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({v, w});
    }
    dijkstra();
    for (int i = 1; i <= n; ++i) {
        if (dis[i] == INF) cout << 2147483647;
        else cout << dis[i];
        cout << " \n"[i == n];
    }
    return 0;
}