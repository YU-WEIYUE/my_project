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
void showplus();//附加功能菜单
status DeleteDuplicate(LinkList &L);   //删除链表中重复的元素        
void VisualizeList(LinkList L);          //可视化链表        
void GetIntersection(LISTS &Lists);      //求多个链表的交集      
void MergeAndSortLists(LinkList &L1, LinkList &L2);      //合并两个有序链表

//主函数

int main(){
    int choice=1;//初始化用户选择
    int currentIndex = -1; //初始化链表指针，-1表示目前没有选中的链表
    Lists.length=0;//初始化链表集合

    while(choice){
        show();//展示菜单界面
        // 高亮显示当前选中的表名
        if(currentIndex != -1) {
            YELLOW;
            printf("\n");
            printf("╔═══════════════════════════════════════════════════════════╗\n");
            printf("                    当前选中链表：%s                          \n", Lists.elem[currentIndex].name);
            printf("╚═══════════════════════════════════════════════════════════╝\n");
            VisualizeList(Lists.elem[currentIndex].L);
        }

        GREEN;
        printf("\n请输入您的选择：");
        YELLOW;
        scanf("%d",&choice);//获取用户选择
        switch(choice){
            case 0:{
                //退出系统
                GREEN;
                printf("感谢使用链表系统！再见！\n");
                printf("输入任意键退出...");
                _getch();
                return 0;
            }

            case 1:{ //查看当前链表集合中有哪些链表
               
                showLists();
                break;
            }

            case 2:{//创建新链表  
                char ListName[30];
                GREEN;
                printf("请输入要创建的链表名称：");
                YELLOW;
                scanf("%s",ListName);
                if(InitList(Lists,ListName)==OK){
                    WHITE;
                    printf("链表【%s】创建成功！\n",ListName);
                    currentIndex=Lists.length-1;// 自动选中新表
                    
                }
                else {
                    RED;
                    printf("链表【%s】创建失败！\n",ListName);
                }
                break;
            }

            case 3:{//查找并选中链表
                
                char Listname[30];
                GREEN;
                printf("请输入要查找的链表名称：");
                YELLOW;
                scanf("%s",Listname);

                //查找下标
                currentIndex=LocateList(Lists,Listname);

                if(currentIndex==-1){
                    RED;
                    printf("链表【%s】查找失败！\n",Listname);
                    break;
                }
                else {
                    WHITE;
                    printf("链表【%s】查找成功！现在可以对其进行操作了！\n", Lists.elem[currentIndex].name);
                }

                break;
            }

            case 4:{//删除某一个特定链表
    char ListName[30];
    GREEN;
    printf("请输入要删除的链表名称：");
    YELLOW;
    scanf("%s",ListName);
    while(getchar() != '\n'); // 清空输入缓冲区

    // 先找到要删除的表的下标
    int delIndex = LocateList(Lists, ListName);

    if(delIndex == -1){
        RED;
        printf("未找到名称为【%s】的链表！\n", ListName);
        break;
    }

    // 先销毁链表（即使已经是NULL也没关系）
    DestroyList(Lists.elem[delIndex].L);
    
    // 从集合中删除记录
    for(int j=delIndex; j<Lists.length-1; j++){
        Lists.elem[j] = Lists.elem[j+1];
    }
    Lists.length--; // 减少链表数目

    WHITE;
    printf("链表【%s】删除成功！\n",ListName);

    if(delIndex==currentIndex)currentIndex=-1;// 如果删的是当前选中的表
    else if(delIndex<currentIndex)currentIndex--;// 如果删的是当前选中表前面的表，下标要减1
    break;
}

            case 5:{//删除当前链表
    if(currentIndex==-1){
        RED;
        printf("请先使用功能键 3 选中一个链表！\n");
        break;
    }
    if(DestroyList(Lists.elem[currentIndex].L)==OK){
        WHITE;printf("链表【%s】销毁成功！\n", Lists.elem[currentIndex].name);
        
        // 从LISTS集合中删除这个链表的记录
        for(int j=currentIndex; j<Lists.length-1; j++){
            Lists.elem[j] = Lists.elem[j+1];
        }
        Lists.length--; // 减少链表数目
        
        currentIndex=-1;//销毁后置为未选中
    }
    else{
        RED;
        printf("链表不存在，销毁失败！\n");
    }
    break;
}

            case 6:{//清空当前链表
                if(currentIndex==-1){
                    RED;
                    printf("请先使用功能键 3 选中一个链表！\n");
                    break;
                }
                if(ClearList(Lists.elem[currentIndex].L)==OK){
                    WHITE;
                    printf("链表【%s】清空成功！\n", Lists.elem[currentIndex].name);
                }

                else{
                    RED;
                    printf("链表不存在，无法清空！\n");
                }

                break; 

            }

            case 7:{// 判断当前链表是否为空
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个链表！\n");break;}
                if(ListEmpty(Lists.elem[currentIndex].L)){RED;printf("链表【%s】为空！\n", Lists.elem[currentIndex].name);}
                else {WHITE;printf("链表【%s】不为空！\n", Lists.elem[currentIndex].name);}
                break;
            }

            case 8:{//获取当前链表长度
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个链表！\n");break;}
                int res=ListLength(Lists.elem[currentIndex].L);
                if(res==INFEASIBLE){
                    RED;printf("链表不存在，无法求长度！\n");break;
                }
                else {
                    WHITE;
                    printf("链表【%s】长度为：%d\n", Lists.elem[currentIndex].name,res);
                    break;
                }
                
                
            }

            case 9:{// 获取指定位置的元素
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个链表！\n");break;}
                int i;
                GREEN;
                printf("请输入要获取的元素位置编号（从1开始）：");
                YELLOW;
                scanf("%d",&i);
                ElemType e;
                if(GetElem(Lists.elem[currentIndex].L,i,e)==OK){WHITE;printf("链表【%s】%d号位置的元素为：%d\n", Lists.elem[currentIndex].name, i, e);}
                else{RED;printf("位置无效，获取元素失败！\n");}
                break;
            }

            case 10:{//定位元素
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个链表！\n");break;}
                int e;
                GREEN;
                printf("请输入要定位的元素值：");
                YELLOW;
                scanf("%d",&e);
                int pos=LocateElem(Lists.elem[currentIndex].L,e);
                if(pos>0){WHITE;printf("链表【%s】中元素%d在第%d号位置！\n", Lists.elem[currentIndex].name, e, pos);}
                else if(pos==0){RED;printf("链表【%s】中没有找到元素%d！\n", Lists.elem[currentIndex].name, e);}
                else{RED;printf("链表不存在，无法定位元素！\n");}    
                break;
            }

            case 11:{//获取元素前驱
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个链表！\n");break;}
                int e;
                GREEN;
                printf("请输入要获取前驱的元素值：");
                YELLOW;
                scanf("%d",&e);
                ElemType pre;
                if(PriorElem(Lists.elem[currentIndex].L,e,pre)==OK){WHITE;printf("链表【%s】中元素%d的前驱是：%d\n", Lists.elem[currentIndex].name, e, pre);}
                else if(PriorElem(Lists.elem[currentIndex].L,e,pre)==ERROR){RED;printf("链表【%s】中元素%d没有前驱！\n", Lists.elem[currentIndex].name, e);}
                else{RED;printf("链表不存在，无法获取前驱！\n");}
                break;
            }

            case 12:{//获取后继
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个链表！\n");break;}
                int e;
                GREEN;
                printf("请输入要获取后继的元素值：");
                YELLOW;
                scanf("%d",&e);
                ElemType next;
                if(NextElem(Lists.elem[currentIndex].L,e,next)==OK){WHITE;printf("链表【%s】中元素%d的后继是：%d\n", Lists.elem[currentIndex].name, e, next);}
                else if(NextElem(Lists.elem[currentIndex].L,e,next)==ERROR){RED;printf("链表【%s】中元素%d没有后继！\n", Lists.elem[currentIndex].name, e);}
                else{RED;printf("链表不存在，无法获取后继！\n");}
                break;
            }

            case 13:{//插入元素
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个链表！\n");break;}
                int i,e;
                GREEN;
                printf("请输入要插入的元素值：");
                YELLOW;
                scanf("%d",&e);
                // 移除元素值范围限制，支持负数输入
                GREEN;
                printf("请输入要插入的位置：");
                YELLOW;
                scanf("%d",&i);
                if(ListInsert(Lists.elem[currentIndex].L,i,e)==OK){WHITE;printf("链表【%s】中元素%d插入成功！\n", Lists.elem[currentIndex].name, e);}
                else{RED;printf("元素%d插入失败！\n",e);}
                break;
            }
            
            case 14:{//删除元素
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个链表！\n");break;}
                int i,e;
                GREEN;
                printf("请输入要删除的元素位置编号（从1开始）：");
                YELLOW;
                scanf("%d",&i);
                if(ListDelete(Lists.elem[currentIndex].L,i,e)==OK){WHITE;printf("链表【%s】中元素%d删除成功！\n", Lists.elem[currentIndex].name, e);}
                else{RED;printf("位置%d删除失败！\n",i);}
                break;
            }

            case 15: {//遍历输出
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个链表！\n");break;}
                if(ListTraverse(Lists.elem[currentIndex].L)==OK){WHITE;printf("\n链表【%s】遍历成功！\n", Lists.elem[currentIndex].name);}
                else{RED;printf("链表不存在，无法遍历输出！\n");}
               break; 
            }

            case 16:{//链表翻转
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个链表！\n");break;}
                if(ListReverse(Lists.elem[currentIndex].L)==OK){
                    WHITE;
                    printf("链表【%s】翻转完成！\n", Lists.elem[currentIndex].name);
                    break;
                }
                else {
                    RED;
                    printf("链表不存在!");
                }

            }

            case 17:{//删除链表的倒数第n个结点
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个链表！\n");break;}
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
                    printf("请检查此链表是否为空，或删除位置是否合法！");
                    break;
                }
                break;
            }

            case 18:{//链表排序
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个链表！\n");break;}
                if(SortList(Lists.elem[currentIndex].L)==OK){
                    WHITE;
                    printf("排序成功！");
                    break;
                }
                else {
                    RED;
                    printf("该链表为空，无法操作！");
                    break;
                }
            }

            case 19:{// 将链表保存到文件中
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个链表！\n");break;}
                GREEN;
                printf("请输入要保存的文件名：");
                char listname[30];
                YELLOW;
                scanf("%s",listname);
                SaveList(Lists.elem[currentIndex].L,listname);
                break;
            }

            case 20:{//读取文件以创建链表
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个链表！\n");break;}
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

            case 21:{//附加功能
                int op=1;
                while(op){
                    system("cls");
                    showplus();
                    // 提示当前选中的表（如果有）
                    if(currentIndex != -1) {
                        YELLOW;
                        printf("\n 当前主菜单选中表：%s\n", Lists.elem[currentIndex].name);
                    }
                    GREEN;
                    printf("\n请输入您的选择：");
                    YELLOW;
                    scanf("%d", &op);
                    
                    switch(op){
                        case 0://返回主菜单
                            op=0;
                            break;

                        case 1://快速填充10个随机数到链表
                            {if(currentIndex == -1){RED;printf("请先在主菜单选中一个链表！\n");break;}
                            srand((unsigned)time(NULL)); // 用当前时间作为随机数种子
                            for(int i=0;i<10;i++){
                                int randNum = rand() % 200-100; // 生成-100到99的随机数
                                ListInsert(Lists.elem[currentIndex].L, i+1, randNum); // 插入到链表末尾
                            }
                            WHITE;printf("已快速填充10个随机数到链表【%s】！\n", Lists.elem[currentIndex].name);
                            break;}

                        case 2://求当前所有链表交集
                            if(Lists.length<2){RED;printf("当前链表集合中没有足够的链表进行交集运算！\n");break;}
                            GetIntersection(Lists);
                            break;
                            
                        case 3://链表去重
                            if(currentIndex == -1){RED;printf("请先在主菜单选中一个链表！\n");break;}
                            if(DeleteDuplicate(Lists.elem[currentIndex].L)==OK){
                                WHITE;printf("链表【%s】去重完成！\n", Lists.elem[currentIndex].name);
                            }else{
                                RED;printf("链表去重失败！\n");
                            }
                            break;

                        case 4://链表可视化
                            if(currentIndex == -1){RED;printf("请先在主菜单选中一个链表！\n");break;}
                            VisualizeList(Lists.elem[currentIndex].L);
                            break;

                        case 5://合并两链表并升序排序
                            {if(Lists.length < 2){RED;printf("当前链表集合中没有足够的链表进行合并运算！\n");break;}
                            int index1, index2;
                            GREEN;
                            printf("请输入要合并的第一个链表的编号（从1开始）：");
                            YELLOW;
                            scanf("%d", &index1);
                            index1--; // 转换为索引
                            if (index1 < 0 || index1 >= Lists.length) {
                                RED;
                                printf("第一个链表编号无效！\n");
                                break;
                            }
                            GREEN;
                            printf("请输入要合并的第二个链表的编号（从1开始）：");
                            YELLOW;
                            scanf("%d", &index2);
                            index2--; // 转换为索引
                            if (index2 < 0 || index2 >= Lists.length) {
                                RED;
                                printf("第二个链表编号无效！\n");
                                break;
                            }
                            MergeAndSortLists(Lists.elem[index1].L, Lists.elem[index2].L);
                            break;}

                        default:
                            RED; printf("无效的选择！\n");
                    }
                    if(op){ // 如果不是选择返回主菜单，就提示按键继续
                        BLUE;
                        printf("按任意键以继续操作......");
                        _getch(); //暂停程序，等待用户按键
                    }
                }

            }




        }

        BLUE;
        printf("按任意键以继续操作......");
        _getch(); //暂停程序，等待用户按键
        system("cls"); //清屏

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

    // 分区1：多链表集合管理
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━  多链表集合管理 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("1. 查看当前链表集合列表\n");
    printf("2. 创建新链表\n");
    printf("3. 查找并选中链表\n");
    printf("4. 删除某一个链表\n");

    // 分区2：单链表基础操作
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 单链表基础操作 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("5. 销毁当前链表\n");
    printf("6. 清空当前链表\n");
    printf("7. 判断当前链表是否为空\n");
    printf("8. 获取当前链表长度\n");

    // 分区3：单链表元素操作
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

    // 分区4：单链表高级功能
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 单链表高级功能 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("16. 链表翻转\n");
    printf("17. 删除链表的倒数第n个结点\n");
    printf("18.链表排序 \n");

    // 分区5：系统操作
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━      系统操作     ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("19. 将链表保存到文件中\n");
    printf("20.读取文件以创建链表\n");
    printf("21.附加功能\n");
    printf("0. 退出系统\n");
}



// 附加功能菜单
void showplus(){
    BLUE;   
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("                                        欢迎使用附加功能菜单                                              \n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("                                                                              Powered by: CS2503班——U202514774\n\n");
    GREEN;
    printf("1.快速填充10个随机数到链表\n");
    printf("2.求当前所有链表交集\n");
    printf("3.链表去重\n");
    printf("4.可视化链表\n");
    printf("5.合并两链表并升序排序\n");
    printf("0.返回主菜单\n");
}


void showLists(){//1.显示链表集合
    BLUE;
    printf("当前链表集合列表：\n");
    if(Lists.length==0){RED;printf("链表集合中没有任何链表！\n");return;}
    for(int i=0;i<Lists.length;i++){
        GREEN;
        printf("%d. %s\n",i+1,Lists.elem[i].name);
    }
}

status InitList(LISTS &Lists,char ListName[])  //2.在Lists中增加一个名称为ListName的空链表
{
    for(int i=0;i<Lists.length;i++){
        if(strcmp(Lists.elem[i].name,ListName)==0){  //如果集合中已经存在同名的链表
            RED;
            printf("集合中已经存在名称为【%s】的链表了，无法创建同名的链表\n", ListName);
            return ERROR;  //返回错误
        }
    }
    // 如果集合中不存在同名的链表，则创建新的链表
    if(Lists.length < 30){  // 假设最多可以有30个链表
        strcpy(Lists.elem[Lists.length].name, ListName);
        Lists.elem[Lists.length].L = (LinkList)malloc(sizeof(LNode));  // 初始化链表指针
        if(Lists.elem[Lists.length].L == NULL) exit(OVERFLOW);
        Lists.elem[Lists.length].L->next = NULL;  // 头结点next置空
        Lists.length++;  // 增加链表数目
        return OK;  // 返回成功
    }
    RED;
    printf("链表集合已满，无法添加新表！\n");
    return OVERFLOW;  // 返回错误
}

status LocateList(LISTS Lists,char ListName[]) //3.在Lists中查找一个名称为ListName的链表的位置
{
    for(int k=0;k<Lists.length;k++){
        if(strcmp(Lists.elem[k].name,ListName)==0){  // 如果集合中存在名称为ListName的链表
            return k;  // 返回序号
        }
    }
    return -1;  // 未找到，返回-1
}

status DeleteList(LISTS &Lists,char ListName[]) //4.在Lists中删除一个名称为ListName的链表
{
    for(int i=0;i<Lists.length;i++){
        if(strcmp(Lists.elem[i].name,ListName)==0){  // 如果集合中存在名称为ListName的链表
            DestroyList(Lists.elem[i].L);// 将该链表从集合中删除
            for(int j=i;j<Lists.length-1;j++){
                Lists.elem[j] = Lists.elem[j+1];
            }
            Lists.length--;  // 减少链表数目
            return OK;  // 返回成功
        }
    }
    RED;
    printf("未找到名称为【%s】的链表！\n", ListName);
    return ERROR;  // 返回错误
}

status DestroyList(LinkList& L) //5.销毁链表L
{
    if(L == NULL) return INFEASIBLE; // 如果链表不存在，返回错误
    LinkList p = L; // 从头结点开始
    while(p != NULL){
        LinkList temp = p;
        p = p->next; // 移动到下一个结点
        free(temp); // 释放当前结点的内存
    }
    L = NULL; // 将链表指针置空，表示链表已销毁
    return OK; // 返回成功
}

status ClearList(LinkList& L)//6.清空链表L
{
    if(L == NULL) return INFEASIBLE; // 如果链表不存在，返回错误
    LinkList p = L->next; // 从第一个结点开始
    while(p != NULL){
        LinkList temp = p;
        p = p->next; // 移动到下一个结点
        free(temp); // 释放当前结点的内存
    }
    L->next = NULL; // 将头结点的next指针置空，表示链表已清空
    return OK; // 返回成功
}

status ListEmpty(LinkList &L)//7.判断链表L是否为空
{
    if(L == NULL) return INFEASIBLE; // 如果链表不存在，返回错误
    if(L->next == NULL) return TRUE; // 如果链表没有结点，返回TRUE
    return FALSE; // 否则返回FALSE
}

status ListLength(LinkList L)//8.求链表的长度
{
    if(L==NULL)return INFEASIBLE; // 如果链表不存在，返回错误
    int length = 0;
    LinkList p = L->next; // 从第一个结点开始
    while(p != NULL){
        length++;
        p = p->next; // 移动到下一个结点
    }
    return length; // 返回链表长度
}

status GetElem(LinkList L,int i,ElemType &e)//9.获取链表L中第i个元素的值
{
    if(L==NULL)return INFEASIBLE; // 如果链表不存在，返回错误
    if(i<1 || i>ListLength(L))return ERROR; // 如果位置不合法，返回错误
    LinkList p = L->next; // 从第一个结点开始
    for(int j=1;j<i;j++){
        p = p->next; // 移动到第i个结点
    }
    e = p->data; // 获取第i个结点的元素值
    return OK; // 返回成功
}

status LocateElem(LinkList &L,ElemType e)//10.定位元素e在链表L中的位置
{
    if(L==NULL)return INFEASIBLE; // 如果链表不存在，返回错误
    LinkList p = L->next; // 从第一个结点开始
    int position = 1; // 位序从1开始
    while(p != NULL){
        if(p->data == e) return position; // 如果找到元素e，返回位序
        p = p->next; // 移动到下一个结点
        position++;
    }
    return ERROR; // 没有找到元素e，报错
}

status PriorElem(LinkList L,ElemType e,ElemType &pre)//11.获取元素e的前驱
{
    if(L==NULL)return INFEASIBLE; // 如果链表不存在，返回错误
    LinkList p = L->next; // 从第一个结点开始
    LinkList preNode = L; // 前驱结点初始为头结点
    while(p != NULL){
        if(p->data == e){
            if(preNode == L) return ERROR; // 如果e是第一个结点，没有前驱，返回错误
            pre = preNode->data; // 获取前驱元素值
            return OK; // 返回成功
        }
        preNode = p; // 更新前驱结点
        p = p->next; // 移动到下一个结点
    }
    return ERROR; // 没有找到元素e，报错
}

status NextElem(LinkList L,ElemType e,ElemType &next)//12.获取元素e的后继
{
    if(L==NULL)return INFEASIBLE; // 如果链表不存在，返回错误
    LinkList p = L->next; // 从第一个结点开始
    while(p != NULL){
        if(p->data == e){
            if(p->next == NULL) return ERROR; // 如果e是最后一个结点，没有后继，返回错误
            next = p->next->data; // 获取后继元素值
            return OK; // 返回成功
        }
        p = p->next; // 移动到下一个结点
    }
    return ERROR; // 没有找到元素e，报错
}

status ListInsert(LinkList &L,int i,ElemType e)//13.在链表L的第i个位置插入元素e
{
    if(L==NULL)return INFEASIBLE;//链表不存在，报错
    if(i<1||i>ListLength(L)+1)return ERROR;//位置不合法，报错
    LinkList p=L; // 从头结点开始
    for(int j=0;j<i-1;j++){
        p=p->next;//移动到第i-1个节点
    }
    LinkList newnode=(LinkList)malloc(sizeof(LNode));//新建链表节点
    if(newnode==NULL)exit(OVERFLOW);//内存分配失败，报错
    newnode->data=e;//设置新节点的数据域为e
    newnode->next=p->next;//将新节点的指针域指向第i个节点
    p->next=newnode;//将第i-1个节点的指针域指向新节点
    return OK;//返回成功
}

status ListDelete(LinkList &L,int i,ElemType &e)//14.删除链表L的第i个元素，并用e返回其值
{
    if(L==NULL)return INFEASIBLE;//链表不存在，报错
    if(i<1||i>ListLength(L))return ERROR;//位置不合法，报错
    LinkList p=L; // 从头结点开始
    for(int j=0;j<i-1;j++){
        p=p->next;//移动到第i-1个节点
    }
    LinkList q=p->next;//q指向第i个节点，即要删除的节点
    e=q->data;//将要删除的节点的数据域值保存在e中
    p->next=q->next;//将第i-1个节点的指针域指向第i+1个节点，跳过第i个节点
    free(q);//释放第i个节点的内存空间
    return OK;//返回成功
}

status ListTraverse(LinkList L)//15.遍历输出链表L中的元素
{
    if(L==NULL)return INFEASIBLE;//链表不存在，报错
    LinkList p=L->next; // 从第一个结点开始
    while(p != NULL){
        visit(p->data); // 输出当前结点的数据域值
        p = p->next; // 移动到下一个结点
    }
    return OK; // 返回成功
}

status ListReverse(LinkList &L)//16.链表翻转
{
    if(L==NULL)return INFEASIBLE;//链表不存在，报错
    LinkList prev = NULL; // 前驱结点初始为NULL
    LinkList current = L->next; // 当前结点从第一个结点开始
    while(current != NULL){
        LinkList next = current->next; // 保存当前结点的下一个结点
        current->next = prev; // 将当前结点的指针域指向前驱结点，实现翻转
        prev = current; // 更新前驱结点为当前结点
        current = next; // 移动到下一个结点
    }
    L->next = prev; // 将头结点的指针域指向新的第一个结点，即翻转后的链表头部
    return OK; // 返回成功
}

status RemoveNthFromEnd(LinkList &L,int n)//17.删除链表的倒数第n个节点
{
    if(L==NULL)return INFEASIBLE;
    int len=ListLength(L);
    if(n<1||n>len)return ERROR;
    
    LinkList fast=L,low=L;
    // 快指针先移动n+1步
    for(int i=0;i<=n;i++){
        fast=fast->next;
    }
    // 快慢指针一起移动，直到快指针到达最后一个结点
    while(fast!=NULL){
        fast=fast->next;
        low=low->next;
    }
    
    LinkList tmp=low->next;
    low->next=tmp->next;
    free(tmp);
    return OK;
}

status SortList(LinkList &L)//18.排序链表
{
    if(L==NULL)return INFEASIBLE;
    if(L->next==NULL||L->next->next==NULL)return OK; // 空表或只有一个结点
    
    LinkList dummy = L; // 虚拟头结点
    LinkList lastSorted = L->next; // 已排序部分的最后一个节点
    LinkList curr = lastSorted->next; // 当前要排序的节点
    
    while(curr != NULL){
        if(curr->data >= lastSorted->data){
            // 当前节点比已排序部分最后一个大，直接接在后面
            lastSorted = curr;
        } else {
            // 找到要插入的位置的前驱节点
            LinkList prev = dummy;
            while(prev->next->data < curr->data){
                prev = prev->next;
            }
            // 移除curr节点
            lastSorted->next = curr->next;
            // 插入到prev后面
            curr->next = prev->next;
            prev->next = curr;
        }
        curr = lastSorted->next;
    }
    return OK;
}

void SaveList(LinkList L,char name[])//19.保存链表到文件中
{
    if(!L) // 如果L不存在或未初始化，无法进行操作
    {
        RED;
        printf("链表不存在\n");
        return;
    }
    FILE *fp = fopen(name,"w"); // 打开文件，以写的方式
    if(fp == NULL) // 如果无法找到文件，报错
    {
        RED;
        printf("打开文件失败\n");
        return;
    }
    LinkList current = L->next; // 指向第一个节点
    while (current != NULL) // 循环遍历链表中的每个节点
    {
        fprintf(fp, "%d  ", current->data); // 将节点的数据写入文件中
        current = current->next;
    }
    fclose(fp); // 关闭文件
    WHITE;
    printf("成功保存到文件%s\n",name); // 提示信息，表明操作成功
    return;
}

status ReadListFromFile(LinkList &L, char name[])//20.从文件中读取数据以创建链表
{
    // 1. 检查链表是否存在
    if(L == NULL){
        RED;
        printf("链表不存在，请先创建链表！\n");
        return INFEASIBLE;
    }

    // 2. 清空链表原有数据（避免内存泄漏）
    ClearList(L);

    // 3. 打开文件
    FILE *fp = fopen(name, "r");
    if(fp == NULL){
        RED;
        printf("打开文件【%s】失败！请检查文件名是否正确。\n", name);
        return ERROR;
    }

    // 4. 读取文件数据并插入链表
    ElemType data;
    LinkList tail = L;  // 尾指针，用于尾插法（保持文件中数据的顺序）

    // 循环读取文件中的整数，直到文件结束
    while(fscanf(fp, "%d", &data) == 1){
        // 分配新节点
        LinkList newNode = (LinkList)malloc(sizeof(LNode));
        if(newNode == NULL){
            fclose(fp);
            RED;
            printf("内存分配失败！\n");
            return OVERFLOW;
        }

        // 尾插法插入节点
        newNode->data = data;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }

    // 5. 关闭文件并返回成功
    fclose(fp);
    return OK;
}

status DeleteDuplicate(LinkList &L) {//21.链表去重
    if(L == NULL) return INFEASIBLE; // 如果链表不存在，返回错误
    LinkList p = L->next; // 从第一个结点开始
    while(p != NULL){
        LinkList q = p; // q指向p，用于查找后续结点中与p重复的元素
        while(q->next != NULL){
            if(q->next->data == p->data){
                // 找到重复元素，删除q->next结点
                LinkList temp = q->next;
                q->next = temp->next; // 跳过重复结点
                free(temp); // 释放重复结点的内存
            } else {
                q = q->next; // 移动q指针继续查找
            }
        }
        p = p->next; // 移动p指针到下一个结点
    }
    return OK; // 返回成功
}

void VisualizeList(LinkList L) {//22.链表可视化
    if (!L) {
        RED;
        printf("链表不存在！\n");
        return;
    }
    LinkList p = L->next;
    printf("链表可视化：\n");
    while (p) {
        printf("[ %d ] -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

void MergeAndSortLists(LinkList &L1, LinkList &L2) {// 23. 合并两链表并升序排序
    char newName[30];
    GREEN;
    printf("输入新链表的名称：");
    scanf("%s", newName);
    while(getchar() != '\n'); // 清空输入缓冲区

    // 先对两个输入链表进行排序
    SortList(L1);
    SortList(L2);

    // 创建新链表保存结果
    if (InitList(Lists, newName) != OK) {
        RED;
        printf("创建新链表失败！\n");
        return;
    }
    int newIndex = Lists.length - 1;
    LinkList newL = Lists.elem[newIndex].L;
    LinkList tail = newL;

    LinkList p1 = L1->next;
    LinkList p2 = L2->next;

    // 合并两个有序链表
    while (p1 && p2) {
        if (p1->data < p2->data) {
            LinkList node = (LinkList)malloc(sizeof(LNode));
            node->data = p1->data;
            node->next = NULL;
            tail->next = node;
            tail = node;
            p1 = p1->next;
        } else {
            LinkList node = (LinkList)malloc(sizeof(LNode));
            node->data = p2->data;
            node->next = NULL;
            tail->next = node;
            tail = node;
            p2 = p2->next;
        }
    }

    // 处理剩余元素
    while (p1) {
        LinkList node = (LinkList)malloc(sizeof(LNode));
        node->data = p1->data;
        node->next = NULL;
        tail->next = node;
        tail = node;
        p1 = p1->next;
    }
    while (p2) {
        LinkList node = (LinkList)malloc(sizeof(LNode));
        node->data = p2->data;
        node->next = NULL;
        tail->next = node;
        tail = node;
        p2 = p2->next;
    }

    WHITE;
    printf("合并完成！新链表【%s】已创建。\n", newName);
    printf("合并结果：");
    ListTraverse(newL);
    printf("\n");
}

// 24.求多个链表的交集函数
void GetIntersection(LISTS &Lists) {  // 改为引用传递！这是最关键的修复
    if (Lists.length < 2) {
        RED;
        printf("至少需要两个链表才能求交集！\n");
        return;
    }

    char newName[30];
    GREEN;
    printf("输入交集链表的名称：");
    scanf("%s", newName);
    while(getchar() != '\n'); // 清空输入缓冲区

    // 创建新链表保存结果
    if (InitList(Lists, newName) != OK) {
        RED;
        printf("创建新链表失败！\n");
        return;
    }
    int newIndex = Lists.length - 1;
    LinkList result = Lists.elem[newIndex].L;
    LinkList tail = result;

    // 优化：先对第一个链表去重，避免重复检查
    LinkList tempFirst = Lists.elem[0].L;
    DeleteDuplicate(tempFirst);  // 先去重，减少后续检查次数

    // 以去重后的第一个链表为基准，遍历它的每个元素
    LinkList p = tempFirst->next;
    while (p) {
        int existsInAll = TRUE;
        // 检查这个元素是否在所有其他链表中都存在
        for (int i = 1; i < Lists.length - 1; i++) {  // 注意：Lists.length已经增加了1（因为创建了新链表）
            if (LocateElem(Lists.elem[i].L, p->data) == ERROR) {
                existsInAll = FALSE;
                break;
            }
        }

        // 如果所有链表都有这个元素，就添加到结果中
        if (existsInAll) {
            LinkList newNode = (LinkList)malloc(sizeof(LNode));
            newNode->data = p->data;
            newNode->next = NULL;
            tail->next = newNode;
            tail = newNode;
        }

        p = p->next;
    }

    WHITE;
    printf("交集计算完成！新链表【%s】已创建并添加到集合中。\n", newName);
    printf("交集结果：");
    ListTraverse(result);
    printf("\n");
}