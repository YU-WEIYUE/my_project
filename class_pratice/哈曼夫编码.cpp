#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 2005; // 2 倍空间

int n, cnt;
pair<int, int> e[MAXN];
string s[MAXN], chain[MAXN], cur = "";
struct node{
	int w, id;
	bool operator<(node x) const{
		return w > x.w; // 坑：优先队列默认大顶堆，需要小顶堆，因此反向定义
	}
};

void search(int u){ // 遍历分配编号，左子树 0，右子树 1
	if(u <= n){ // 是原有节点
		chain[u] = cur;
		return;
	}
	cur += '0';
	search(e[u].first);
	cur.pop_back();
	cur += '1';
	search(e[u].second);
	cur.pop_back();
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	cin >> n;
	cnt = n;
	priority_queue<node> q;
	for(int i = 1, w; i <= n; ++ i)
		cin >> s[i] >> w, q.push({w, i});
	if(n == 1){ // n = 1 时 search 会算出空字符串，故特殊处理
		cout << s[1] << " 0";
		return 0;
	}
	while(q.size() > 1){ // 合并果子模板，至少 2 个才能取！
		node x = q.top(); q.pop();
		node y = q.top(); q.pop();
		e[++ cnt] = {x.id, y.id};
		q.push({x.w + y.w, cnt});
	}
	search(cnt);
	for(int i = 1; i <= n; ++ i)
		cout << s[i] << " " << chain[i] << "\n";
	
	return 0;
}
