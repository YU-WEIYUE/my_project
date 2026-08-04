#include <stdio.h>
#include <string.h>
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
void preorder(char *in, char *post, int len) {
    if (len <= 0) return;
    
    char root = post[len - 1];          // 后序最后一个字符是根
    putchar(root);                      // 输出根（先序）
    
    // 在中序中找到根的位置
    int i;
    for (i = 0; i < len; i++) {
        if (in[i] == root) break;
    }
    
    // 左子树长度 = i，右子树长度 = len - i - 1
    preorder(in, post, i);                           // 左子树
    preorder(in + i + 1, post + i, len - i - 1);     // 右子树
}

int main() {
    char in[10], post[10];   // 节点数 ≤ 8，多开一点
    scanf("%s %s", in, post);
    preorder(in, post, strlen(in));
    return 0;
}