/*----------头文件的引入---------*/
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include "string.h"
#include<windows.h>
#include<conio.h>
#include <time.h> 


/*----------预定义-----------*/

//定义布尔类型TRUE和FALSE
#define TRUE 1
#define FALSE 0

//定义函数返回值类型
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//数据元素类型定义
typedef int status;
typedef int ElemType; 

//定义顺序表的初始长度和每次扩展的长度
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

//单链表（链式结构）结点的定义
typedef struct LNode{  
      ElemType data;
      struct LNode *next;
}LNode,*LinkList;

//定义字体颜色切换
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
#define GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

//多链表的定义
typedef struct {
    struct {
        char name[30]; //集合的名称，最多可以有 30 个字符
        LinkList L; //指向链表头结点的指针
    }elem[30]; //集合中最多包含 30 个链表
    int length; //集合中包含的链表数目
}LISTS;
LISTS Lists;  //链表集合实例化为Lists对象
/*---------函数声明---------*/
void visit(int x){printf("%d"),x;}  //遍历函数时候调用的输出函数
status ClearList(LinkList &L);//清空表
status ListEmpty(LinkList L);//判定空表
status ListLength(LinkList L);//求表长
status GetElem(LinkList L,int i,ElemType &e);//获得元素
status LocateElem(LinkList L,ElemType e);//定位元素
status PriorElem(LinkList L,ElemType cur_e,ElemType &pre_e);//前驱
status NextElem(LinkList L,ElemType cur_e,ElemType &next_e);//后
status ListInsert(LinkList &L,int i,ElemType e);//插入元素
status ListDelete(LinkList &L,int i,ElemType &e);//删除元素
status ListTraverse(LinkList L, void (*visit)(int));//遍历线性表
status reverseList(LinkList L);   //翻转线性表
status RemoveNthFromEnd(LinkList L,int n);  //删除倒数第n个元素
status SaveList(LinkList L,char FileName[]);  //保存线性表到文件
status LoadList(LinkList &L,char FileName[]);  //从文件加载线性
status AddList(LISTS &Lists,char ListName[]);  //在Lists中增加一个名称为ListName的空线性表
status DeleteList(LISTS &Lists,char ListName[]);  //在Lists中删除一个名称为ListName的线性表
status LocateList(LISTS Lists,char ListName[]);  //在Lists中查找一个名称为ListName的线性表的位置
void SearchList(LISTS Lists);  //展示已经创建的线性表

void show();  //管理菜单

/*---------主函数---------*/
int main(){
    srand((unsigned)time(NULL));//设置随机数种子为当前时间，保证每次运行程序时生成的随机数序列不同
    int choice=1;//记录用户选择
    
    // 用下标记录当前选中的表，-1表示未选中
    int currentIndex = -1; 
    Lists.length=0;//初始化线性表集合长度为0，表示集合中没有默认线性表
    while(choice){
        show(); //显示菜单界面
        // 高亮显示当前选中的表名
        if(currentIndex != -1) {
            YELLOW;
            printf("\n");
            printf("╔═══════════════════════════════════════════════════════════╗\n");
            printf("                    当前选中表：%s                          \n", Lists.elem[currentIndex].name);
            printf("╚═══════════════════════════════════════════════════════════╝\n");
        }
        
        GREEN;
        printf("\n请输入您的选择：");

        YELLOW;
        scanf("%d",&choice);//获取用户选择
        switch(choice){
            // ========== 系统操作 ==========
            case 0:
                //退出系统
                GREEN;
                printf("感谢使用线性表系统！再见！\n");
                printf("输入任意键退出...");
                _getch();
                return 0;
            case 1:
                //初始化线性表
                {
                    char ListName[30];
                    GREEN;
                    printf("请输入要创建的线性表名称（最多30个字符）：");
                    YELLOW;
                    scanf("%s",ListName);
                    if(AddList(Lists,ListName)==OK){
                        WHITE;printf("线性表【%s】创建成功！\n",ListName);
                        currentIndex = Lists.length - 1; // 自动选中新表
                    }
                    else{RED;printf("线性表【%s】创建失败！\n",ListName);}
                    break;
                }
            case 2:
                //销毁线性表
                {
                    char Listname[30];
                    GREEN;
                    printf("请输入要删除的线性表名称（最多30个字符）：");
                    YELLOW;
                    scanf("%s",Listname);
                    if(DeleteList(Lists,Listname)==OK){
                        WHITE;printf("线性表【%s】删除成功！\n",Listname);
                        // 如果删除的是当前选中的表，重置 currentIndex
                        if(currentIndex != -1 && strcmp(Lists.elem[currentIndex].name, Listname) == 0) {
                            currentIndex = -1;
                        }
                    }
                    else{RED;printf("线性表【%s】删除失败！\n",Listname);}
                    break;
                }
                case 3:
                //查找线性表
                {
                    char ListName[30];
                    GREEN;
                    printf("请输入要查找的线性表名称（最多30个字符）：");
                    YELLOW;
                    scanf("%s",ListName);
                    int index = LocateList(Lists, ListName);
                    if(index != -1) {
                        currentIndex = index - 1; // LocateList 返回的是逻辑序号，数组下标需要减1
                    }
                    break;
                }
            }
        }
}

status AddList(LISTS &Lists,char ListName[])  //1.在Lists中增加一个名称为ListName的空线性表
{
    for(int i=0;i<Lists.length;i++){
        if(strcmp(Lists.elem[i].name,ListName)==0){  //如果集合中已经存在同名的线性表
            RED;
            printf("集合中已经存在名称为【%s】的线性表了，无法创建同名的线性表\n", ListName);
            return ERROR;  //返回错误
        }
    }
    // 如果集合中不存在同名的线性表，则创建新的线性表
    if(Lists.length < 30){  // 假设最多可以有30个线性表
        strcpy(Lists.elem[Lists.length].name, ListName);
        Lists.elem[Lists.length].L = NULL;  // 初始化链表指针
        Lists.length++;  // 增加线性表数目
        return OK;  // 返回成功
    }
    RED;
    printf("线性表集合已满，无法添加新表！\n");
    return OVERFLOW;  // 返回错误
}

status DeleteList(LISTS &Lists,char ListName[]) //2.在Lists中删除一个名称为ListName的线性表
{
    for(int i=0;i<Lists.length;i++){
        if(strcmp(Lists.elem[i].name,ListName)==0){  // 如果集合中存在名称为ListName的线性表
            // 将该线性表从集合中删除
            for(int j=i;j<Lists.length-1;j++){
                Lists.elem[j] = Lists.elem[j+1];
            }
            Lists.length--;  // 减少线性表数目
            return OK;  // 返回成功
        }
    }
    RED;
    printf("未找到名称为【%s】的线性表！\n", ListName);
    return ERROR;  // 返回错误
}

status LocateList(LISTS Lists,char ListName[]) //3.在Lists中查找一个名称为ListName的线性表的位置
{
    for(int k=0;k<Lists.length;k++){
        if(strcmp(Lists.elem[k].name,ListName)==0){  // 如果集合中存在名称为ListName的线性表
            return k + 1;  // 返回逻辑序号
        }
    }
    return -1;  // 未找到，返回-1
}