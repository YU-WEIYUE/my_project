#include<stdio.h>
#include<stdlib.h>

//静态分配
#define maxleng 100
typedef struct 
{int elem[maxleng];//下标:0,1,...,maxleng-1
int length;//表长
} SqList;
SqList LA;

//动态分配
typedef struct
{ int *elem; //存储空间或动态数组基地址
int length; //表长（表中有多少个元素）
int listsize; //当前分配的存储容量,以sizeof(ElemType)为单位
} SqListq;
SqListq LB;

