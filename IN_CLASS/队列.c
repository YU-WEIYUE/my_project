#include <stdio.h>

// 循环队列最大容量
#define MAXSIZE 6

typedef struct
{
    int data[MAXSIZE];
    int front;   // 队头指针
    int rear;    // 队尾指针，指向即将存入的位置
}CirQueue;

// 初始化循环队列
void InitQueue(CirQueue *q)
{
    q->front = 0;
    q->rear  = 0;
}

// 判断队列是否为空
int IsEmpty(CirQueue *q)
{
    return q->front == q->rear;
}

// 判断队列是否满
// 预留一个空位区分空/满
int IsFull(CirQueue *q)
{
    return (q->rear + 1) % MAXSIZE == q->front;
}

// 入队
int EnQueue(CirQueue *q, int val)
{
    if(IsFull(q))
    {
        printf("队列已满，无法入队！\n");
        return 0;
    }
    q->data[q->rear] = val;
    q->rear = (q->rear + 1) % MAXSIZE;
    return 1;
}

// 出队
int DeQueue(CirQueue *q, int *val)
{
    if(IsEmpty(q))
    {
        printf("队列为空，无法出队！\n");
        return 0;
    }
    *val = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;
    return 1;
}

// 遍历输出队列所有元素
void ShowQueue(CirQueue *q)
{
    if(IsEmpty(q))
    {
        printf("当前队列：空\n");
        return;
    }
    printf("当前队列元素：");
    int i = q->front;
    while(i != q->rear)
    {
        printf("%d ", q->data[i]);
        i = (i + 1) % MAXSIZE;
    }
    printf("\n");
}

int main()
{
    CirQueue q;
    int ret, x;

    InitQueue(&q);
    printf("===== 循环队列演示 =====\n");

    // 批量入队
    EnQueue(&q, 11);
    EnQueue(&q, 22);
    EnQueue(&q, 33);
    EnQueue(&q, 44);
    ShowQueue(&q);

    // 出队
    DeQueue(&q, &x);
    printf("出队元素：%d\n", x);
    DeQueue(&q, &x);
    printf("出队元素：%d\n", x);
    ShowQueue(&q);

    // 利用循环特性：前面空了，继续入队
    EnQueue(&q, 55);
    EnQueue(&q, 66);
    ShowQueue(&q);

    // 测试队满
    EnQueue(&q, 77);
    EnQueue(&q, 88);

    // 清空出队测试队空
    while(!IsEmpty(&q))
    {
        DeQueue(&q, &x);
    }
    DeQueue(&q, &x);

    return 0;
}