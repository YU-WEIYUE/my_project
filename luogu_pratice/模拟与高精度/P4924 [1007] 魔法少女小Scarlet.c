#include<stdio.h>
#include<stdlib.h>
// 定义矩阵最大尺寸，避免魔法数字
#define MAX_SIZE 501
int arr[MAX_SIZE][MAX_SIZE], temp[MAX_SIZE][MAX_SIZE];
int a = 1;

// 旋转子矩阵函数：x,y为中心，r为半径（子矩阵大小2r+1），z=0顺时针，z=1逆时针
void spin() {
    int x, y, r, z;
    scanf("%d %d %d %d", &x, &y, &r, &z);
    
    // 第一步：先将原矩阵的子矩阵区域复制到temp，避免旋转时覆盖原数据
    for (int i = x - r; i <= x + r; i++) {
        for (int j = y - r; j <= y + r; j++) {
            temp[i][j] = arr[i][j];
        }
    }
    
    // 计算子矩阵的边长
    int size = 2 * r + 1;
    // 第二步：根据旋转方向，用temp（原数据）更新arr（新数据）
    switch (z) {
        case 0: // 顺时针旋转90度
            for (int i = x - r; i <= x + r; i++) {
                for (int j = y - r; j <= y + r; j++) {
                    // 坐标转换：将子矩阵相对坐标转换为旋转后的坐标
                    // 1. 计算相对于中心(x,y)的偏移量
                    int dx = i - x;
                    int dy = j - y;
                    // 2. 顺时针旋转90度：(dx, dy) → (dy, -dx)
                    int new_i = x + dy;
                    int new_j = y - dx;
                    // 3. 用原数据(temp)赋值给新位置(arr)
                    arr[new_i][new_j] = temp[i][j];
                }
            }
            break;
        case 1: // 逆时针旋转90度
        
            for (int i = x - r; i <= x + r; i++) {
                for (int j = y - r; j <= y + r; j++) {
                    // 1. 计算相对于中心(x,y)的偏移量
                    int dx = i - x;
                    int dy = j - y;
                    // 2. 逆时针旋转90度：(dx, dy) → (-dy, dx)
                    int new_i = x - dy;
                    int new_j = y + dx;
                    // 3. 用原数据(temp)赋值给新位置(arr)
                    arr[new_i][new_j] = temp[i][j];
                }
            }
            break;
    }
}

int main() {
    int n, m;
    // 输入矩阵大小n，旋转操作次数m
    scanf("%d %d", &n, &m);

    // 初始化n×n矩阵：元素从1开始递增
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            arr[i][j] = a++;
            temp[i][j] = arr[i][j]; // 初始化temp（可选，spin中会重新复制）
        }
    }

    // 执行m次旋转操作
    for (int i = 0; i < m; i++) {
        spin();
    }

    // 输出最终矩阵
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}