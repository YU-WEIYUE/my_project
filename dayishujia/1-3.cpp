#include<bits/stdc++.h>
#define itn int 
#define ll long long
using namespace std;
vector<ll> stone, value, le, ri;
ll m, n, s, big, small = 1000000;
itn main() {
    cin >> n >> m >> s;
    for (ll i = 0; i < n; i++) {
        ll j, k;
        cin >> j >> k;
        if (j > big) big = j;
        if (j < small) small = j;
        stone.push_back(j);
        value.push_back(k);
    }
    for (ll i = 0; i < m; i++) {
        ll l, r;
        cin >> l >> r;
        le.push_back(l);
        ri.push_back(r);
    }

    ll l = 0, r = big + 1;        // W 的搜索范围
    ll ans = LLONG_MAX;

    while (l <= r) {
        ll w = (l + r) / 2;

        // ---- 用前缀和快速计算 y(w) ----
        vector<ll> cnt(n + 1, 0), sum(n + 1, 0);
        for (ll i = 1; i <= n; i++) {
            cnt[i] = cnt[i - 1];
            sum[i] = sum[i - 1];
            if (stone[i - 1] >= w) {
                cnt[i]++;
                sum[i] += value[i - 1];
            }
        }
        ll y = 0;
        for (ll i = 0; i < m; i++) {
            ll L = le[i], R = ri[i];
            ll c = cnt[R] - cnt[L - 1];
            ll sv = sum[R] - sum[L - 1];
            y += c * sv;
        }
        // --------------------------------

        ans = min(ans, llabs(s - y));   // 更新最小差值

        if (y > s)
            l = w + 1;    // y 太大，需要增大 W
        else if (y < s)
            r = w - 1;    // y 太小，需要减小 W
        else
            break;        // 差值为 0，已是最优
    }

    cout << ans << "\n";
    return 0;
}