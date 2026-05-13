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
    }elem[31]; //集合中最多包含 30 个链表
    int length; //集合中包含的链表数目
}LISTS;

LISTS Lists;  //链表集合实例化为Lists对象


/*---------函数声明---------*/
void visit(int x){printf("%d ",x);}  //遍历函数时候调用的输出函数
void show();//展示菜单
void showLists();//显示链表集合
status DestroyList(LinkList& L); //销毁
status ClearList(LinkList& L); //清空
status ListEmpty(LinkList &L);  //判空
status ListLength(LinkList L);  //求长度
status GetElem(LinkList L,int i,ElemType &e);  //获取元素
status LocateElem(LinkList &L,ElemType e);  //判断位置
status PriorElem(LinkList L,ElemType e,ElemType &pre);  //获得前驱
status NextElem(LinkList L,ElemType e,ElemType &next);  //获得后继
status ListInsert(LinkList &L,int i,ElemType e);  //插入元素
status ListDelete(LinkList &L,int i,ElemType &e);  //删除元素
status ListTraverse(LinkList L); //遍历输出
status DeleteList(LISTS &Lists,char ListName[]); //在Lists中删除一个名称为ListName的链表
status LocateList(LISTS Lists,char ListName[]); //在Lists中查找一个名称为ListName的链表的位置
status InitList(LISTS &Lists,char ListName[]);  //在Lists中增加一个名称为ListName的空链表
status ListReverse(LinkList &L);//链表翻转
status RemoveNthFromEnd(LinkList &L,int n);//删除链表的倒数第n个结点
status SortList(LinkList &L);//链表排序
void SaveList(LinkList L,char name[]);//把链表保存到文件中
status ReadListFromFile(LinkList &L, char name[]); //从文件中读取数据创建链表

// ↓↓↓ 你要的新增5个函数 ↓↓↓
status CreateRandomList10(LinkList &L);         // 1.生成10个随机数
status RemoveDuplicate(LinkList &L);            // 2.链表去重
int MaxSubArray(LinkList L);                    // 3.最大连续子串和
status IntersectionAllLists(LISTS &Lists);      // 4.求所有表交集
status MergeTwoListSort(LinkList L1, LinkList L2, LinkList &L3); // 5.合并两个链表并排序


//主函数

int main(){
    int choice=1;//初始化用户选择
    int currentIndex = -1; //初始化链表指针，-1表示目前没有选中的链表
    Lists.length=0;//初始化链表集合
    srand((unsigned)time(NULL)); //随机数种子

    while(choice){
        show();//展示菜单界面
        // 高亮显示当前选中的表名
        if(currentIndex != -1) {
            YELLOW;
            printf("\n");
            printf("╔═══════════════════════════════════════════════════════════╗\n");
            printf("                    当前选中链表：%s                          \n", Lists.elem[currentIndex].name);
            printf("╚═══════════════════════════════════════════════════════════╝\n");
        }

        GREEN;
        printf("\n请输入您的选择：");
        YELLOW;
        scanf("%d",&choice);//获取用户选择
        switch(choice){
            case 0:{
                GREEN;
                printf("感谢使用链表系统！再见！\n");
                printf("输入任意键退出...");
                _getch();
                return 0;
            }

            case 1:{ //查看当前线性表集合中有哪些线性表
                showLists();
                break;
            }

            case 2:{//创建新链表  
                char ListName[30];
                GREEN;
                printf("请输入要创建的线性表名称：");
                YELLOW;
                scanf("%s",ListName);
                if(InitList(Lists,ListName)==OK){
                    WHITE;
                    printf("线性表【%s】创建成功！\n",ListName);
                    currentIndex=Lists.length-1;// 自动选中新表
                }
                else {
                    RED;
                    printf("线性表【%s】创建失败！\n",ListName);
                }
                break;
            }

            case 3:{//查找并选中链表
                char Listname[30];
                GREEN;
                printf("请输入要查找的线性表名称：");
                YELLOW;
                scanf("%s",Listname);
                currentIndex=LocateList(Lists,Listname);
                if(currentIndex==-1){
                    RED;
                    printf("线性表【%s】查找失败！\n",Listname);
                    break;
                }
                else {
                    WHITE;
                    printf("线性表【%s】查找成功！现在可以对其进行操作了！\n", Lists.elem[currentIndex].name);
                }
                break;
            }

            case 4:{//删除某一个特定链表
                char ListName[30];
                GREEN;
                printf("请输入要删除的线性表名称：");
                YELLOW;
                scanf("%s",ListName);
                int delIndex = LocateList(Lists, ListName);
                if(DeleteList(Lists,ListName)==OK){
                    WHITE;
                    printf("线性表【%s】删除成功！\n",ListName);
                }
                else {
                    RED;
                    printf("线性表【%s】删除失败！\n",ListName);
                    break;
                }
                if(delIndex==currentIndex)currentIndex=-1;
                else if(delIndex<currentIndex)currentIndex--;
                break;
            }

            case 5:{//删除当前链表
                if(currentIndex==-1){
                    RED;
                    printf("请先使用功能键 3 选中一个线性表！\n");
                    break;
                }
                if(DestroyList(Lists.elem[currentIndex].L)==OK){
                    WHITE;printf("线性表【%s】销毁成功！\n", Lists.elem[currentIndex].name);
                    currentIndex=-1;
                }
                else{
                    RED;
                    printf("线性表不存在，销毁失败！\n");
                }
                break;
            }

            case 6:{//清空当前链表
                if(currentIndex==-1){
                    RED;
                    printf("请先使用功能键 3 选中一个线性表！\n");
                    break;
                }
                if(ClearList(Lists.elem[currentIndex].L)==OK){
                    WHITE;
                    printf("线性表【%s】清空成功！\n", Lists.elem[currentIndex].name);
                }
                else{
                    RED;
                    printf("线性表不存在，无法清空！\n");
                }
                break; 
            }

            case 7:{// 判断当前链表是否为空
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                if(ListEmpty(Lists.elem[currentIndex].L)){RED;printf("线性表【%s】为空！\n", Lists.elem[currentIndex].name);}
                else {WHITE;printf("线性表【%s】不为空！\n", Lists.elem[currentIndex].name);}
                break;
            }

            case 8:{//获取当前链表长度
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                int res=ListLength(Lists.elem[currentIndex].L);
                if(res==INFEASIBLE){
                    RED;printf("线性表不存在，无法求长度！\n");break;
                }
                else {
                    WHITE;
                    printf("线性表【%s】长度为：%d\n", Lists.elem[currentIndex].name,res);
                    break;
                }
            }

            case 9:{// 获取指定位置的元素
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                int i;
                GREEN;
                printf("请输入要获取的元素位置编号（从1开始）：");
                YELLOW;
                scanf("%d",&i);
                ElemType e;
                if(GetElem(Lists.elem[currentIndex].L,i,e)==OK){WHITE;printf("线性表【%s】%d号位置的元素为：%d\n", Lists.elem[currentIndex].name, i, e);}
                else{RED;printf("位置无效，获取元素失败！\n");}
                break;
            }

            case 10:{//定位元素
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                int e;
                GREEN;
                printf("请输入要定位的元素值：");
                YELLOW;
                scanf("%d",&e);
                int pos=LocateElem(Lists.elem[currentIndex].L,e);
                if(pos>0){WHITE;printf("线性表【%s】中元素%d在第%d号位置！\n", Lists.elem[currentIndex].name, e, pos);}
                else if(pos==0){RED;printf("线性表【%s】中没有找到元素%d！\n", Lists.elem[currentIndex].name, e);}
                else{RED;printf("线性表不存在，无法定位元素！\n");}    
                break;
            }

            case 11:{//获取元素前驱
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                int e;
                GREEN;
                printf("请输入要获取前驱的元素值：");
                YELLOW;
                scanf("%d",&e);
                ElemType pre;
                if(PriorElem(Lists.elem[currentIndex].L,e,pre)==OK){WHITE;printf("线性表【%s】中元素%d的前驱是：%d\n", Lists.elem[currentIndex].name, e, pre);}
                else if(PriorElem(Lists.elem[currentIndex].L,e,pre)==ERROR){RED;printf("线性表【%s】中元素%d没有前驱！\n", Lists.elem[currentIndex].name, e);}
                else{RED;printf("线性表不存在，无法获取前驱！\n");}
                break;
            }

            case 12:{//获取后继
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                int e;
                GREEN;
                printf("请输入要获取后继的元素值：");
                YELLOW;
                scanf("%d",&e);
                ElemType next;
                if(NextElem(Lists.elem[currentIndex].L,e,next)==OK){WHITE;printf("线性表【%s】中元素%d的后继是：%d\n", Lists.elem[currentIndex].name, e, next);}
                else if(NextElem(Lists.elem[currentIndex].L,e,next)==ERROR){RED;printf("线性表【%s】中元素%d没有后继！\n", Lists.elem[currentIndex].name, e);}
                else{RED;printf("线性表不存在，无法获取后继！\n");}
                break;
            }

            case 13:{//插入元素
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                int i,e;
                GREEN;
                printf("请输入要插入的元素值：");
                YELLOW;
                scanf("%d",&e);
                GREEN;
                printf("请输入要插入的位置：");
                YELLOW;
                scanf("%d",&i);
                if(ListInsert(Lists.elem[currentIndex].L,i,e)==OK){WHITE;printf("线性表【%s】中元素%d插入成功！\n", Lists.elem[currentIndex].name, e);}
                else{RED;printf("元素%d插入失败！\n",e);}
                break;
            }
            
            case 14:{//删除元素
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                int i,e;
                GREEN;
                printf("请输入要删除的元素位置编号（从1开始）：");
                YELLOW;
                scanf("%d",&i);
                if(ListDelete(Lists.elem[currentIndex].L,i,e)==OK){WHITE;printf("线性表【%s】中元素%d删除成功！\n", Lists.elem[currentIndex].name, e);}
                else{RED;printf("位置%d删除失败！\n",i);}
                break;
            }

            case 15: {//遍历输出
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                if(ListTraverse(Lists.elem[currentIndex].L)==OK){WHITE;printf("\n线性表【%s】遍历成功！\n", Lists.elem[currentIndex].name);}
                else{RED;printf("线性表不存在，无法遍历输出！\n");}
               break; 
            }

            case 16:{//链表翻转
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                if(ListReverse(Lists.elem[currentIndex].L)==OK){
                    WHITE;
                    printf("线性表【%s】翻转完成！\n", Lists.elem[currentIndex].name);
                    break;
                }
                else {
                    RED;
                    printf("链表不存在!");
                }
                break;
            }

            case 17:{//删除链表的倒数第n个结点
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                int n;
                GREEN;
                printf("请问你想要删除掉倒数第几个节点？请输入：");
                YELLOW;
                scanf("%d",&n);
                if(RemoveNthFromEnd(Lists.elem[currentIndex].L,n)==OK){
                    WHITE;
                    printf("删除成功！");
                    break;
                }
                else{
                    RED;
                    printf("请检查此线性表是否为空，或删除位置是否合法！");
                    break;
                }
            }

            case 18:{//链表排序
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                if(SortList(Lists.elem[currentIndex].L)==OK){
                    WHITE;
                    printf("排序成功！");
                    break;
                }
                else {
                    RED;
                    printf("该线性表为空，无法操作！");
                    break;
                }
            }

            case 19:{// 将链表保存到文件中
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                GREEN;
                printf("请输入要保存的文件名：");
                char listname[30];
                YELLOW;
                scanf("%s",listname);
                SaveList(Lists.elem[currentIndex].L,listname);
                break;
            }

            case 20:{//读取文件以创建链表
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                char filename[30];
                GREEN;
                printf("请输入要读取的文件名：");
                YELLOW;
                scanf("%s",filename);
                if(ReadListFromFile(Lists.elem[currentIndex].L, filename) == OK){
                    WHITE;
                    printf("文件【%s】读取成功，数据已加载到链表【%s】中！\n", filename, Lists.elem[currentIndex].name);
                }
                break;
            }
            case 21:{
                if(currentIndex == -1){
                    RED;
                    printf("请先选中一个链表！\n");
                    break;
                }
                system("cls");
                BLUE;
                printf("==================== 附加功能 ====================\n");
                GREEN;
                printf("1. 生成10个随机数字链表\n");
                printf("2. 链表去重\n");
                printf("3. 求链表最大连续子串和\n");
                printf("4. 求当前所有链表的交集\n");
                printf("5. 合并两个链表并排序\n");
                printf("0. 返回主菜单\n");
                printf("==================================================\n");
                YELLOW;
                int op;
                printf("请选择：");
                scanf("%d",&op);

                if(op == 1){
                    CreateRandomList10(Lists.elem[currentIndex].L);
                    WHITE;
                    printf("生成10个随机数成功！\n");
                }
                else if(op == 2){
                    RemoveDuplicate(Lists.elem[currentIndex].L);
                    WHITE;
                    printf("去重完成！\n");
                }
                else if(op == 3){
                    int max = MaxSubArray(Lists.elem[currentIndex].L);
                    WHITE;
                    printf("最大连续子串和 = %d\n",max);
                }
                else if(op == 4){
                    IntersectionAllLists(Lists);
                }
                else if(op == 5){
                    char name2[30];
                    GREEN;
                    printf("请输入另一个链表名：");
                    YELLOW;
                    scanf("%s",name2);
                    int idx2 = LocateList(Lists,name2);
                    if(idx2 == -1){
                        RED;
                        printf("不存在！\n");
                        break;
                    }
                    char newName[30];
                    GREEN;
                    printf("请输入新链表名：");
                    YELLOW;
                    scanf("%s",newName);
                    InitList(Lists,newName);
                    MergeTwoListSort(Lists.elem[currentIndex].L, Lists.elem[idx2].L, Lists.elem[Lists.length-1].L);
                    WHITE;
                    printf("合并+排序完成！新表：%s\n",newName);
                }
                break;
            }

            default:{
                RED;
                printf("输入无效！\n");
                break;
            }

        }

        BLUE;
        printf("按任意键以继续操作......");
        _getch();
        system("cls");

    }
    system("pause>nul"); 
    return 0;

}


//具体函数实现

void show(){//展示菜单
    BLUE;   
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("                                        欢迎使用链表管理系统                                              \n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━  多链表集合管理 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("1. 查看当前链表集合列表\n");
    printf("2. 创建新链表\n");
    printf("3. 查找并选中链表\n");
    printf("4. 删除某一个链表\n");

    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 单链表基础操作 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("5. 销毁当前链表\n");
    printf("6. 清空当前链表\n");
    printf("7. 判断当前链表是否为空\n");
    printf("8. 获取当前链表长度\n");

    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 单链表元素操作 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("9. 获取指定位置的元素\n");
    printf("10. 定位元素位置\n");
    printf("11. 获取元素前驱\n");
    printf("12. 获取元素后继\n");
    printf("13. 插入元素\n");
    printf("14. 删除元素\n");
    printf("15. 遍历输出链表\n");

    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 单链表高级功能 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("16. 链表翻转\n");
    printf("17. 删除链表的倒数第n个结点\n");
    printf("18.链表排序 \n");

    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━      系统操作     ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("19. 将链表保存到文件中\n");
    printf("20.读取文件以创建链表\n");
    printf("21.附加功能\n");
    printf("0. 退出系统\n");
}


void showLists(){
    BLUE;
    printf("当前链表集合列表：\n");
    if(Lists.length==0){RED;printf("链表集合中没有任何链表！\n");return;}
    for(int i=0;i<Lists.length;i++){
        GREEN;
        printf("%d. %s\n",i+1,Lists.elem[i].name);
    }
}

status InitList(LISTS &Lists,char ListName[]) 
{
    for(int i=0;i<Lists.length;i++){
        if(strcmp(Lists.elem[i].name,ListName)==0){  
            RED;
            printf("集合中已经存在名称为【%s】的链表了，无法创建同名的链表\n", ListName);
            return ERROR; 
        }
    }
    if(Lists.length < 30){  
        strcpy(Lists.elem[Lists.length].name, ListName);
        Lists.elem[Lists.length].L = (LinkList)malloc(sizeof(LNode)); 
        if(Lists.elem[Lists.length].L == NULL) exit(OVERFLOW);
        Lists.elem[Lists.length].L->next = NULL; 
        Lists.length++; 
        return OK;
    }
    RED;
    printf("链表集合已满，无法添加新表！\n");
    return OVERFLOW;
}

status LocateList(LISTS Lists,char ListName[]) 
{
    for(int k=0;k<Lists.length;k++){
        if(strcmp(Lists.elem[k].name,ListName)==0){  
            return k; 
        }
    }
    return -1; 
}

status DeleteList(LISTS &Lists,char ListName[]) 
{
    for(int i=0;i<Lists.length;i++){
        if(strcmp(Lists.elem[i].name,ListName)==0){
            DestroyList(Lists.elem[i].L);
            for(int j=i;j<Lists.length-1;j++){
                Lists.elem[j] = Lists.elem[j+1];
            }
            Lists.length--;
            return OK;
        }
    }
    RED;
    printf("未找到名称为【%s】的链表！\n", ListName);
    return ERROR;
}

status DestroyList(LinkList& L) 
{
    if(L == NULL) return INFEASIBLE;
    LinkList p = L;
    while(p != NULL){
        LinkList temp = p;
        p = p->next;
        free(temp);
    }
    L = NULL;
    return OK;
}

status ClearList(LinkList& L)
{
    if(L == NULL) return INFEASIBLE;
    LinkList p = L->next;
    while(p != NULL){
        LinkList temp = p;
        p = p->next;
        free(temp);
    }
    L->next = NULL;
    return OK;
}

status ListEmpty(LinkList &L)
{
    if(L == NULL) return INFEASIBLE;
    if(L->next == NULL) return TRUE;
    return FALSE;
}

status ListLength(LinkList L)
{
    if(L==NULL)return INFEASIBLE;
    int length = 0;
    LinkList p = L->next;
    while(p != NULL){
        length++;
        p = p->next;
    }
    return length;
}

status GetElem(LinkList L,int i,ElemType &e)
{
    if(L==NULL)return INFEASIBLE;
    if(i<1 || i>ListLength(L))return ERROR;
    LinkList p = L->next;
    for(int j=1;j<i;j++){
        p = p->next;
    }
    e = p->data;
    return OK;
}

status LocateElem(LinkList &L,ElemType e)
{
    if(L==NULL)return INFEASIBLE;
    LinkList p = L->next;
    int position = 1;
    while(p != NULL){
        if(p->data == e) return position;
        p = p->next;
        position++;
    }
    return ERROR;
}

status PriorElem(LinkList L,ElemType e,ElemType &pre)
{
    if(L==NULL)return INFEASIBLE;
    LinkList p = L->next;
    LinkList preNode = L;
    while(p != NULL){
        if(p->data == e){
            if(preNode == L) return ERROR;
            pre = preNode->data;
            return OK;
        }
        preNode = p;
        p = p->next;
    }
    return ERROR;
}

status NextElem(LinkList L,ElemType e,ElemType &next)
{
    if(L==NULL)return INFEASIBLE;
    LinkList p = L->next;
    while(p != NULL){
        if(p->data == e){
            if(p->next == NULL) return ERROR;
            next = p->next->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}

status ListInsert(LinkList &L,int i,ElemType e)
{
    if(L==NULL)return INFEASIBLE;
    if(i<1||i>ListLength(L)+1)return ERROR;
    LinkList p=L;
    for(int j=0;j<i-1;j++){
        p=p->next;
    }
    LinkList newnode=(LinkList)malloc(sizeof(LNode));
    if(newnode==NULL)exit(OVERFLOW);
    newnode->data=e;
    newnode->next=p->next;
    p->next=newnode;
    return OK;
}

status ListDelete(LinkList &L,int i,ElemType &e)
{
    if(L==NULL)return INFEASIBLE;
    if(i<1||i>ListLength(L))return ERROR;
    LinkList p=L;
    for(int j=0;j<i-1;j++){
        p=p->next;
    }
    LinkList q=p->next;
    e=q->data;
    p->next=q->next;
    free(q);
    return OK;
}

status ListTraverse(LinkList L)
{
    if(L==NULL)return INFEASIBLE;
    LinkList p=L->next;
    while(p != NULL){
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

status ListReverse(LinkList &L)
{
    if(L==NULL)return INFEASIBLE;
    LinkList prev = NULL;
    LinkList current = L->next;
    while(current != NULL){
        LinkList next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    L->next = prev;
    return OK;
}

status RemoveNthFromEnd(LinkList &L,int n)
{
    if(L==NULL)return INFEASIBLE;
    int len=ListLength(L);
    if(n<1||n>len)return ERROR;
    
    LinkList fast=L,low=L;
    for(int i=0;i<n;i++){
        fast=fast->next;
    }
    while(fast->next!=NULL){
        fast=fast->next;
        low=low->next;
    }
    
    LinkList tmp=low->next;
    low->next=tmp->next;
    free(tmp);
    return OK;
}

status SortList(LinkList &L) {
    if (L == NULL || L->next == NULL || L->next->next == NULL)
        return OK;  // 空表或只有一个节点，无需排序

    LinkList sorted = L->next;      // 初始：第一个节点为已排序部分
    LinkList unsorted = sorted->next; // 第二个节点开始为未排序部分
    sorted->next = NULL;            // 断开，形成独立的已排序链

    while (unsorted != NULL) {
        LinkList cur = unsorted;    // 取出当前要插入的节点
        unsorted = unsorted->next;  // 提前保存下一个节点

        // 寻找插入位置
        LinkList p = L;
        while (p->next != NULL && p->next->data < cur->data) {
            p = p->next;
        }

        // 插入到 p 后面
        cur->next = p->next;
        p->next = cur;
    }
    return OK;
}

void SaveList(LinkList L,char name[])
{
    if(!L)
    {
        RED;
        printf("线性表不存在\n");
        return;
    }
    FILE *fp = fopen(name,"w");
    if(fp == NULL)
    {
        RED;
        printf("打开文件失败\n");
        return;
    }
    LinkList current = L->next;
    while (current != NULL)
    {
        fprintf(fp, "%d  ", current->data);
        current = current->next;
    }
    fclose(fp);
    WHITE;
    printf("成功保存到文件%s\n",name);
    return;
}

status ReadListFromFile(LinkList &L, char name[])
{
    if(L == NULL){
        RED;
        printf("线性表不存在，请先创建链表！\n");
        return INFEASIBLE;
    }
    ClearList(L);
    FILE *fp = fopen(name, "r");
    if(fp == NULL){
        RED;
        printf("打开文件【%s】失败！请检查文件名是否正确。\n", name);
        return ERROR;
    }
    ElemType data;
    LinkList tail = L;
    while(fscanf(fp, "%d", &data) == 1){
        LinkList newNode = (LinkList)malloc(sizeof(LNode));
        if(newNode == NULL){
            fclose(fp);
            RED;
            printf("内存分配失败！\n");
            return OVERFLOW;
        }
        newNode->data = data;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }
    fclose(fp);
    return OK;
}

// ===================== 5个新函数 =====================

// 1. 生成10个随机数字链表
status CreateRandomList10(LinkList &L){
    ClearList(L);
    LinkList tail = L;
    for(int i=0;i<10;i++){
        LinkList node = (LinkList)malloc(sizeof(LNode));
        node->data = rand()%100;
        node->next = NULL;
        tail->next = node;
        tail = node;
    }
    return OK;
}

// 2. 链表去重
status RemoveDuplicate(LinkList &L){
    if(L == NULL || L->next == NULL) return OK;
    LinkList p = L->next;
    while(p && p->next){
        if(p->data == p->next->data){
            LinkList q = p->next;
            p->next = q->next;
            free(q);
        }else p = p->next;
    }
    return OK;
}

// 3. 最大连续子串和（Kadane算法）
int MaxSubArray(LinkList L){
    if(L == NULL || L->next == NULL) return 0;
    int max = L->next->data;
    int cur = L->next->data;
    LinkList p = L->next->next;
    while(p){
        cur = cur+p->data > p->data ? cur+p->data : p->data;
        if(cur>max) max=cur;
        p = p->next;
    }
    return max;
}

// 4. 求所有链表交集
status IntersectionAllLists(LISTS &Lists){
    if(Lists.length < 2){
        RED;
        printf("至少需要两个链表！\n");
        return ERROR;
    }
    int arr[1005] = {0};
    LinkList p = Lists.elem[0].L->next;
    while(p){
        arr[p->data] = 1;
        p = p->next;
    }
    for(int i=1;i<Lists.length;i++){
        int tmp[1005] = {0};
        LinkList q = Lists.elem[i].L->next;
        while(q){
            if(arr[q->data]) tmp[q->data] = 1;
            q = q->next;
        }
        for(int j=0;j<1005;j++) arr[j] = tmp[j];
    }
    char newName[30] = "交集结果";
    InitList(Lists,newName);
    LinkList tail = Lists.elem[Lists.length-1].L;
    for(int i=0;i<1005;i++){
        if(arr[i]){
            LinkList node = (LinkList)malloc(sizeof(LNode));
            node->data = i;
            node->next = NULL;
            tail->next = node;
            tail = node;
        }
    }
    WHITE;
    printf("交集已生成到新表：交集结果\n");
    return OK;
}

// 5. 合并两个链表并排序
status MergeTwoListSort(LinkList L1, LinkList L2, LinkList &L3){
    ClearList(L3);
    LinkList a = L1->next, b = L2->next, t = L3;
    while(a && b){
        if(a->data <= b->data){
            t->next = a; a = a->next;
        }else{
            t->next = b; b = b->next;
        }
        t = t->next;
    }
    while(a) {t->next=a; a=a->next; t=t->next;}
    while(b) {t->next=b; b=b->next; t=t->next;}
    return OK;
}