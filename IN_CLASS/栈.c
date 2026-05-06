#include <stdio.h>
#include <string.h>

#define MAXSIZE 20

char stack[MAXSIZE];
int top = -1;

void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }

int main() {
    char str[] = "hello";
    int i;

    // 入栈：h e l l o
    for (i = 0; i < strlen(str); i++)
        push(str[i]);

    // 出栈：o l l e h
    printf("反转后：");
    for (i = 0; i < strlen(str); i++)
        printf("%c", pop());
    printf("\n");
    return 0;
    scanf("%d"); // 防止程序立即退出
}