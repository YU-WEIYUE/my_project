#include <iostream>
#include <queue>

using namespace std;

// 建议将数组开大一点点防止越界，51 改为 55
int n, m, ans;
int mp[55][55]; 
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

void bfs(int x, int y) {
    queue<pair<int, int>> que;
    que.push(make_pair(x, y));
    mp[x][y] = 0; // 【关键】入队立刻修改地图，防止重复进入

    while (!que.empty()) {
        pair<int, int> now = que.front();
        que.pop();

        for (int i = 0; i < 4; i++) {
            int nx = now.first + dx[i];
            int ny = now.second + dy[i];

            // 这里的边界判断必须严格对应 n(行) 和 m(列)
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
                if (mp[nx][ny] == 1) {
                    mp[nx][ny] = 0; // 只要是连通的边界陆地，全部变成 0
                    que.push(make_pair(nx, ny));
                }
            }
        }
    }
}

int main() {
    // 习惯上：n 是行数，m 是列数
    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mp[i][j];
        }
    }

    // 1. 处理左右两边的边界
    for (int i = 1; i <= n; i++) {
        if (mp[i][1] == 1) bfs(i, 1);
        if (mp[i][m] == 1) bfs(i, m);
    }

    // 2. 处理上下两边的边界
    for (int j = 1; j <= m; j++) {
        if (mp[1][j] == 1) bfs(1, j);
        if (mp[n][j] == 1) bfs(n, j);
    }

    // 3. 统计剩下的 1（即被包围的部分）
    ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j] == 1) ans++;
        }
    }

    cout << ans << endl;
    return 0;
}