#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 205;
const int INF = 0x3f3f3f3f; // 表示无穷大（足够大的数）

int r[MAXN][MAXN]; // r[i][j]存储i→j的租金
int dp[MAXN];      // dp[i]表示1→i的最少租金

int main() {
    int n;
    cin >> n;
    
    // 第一步：初始化租金表（先全部设为无穷大，再填输入值）
    memset(r, INF, sizeof(r));
    for (int i = 1; i < n; ++i) { // i从1到n-1
        for (int j = i+1; j <= n; ++j) { // j从i+1到n
            cin >> r[i][j];
        }
    }
    
    // 第二步：初始化dp数组（全部设为无穷大）
    memset(dp, INF, sizeof(dp));
    dp[1] = 0; // 起点1的租金为0
    
    // 第三步：动态规划计算dp[i]
    for (int i = 2; i <= n; ++i) { // 计算从2到n的最少租金
        for (int j = 1; j < i; ++j) { // 枚举所有能到i的j（j < i）
            // 状态转移：取最小值
            dp[i] = min(dp[i], dp[j] + r[j][i]);
        }
    }
    
    // 第四步：输出答案（1→n的最少租金）
    cout << dp[n] << endl;
    
    return 0;
}