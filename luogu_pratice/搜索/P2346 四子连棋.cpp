#include <cstdlib>
#include <iostream>
#include <cstdio>  // 显式包含C标准输入输出头文件
using namespace std;

#define MaxVertexNum 26
#define DIRECTED true  // 控制是否为有向图
#define MaxSize 50

// 边结点结构
typedef struct ArcNode {
    int adjvex;          // 边指向的顶点下标
    int weight;          // 权值
    struct ArcNode *next;// 下一条边
} ArcNode;

// 顶点结点结构
typedef struct VNode {
    char data;           // 顶点值
    ArcNode *first;      // 第一条边
} VNode, AdjList[MaxVertexNum];

// 邻接表图结构
typedef struct {
    AdjList adjList;
    int vexnum, arcnum;  // 顶点数、边数
} ALGraph;

// 循环队列结构（BFS用）
typedef struct {
    int data[MaxSize];
    int front, rear;
} SqQueue;

// 全局访问标记（简化参数传递）
bool visited[MaxVertexNum];

// ========== 工具函数 ==========
// 队列初始化
void Queue_Init(SqQueue &Q) {
    Q.front = Q.rear = 0;
}

// 判断队列空
bool Queue_Empty(SqQueue Q) {
    return Q.front == Q.rear;
}

// 入队
bool Queue_En(SqQueue &Q, int e) {
    if ((Q.rear + 1) % MaxSize == Q.front) return false;
    Q.data[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}

// 出队
bool Queue_De(SqQueue &Q, int &e) {
    if (Queue_Empty(Q)) return false;
    e = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}

// ========== 核心功能 ==========
// 创建邻接表
void ALGraph_Create(ALGraph &G) {
    // 初始化顶点边指针
    for (int i = 0; i < MaxVertexNum; i++)
        G.adjList[i].first = nullptr;  // C++用nullptr代替NULL

    // 输入顶点数、边数（改用C++的cin，避免格式问题）
    cout << "输入顶点数 边数：";
    cin >> G.vexnum >> G.arcnum;

    // 输入顶点值
    for (int i = 0; i < G.vexnum; i++) {
        cout << "顶点" << i << "：";
        cin >> G.adjList[i].data;
    }

    // 输入边（vi->vj，权值）
    int vi, vj, w;
    for (int i = 0; i < G.arcnum; i++) {
        cout << "边" << i << "(vi vj w)：";
        cin >> vi >> vj >> w;

        // 头插法创建边（C++用new代替malloc）
        ArcNode *p = new ArcNode();  // 注意加括号初始化
        p->adjvex = vj;
        p->weight = w;
        p->next = G.adjList[vi].first;
        G.adjList[vi].first = p;

        // 无向图则添加反向边
        if (!DIRECTED) {
            ArcNode *q = new ArcNode();
            q->adjvex = vi;
            q->weight = w;
            q->next = G.adjList[vj].first;
            G.adjList[vj].first = q;
        }
    }
}

// 打印邻接表
void ALGraph_Show(ALGraph G) {
    cout << "\n邻接表：\n";
    for (int i = 0; i < G.vexnum; i++) {
        cout << G.adjList[i].data << " ";
        ArcNode *p = G.adjList[i].first;
        while (p != nullptr) {
            cout << "->(" << p->adjvex << "," << p->weight << ") ";
            p = p->next;
        }
        cout << endl;
    }
}

// 深度优先遍历（递归）
void DFS(ALGraph G, int v) {
    cout << G.adjList[v].data << " ";  // 访问顶点值（更直观）
    visited[v] = true;
    ArcNode *p = G.adjList[v].first;
    while (p != nullptr) {
        if (!visited[p->adjvex])
            DFS(G, p->adjvex);
        p = p->next;
    }
}

// 广度优先遍历
void BFS(ALGraph G, int v) {
    SqQueue Q;
    Queue_Init(Q);
    cout << G.adjList[v].data << " ";
    visited[v] = true;
    Queue_En(Q, v);

    while (!Queue_Empty(Q)) {
        Queue_De(Q, v);
        ArcNode *p = G.adjList[v].first;
        while (p != nullptr) {
            if (!visited[p->adjvex]) {
                cout << G.adjList[p->adjvex].data << " ";
                visited[p->adjvex] = true;
                Queue_En(Q, p->adjvex);
            }
            p = p->next;
        }
    }
}

// 遍历整个图（处理非连通图）
void Traverse(ALGraph G, void (*func)(ALGraph, int)) {
    for (int i = 0; i < G.vexnum; i++)
        visited[i] = false;
    
    cout << "\n遍历结果";
    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i])
            func(G, i);
    }
    cout << endl;
}

// ========== 主函数 ==========
int main() {
    ALGraph G;
    ALGraph_Create(G);   // 创建图
    ALGraph_Show(G);     // 打印邻接表
    Traverse(G, DFS);    // DFS遍历
    Traverse(G, BFS);    // BFS遍历
    
    // 可选：释放内存（避免内存泄漏）
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.adjList[i].first;
        while (p != nullptr) {
            ArcNode *tmp = p;
            p = p->next;
            delete tmp;
        }
    }
    
    return 0;
}