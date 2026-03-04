#include <iostream>
#include <queue>
using namespace std;

int main() {
    // 小顶堆（优先队列），用于每次取最小的两个节点
    priority_queue<int, vector<int>, greater<int>> q;
    // 输入权值：5 9 12 13 16
    int weights[] = {5, 9, 12, 13, 16};
    int n = sizeof(weights) / sizeof(int);
    for (int i = 0; i < n; ++i) {
        q.push(weights[i]);
    }
    
    int total_wpl = 0;  // 总带权路径长度（最小代价）
    while (q.size() > 1) {
        // 取最小的两个节点
        int a = q.top(); q.pop();
        int b = q.top(); q.pop();
        // 合并成新节点，代价累加（新节点权值=a+b）
        int new_node = a + b;
        total_wpl += new_node;
        q.push(new_node);
    }
    
    // 输出总WPL：124（和手动计算一致）
    cout << "最小带权路径长度：" << total_wpl << endl;
    return 0;
}