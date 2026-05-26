/*----------头文件的引入---------*/
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include "string.h"
#include<windows.h>
#include<conio.h>
#include <time.h> 


/*----------预定义-----------*/

// 定义布尔类型TRUE和FALSE
#define TRUE 1
#define FALSE 0

// 定义函数返回值类型
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;

// 顺序表中数据元素的类型
typedef int ElemType;

// 定义顺序表的初始长度和每次扩展的长度
#define LIST_INIT_SIZE 100  
#define LISTINCREMENT 10

// 定义顺序表类型
typedef struct{
    ElemType * elem; // 存储数据元素的数组指针
    int length; // 当前长度
    int listsize; // 当前可容纳的最大长度
}SqList;

// 定义线性表集合中的每个线性表的类型
typedef struct{
    char name[30]; // 线性表的名称
    SqList L; // 线性表本身
}LIST_ELEM;

typedef struct{  //线性表的管理表定义
     struct { char name[30];
              SqList L;	
      } 
      elem[10];
      int length;//当前集合长度
      int listsize;//当前集合可容纳的最大长度
 }LISTS;
LISTS Lists; // 声明线性表集合的变量名为Lists


//定义字体颜色切换
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
#define GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);


/*---------函数声明---------*/

//单个线性表操作
status InitList(SqList& L); //新建
status DestroyList(SqList& L); //销毁
status ClearList(SqList& L); //清空
status ListEmpty(SqList L);  //判空
status ListLength(SqList L);  //求长度
status GetElem(SqList L,int i,ElemType &e);  //获取元素
status LocateElem(SqList L,ElemType e);  //判断位置
status PriorElem(SqList L,ElemType e,ElemType &pre);  //获得前驱
status NextElem(SqList L,ElemType e,ElemType &next);  //获得后继
status ListInsert(SqList &L,int i,ElemType e);  //插入元素
status ListDelete(SqList &L,int i,ElemType &e);  //删除元素
status ListTraverse(SqList L); //遍历输出
void visit(int elem);  //遍历输出时候调用的visit函数
void MaxSubArray(SqList L);  //最大连续子数组
void SubArrayNum(SqList L , int k); //和为k的子数组个数
void sortList(SqList &L);  //顺序表排序
status AddList(LISTS &Lists,char ListName[]);//添加线性表到集合
status RemoveList(LISTS &Lists,char ListName[]);//从集合中删除线性表
int LocateList(LISTS &Lists,char ListName[]);//在集合中查找线性表，返回下标
void show();//菜单界面
void showplus();//附加功能菜单界面
void showLists(LISTS Lists);//显示集合中有哪些线性表
status SaveList(SqList L,char FileName[]);//将线性表保存到文件中
status RemoveDuplicates(SqList &L); //线性表去重
status ReverseList(SqList &L); //线性表反转
status MergeLists(SqList &L1, SqList L2); //合并两个线性表
status IntersectLists(LISTS Lists, SqList &Intersect); //求当前所有线性表交集
status ReadListFromFile(SqList &L, char FileName[]); //从文件中读取数据创建线性表

/*---------主函数---------*/
int main(){
    
    srand((unsigned)time(NULL));//设置随机数种子为当前时间，保证每次运行程序时生成的随机数序列不同
    int choice=1;//记录用户选择
    
    // 用下标记录当前选中的表，-1表示未选中
    int currentIndex = -1; 
    
    Lists.length=0;//初始化线性表集合长度为0，表示集合中没有默认线性表
    Lists.listsize = 10; // 初始化集合最大容量
    
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

            // ========== 多线性表集合管理 ==========
            case 1:{//查看当前线性表集合中有哪些线性表
                showLists(Lists);
                break;}

            case 2:{//创建新一个线性表
                char ListName[30];
                GREEN;
                printf("请输入要创建的线性表名称：");
                YELLOW;
                scanf("%s",ListName);
                if(AddList(Lists,ListName)==OK){
                    WHITE;printf("线性表【%s】创建成功！\n",ListName);
                    currentIndex = Lists.length - 1; // 自动选中新表
                }
                else{RED;printf("线性表【%s】创建失败！\n",ListName);}
                break;
            }

            case 3:{//查找一个线性表和进行操作
                char ListName[30];
                GREEN;
                printf("请输入要查找的线性表名称：");
                YELLOW;
                scanf("%s",ListName);
                
                // 查找下标
                currentIndex = LocateList(Lists, ListName);
                
                if(currentIndex != -1){
                    WHITE;printf("线性表【%s】查找成功！现在可以对其进行操作了！\n", Lists.elem[currentIndex].name);
                }
                else{RED;printf("线性表【%s】查找失败！\n",ListName);}
                break;
            }

            case 4:{//删除一个线性表
                char ListName[30];
                GREEN;
                printf("请输入要删除的线性表名称：");
                YELLOW;
                scanf("%s",ListName);
                
                // 先找到要删除的表的下标
                int delIndex = LocateList(Lists, ListName);
                
                if(delIndex != -1) {
                    // 如果删的是当前选中的表
                    if(delIndex == currentIndex) {
                        currentIndex = -1;
                    } 
                    // 如果删的是当前选中表前面的表，下标要减1
                    else if(delIndex < currentIndex) {
                        currentIndex--;
                    }
                }
                
                if(RemoveList(Lists,ListName)==OK){WHITE;printf("线性表【%s】删除成功！\n",ListName);}
                else{RED;printf("线性表【%s】删除失败！\n",ListName);}
                break;
            }

            // ========== 单线性表基础操作 ==========
            case 5://销毁线性表
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                if(DestroyList(Lists.elem[currentIndex].L)==OK){
                    WHITE;printf("线性表【%s】销毁成功！\n", Lists.elem[currentIndex].name);
                    currentIndex = -1; // 销毁后置为未选中
                }
                else{RED;printf("线性表不存在，销毁失败！\n");}
                break;
            
            case 6:{//清空线性表
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                if(ClearList(Lists.elem[currentIndex].L)==OK){WHITE;printf("线性表【%s】清空成功！\n", Lists.elem[currentIndex].name);}
                else{RED;printf("线性表不存在，无法清空！\n");}
                break;
            }

            case 7:{//判空线性表
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                if(ListEmpty(Lists.elem[currentIndex].L)){RED;printf("线性表【%s】为空！\n", Lists.elem[currentIndex].name);}
                else {WHITE;printf("线性表【%s】不为空！\n", Lists.elem[currentIndex].name);}
                break;
            }

            case 8:{//求线性表长度
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                int length=ListLength(Lists.elem[currentIndex].L);
                if(length!=INFEASIBLE){WHITE;printf("线性表【%s】长度为：%d\n", Lists.elem[currentIndex].name, length);}
                else{RED;printf("线性表不存在，无法求长度！\n");}
                break;
            }

            // ========== 单线性表元素操作 ==========
            case 9:{//获取元素
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

            case 11:{//获取前驱
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
                if(NextElem(Lists.elem[currentIndex].L,e,next)==OK){
                    WHITE;
                    printf("线性表【%s】中元素%d的后继是：%d\n", Lists.elem[currentIndex].name, e, next);}
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
                // 移除元素值范围限制，支持负数输入
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

            // ========== 单线性表高级功能 ==========
            case 16:{//顺序表排序
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                sortList(Lists.elem[currentIndex].L);
                WHITE;printf("线性表【%s】排序完成！\n", Lists.elem[currentIndex].name);
                break;
            }
                
            case 17:{//最大连续子数组和
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                MaxSubArray(Lists.elem[currentIndex].L);
                break;
            }

            case 18:{//和为k的子数组个数
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                int k;
                GREEN;
                printf("请输入要计算和为k的子数组个数的k值：");
                YELLOW;
                scanf("%d",&k);
                SubArrayNum(Lists.elem[currentIndex].L,k);
                break;
            }

            // ========== 系统操作 ==========
            case 19:{//将线性表保存到文件中
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个线性表！\n");break;}
                char FileName[20];
                GREEN;
                printf("请输入要保存的文件名：");
                YELLOW;
                scanf("%s",FileName);
                if(SaveList(Lists.elem[currentIndex].L,FileName)==OK){
                    WHITE;printf("线性表【%s】已保存到文件【%s】！\n", Lists.elem[currentIndex].name, FileName);
                }else{
                    RED;printf("文件保存失败！\n");
                }
                break;
            }
            case 20:{//附加功能
                int plusLoop = 1;
                while(plusLoop) {
                system("cls");
                showplus();
                // 提示当前选中的表（如果有）
                if(currentIndex != -1) {
                    YELLOW;
                    printf("\n 当前主菜单选中表：%s\n", Lists.elem[currentIndex].name);
                }

                GREEN;
                printf("\n请输入您的选择：");
                int pluschoice;
                YELLOW;
                scanf("%d", &pluschoice);

                switch(pluschoice) {
                    case 0: // 返回主菜单
                    plusLoop = 0;
                    break;

                    case 1: // 1. 线性表去重
                    if(currentIndex == -1){RED;printf(" 请先在主菜单选中一个线性表！\n");break;}
                    if(RemoveDuplicates(Lists.elem[currentIndex].L)==OK){
                        WHITE;printf(" 线性表【%s】去重完成！\n", Lists.elem[currentIndex].name);
                    }else{
                        RED;printf(" 线性表去重失败！\n");
                    }
                    break;

                    case 2: // 2. 合并两个线性表
                        {if(Lists.length < 2){RED;printf(" 至少需要2个线性表才能合并！\n");break;}
                    
                        char name1[30], name2[30];
                        WHITE; printf(" 当前集合中的表：\n"); showLists(Lists);
                    
                        GREEN; printf("\n请输入第一个表名（目标表，结果会存到这里）：");
                        YELLOW; scanf("%s", name1);
                        int idx1 = LocateList(Lists, name1);
                    
                        GREEN; printf("请输入第二个表名（源表，数据会追加过去）：");
                        YELLOW; scanf("%s", name2);
                        int idx2 = LocateList(Lists, name2);

                        if(idx1 == -1 || idx2 == -1) {
                            RED; printf(" 表名输入错误！\n");
                        } else {
                            if(MergeLists(Lists.elem[idx1].L, Lists.elem[idx2].L)==OK){
                                WHITE;printf(" 线性表【%s】合并【%s】完成！\n", name1, name2);
                                currentIndex = idx1;
                            }else{
                                RED;printf(" 线性表合并失败！\n");
                            }
                        }
                        break;}

                    case 3: // 3. 求当前所有线性表交集
                        {if(Lists.length < 2){RED;printf(" 至少需要2个线性表才能求交集！\n");break;}
                        SqList resIntersect;
                        resIntersect.elem = NULL; // 初始化
                        resIntersect.length = 0;
                        resIntersect.listsize = 0;
                        if(IntersectLists(Lists, resIntersect)==OK){
                            WHITE;printf(" 所有线性表交集计算完成！\n");
                            ListTraverse(resIntersect);
                            // 【可选】询问是否保存交集为新表
                            char saveNew;
                            GREEN; printf("\n是否将交集保存为新线性表？(y/n): ");
                            YELLOW; scanf(" %c", &saveNew);
                            if(saveNew == 'y' || saveNew == 'Y') {
                                char newName[30];
                                GREEN; printf("请输入新表名称：");
                                YELLOW; scanf("%s", newName);
                                if(AddList(Lists, newName) == OK) {
                                    // 深拷贝
                                    SqList &newL = Lists.elem[Lists.length-1].L;
                                    free(newL.elem);
                                    newL.elem = (ElemType*)malloc(resIntersect.listsize * sizeof(ElemType));
                                    newL.length = resIntersect.length;
                                    newL.listsize = resIntersect.listsize;
                                    memcpy(newL.elem, resIntersect.elem, resIntersect.length * sizeof(ElemType));
                                    WHITE; printf(" 交集已保存为新表【%s】！\n", newName);
                                    currentIndex = Lists.length - 1;
                                }       
                            } 
                        }else{
                            RED;printf(" 交集计算失败！\n");
                        }
                        // 释放临时交集内存
                        if(resIntersect.elem != NULL) {
                            free(resIntersect.elem);
                            resIntersect.elem = NULL;
                        }
                        break;}
                    
                    case 4: // 4. 线性表反转
                        if(currentIndex == -1){RED;printf(" 请先在主菜单选中一个线性表！\n");break;}
                        if(ReverseList(Lists.elem[currentIndex].L)==OK){
                            WHITE;printf(" 线性表【%s】反转完成！\n", Lists.elem[currentIndex].name);
                        }else{
                            RED;printf(" 线性表反转失败！\n");
                        }
                        break;

                    default:
                        RED; printf("无效的选择！\n");
                }

                if(plusLoop) {
                    BLUE; printf("\n按任意键继续附加功能...");
                    _getch();
                }
            }
            
            break;
        }
            case 21:{
                char FileName[20];
                GREEN;
                printf("请输入要读取的文件名：");
                YELLOW;
                scanf("%s",FileName);
                SqList newList;
                // 初始化局部newList，防止垃圾值导致崩溃
                newList.elem = NULL;
                newList.length = 0;
                newList.listsize = 0;
                if(ReadListFromFile(newList, FileName) == OK) {
                    char newName[30];
                    GREEN; printf("请输入新表名称：");
                    YELLOW; scanf("%s", newName);
                    if(AddList(Lists, newName) == OK) {
                        // 成功添加到集合后，更新新表的内容
                        Lists.elem[Lists.length-1].L = newList;
                        WHITE; printf("文件中的线性表已成功创建为【%s】！\n", newName);
                        currentIndex = Lists.length - 1; // 自动选中新表
                    } else {
                        RED; printf("线性表【%s】创建失败！\n", newName);
                        // 释放newList内存
                        if(newList.elem != NULL) {
                            free(newList.elem);
                            newList.elem = NULL;
                        }
                    }
                } else {
                    RED; printf("从文件读取线性表失败！请检查文件是否存在且格式正确。\n");
                }
                break;
            }
                
            
            default:
                RED;
                printf("无效的选择，请重新输入！\n");
        }
        BLUE;
        printf("按任意键以继续操作......");
        _getch(); //暂停程序，等待用户按键
        system("cls"); //清屏
    }
    system("pause>nul"); 
    return 0;
}

// 菜单界面（已分区优化）
void show(){
    BLUE;   
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("                                        欢迎使用线性表管理系统                                              \n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    // 分区1：多线性表集合管理
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━  多线性表集合管理 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("1. 查看当前线性表集合列表\n");
    printf("2. 创建新线性表\n");
    printf("3. 查找并选中线性表\n");
    printf("4. 删除某一个线性表\n");

    // 分区2：单线性表基础操作
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 单线性表基础操作 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("5. 销毁当前线性表\n");
    printf("6. 清空当前线性表\n");
    printf("7. 判断当前线性表是否为空\n");
    printf("8. 获取当前线性表长度\n");

    // 分区3：单线性表元素操作
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 单线性表元素操作 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("9. 获取指定位置的元素\n");
    printf("10. 定位元素位置\n");
    printf("11. 获取元素前驱\n");
    printf("12. 获取元素后继\n");
    printf("13. 插入元素\n");
    printf("14. 删除元素\n");
    printf("15. 遍历输出线性表\n");

    // 分区4：单线性表高级功能
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 单线性表高级功能 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("16. 线性表升序排序\n");
    printf("17. 最大连续子数组和\n");
    printf("18. 和为k的子数组个数\n");

    // 分区5：系统操作
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━      系统操作     ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("19. 将线性表保存到文件中\n");
    printf("20. 附加功能\n");
    printf("21.读取文件以创建线性表\n");
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
    printf("1.线性表去重\n");
    printf("2.合并两个线性表\n");
    printf("3.求当前所有线性表交集\n");
    printf("4.线性表反转\n");
    printf("0.返回主菜单\n");
}

// 1. 初始化表：函数名称是InitList(L)；初始条件是线性表L不存在；操作结果是构造一个空的线性表；
status InitList(SqList& L){
    if(L.elem!=NULL)return INFEASIBLE;//线性表已存在，返回线性表不存在的错误代码
    L.elem=(int*)malloc(LIST_INIT_SIZE*sizeof(int));//为线性表分配内存空间
    if(L.elem==NULL)return OVERFLOW;//检查是否分配成功
    L.length=10;//将线性表的长度设置为10
    L.listsize=LIST_INIT_SIZE;//设置线性表的容量
    for(int i=0;i<L.length;i++){//为新建的线性表赋随机值（包含负数），方便测试
        L.elem[i]=rand()%200 - 100;//生成-100到99之间的随机整数，支持负数
    }
    return OK;//返回操作成功的代码
}

// 2. 销毁表：函数名称是DestroyList(L)；初始条件是线性表L已存在；操作结果是销毁线性表L；
status DestroyList(SqList& L){
    if(L.elem==NULL){return INFEASIBLE;}//如果线性表不存在，返回线性表不存在的错误代码
    free(L.elem);//释放线性表中元素的内存空间
    L.elem=NULL;//将线性表指针置为空指针
    L.length=0;//将线性表长度置为0
    L.listsize=0;//将线性表容量置为0
    return OK;//返回操作成功的代码
}

// 3.清空表：函数名称是ClearList(L)；初始条件是线性表L已存在；操作结果是将L重置为空表；
status ClearList(SqList& L){
    if(!L.elem)return INFEASIBLE;//如果线性表不存在，返回线性表不存在的错误代码
    L.length=0;return OK;//将线性表长度置为0，表示清空线性表，返回操作成功的代码
}

//4. 判定空表：函数名称是ListEmpty(L)；初始条件是线性表L已存在；操作结果是若L为空表则返回TRUE,否则返回FALSE；
status ListEmpty(SqList L){
    if(L.elem==NULL)return INFEASIBLE;//如果线性表不存在，返回线性表不存在的错误代码
    if(L.length==0)return TRUE;//如果线性表长度为0，返回TRUE，表示线性表为空
    return FALSE;//否则返回FALSE，表示线性表不为空
}

//5.求表长：函数名称是ListLength(L)；初始条件是线性表L已存在；操作结果是返回L中数据元素的个数；
status ListLength(SqList L){
    if(!L.elem)return INFEASIBLE;//如果线性表不存在，返回线性表不存在的错误代码
    return L.length;//返回线性表长度
}

//6.获得元素：函数名称是GetElem(L,i,e)；初始条件是线性表L已存在，1≤i≤ListLength(L)；操作结果是用e返回L中第i个数据元素的值；
status GetElem(SqList L,int i,ElemType &e){
    if(!L.elem)return INFEASIBLE;//如果线性表不存在，返回线性表不存在的错误代码
    if(i>L.length||i<1)return ERROR;//如果i不合法，返回ERROR
    e=L.elem[i-1];return OK;//返回第i个元素的值，注意数组下标从0开始，返回操作成功的代码
}

//7.定位元素：函数名称是LocateElem(L,e,compare)；初始条件是线性表L已存在；操作结果是返回L中第一个与e满足关系compare的数据元素的位序，若这样的数据元素不存在，则返回0；如果线性表L不存在，返回INFEASIBLE。
int LocateElem(SqList L,ElemType e){
    if(!L.elem)return INFEASIBLE;//如果线性表不存在，返回线性表不存在的错误代码
    for(int i=0;i<L.length;i++){//遍历线性表中的元素，比较每个元素与e是否相等（支持负数）
        if(L.elem[i]==e)return i+1;//如果找到与e相等的元素，返回该元素的位序，注意位序从1开始
    }
    return 0;//没有找到与e相等的元素，返回0
}

//8.获得前驱：函数名称是PriorElem(L,e,pre)；初始条件是线性表L已存在；操作结果是用pre返回L中第一个与e满足关系compare的数据元素的前驱，若这样的数据元素不存在，则返回INFEASIBLE。
status PriorElem(SqList L,ElemType e,ElemType &pre){
    if(!L.elem)return INFEASIBLE;//如果线性表不存在，返回线性表不存在的错误代码
    int i;
    for(i=0;i<L.length;i++){//遍历线性表中的元素，比较每个元素与e是否相等（支持负数）
        if(L.elem[i]==e)break;
    }
    if(i==L.length)return ERROR;//如果没找到元素e，返回ERROR
    if(i==0)return ERROR;//如果元素e是第一个元素，没有前驱，返回ERROR
    pre=L.elem[i-1];//否则，返回元素e的前驱
    return OK;//返回操作成功的代码
}

//9.获得后继：函数名称是NextElem(L,e,next)；初始条件是线性表L已存在；操作结果是用next返回L中第一个与e满足关系compare的数据元素的后继，若这样的数据元素不存在，则返回INFEASIBLE。
status NextElem(SqList L,ElemType e,ElemType &next){
    if(!L.elem)return INFEASIBLE;//如果线性表不存在，返回线性表不存在的错误代码
    int i;
    for(i=0;i<L.length;i++){
        if(L.elem[i]==e)break;//遍历线性表中的元素，比较每个元素与e是否相等（支持负数），如果找到与e相等的元素，跳出循环
    }
    if(i==L.length)return ERROR;//如果没找到元素e，返回ERROR
    if(i==L.length-1)return ERROR;//如果元素e是最后一个元素，没有后继，返回ERROR
    next=L.elem[i+1];//正常情况下则返回元素e的后继
    return OK;//返回操作成功的代码
}

//10.插入元素：函数名称是ListInsert(L,i,e)；初始条件是线性表L已存在，1≤i≤ListLength(L)+1；操作结果是在L中第i个位置之前插入新的数据元素e，L的长度加1；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE
status ListInsert(SqList &L,int i,ElemType e){
    if(!L.elem) return INFEASIBLE;//如果线性表不存在，返回线性表不存在的错误代码
    if(i > L.length + 1 || i < 1) return ERROR;//如果i不合法，返回ERROR
    if(L.length >= L.listsize) {//如果线性表长度达到容量，需要扩展线性表
        ElemType *newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));//重新分配内存空间，扩展容量
        if(!newbase) return ERROR;//如果重新分配内存空间失败，返回ERROR
        L.elem = newbase;//更新线性表的元素指针
        L.listsize += LISTINCREMENT;//更新线性表的容量
    }
    
    int j;
    for(j = L.length; j >= i; j--) {//从线性表的末尾开始，依次将元素向后移动一个位置，直到第i个位置
        L.elem[j] = L.elem[j - 1];//将第j-1个元素移动到第j个位置
    }
    L.elem[i - 1] = e;//在第i个位置插入新的数据元素e（支持负数），注意数组下标从0开始，所以是i-1
    L.length++;//线性表长度加1
    return OK;//返回操作成功的代码
}

//11.删除元素：如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status ListDelete(SqList &L,int i,ElemType &e){
    if(L.elem==NULL)return INFEASIBLE;//如果线性表不存在，返回线性表不存在的错误代码
    if(i>L.length||i<1)return ERROR;//如果i不合法，返回ERROR
    e=L.elem[i-1];//将第i个元素的值保存在e中，注意数组下标从0开始，所以是i-1
    for(int j=i-1;j<L.length-1;j++){
        L.elem[j]=L.elem[j+1];//从第i个位置开始，依次将后面的元素向前移动一个位置，覆盖掉第i个位置的元素
    }
    L.length--;//线性表长度减1
    return OK;//返回操作成功的代码
}

//12.遍历线性表：如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
status ListTraverse(SqList L){
    if(L.elem==NULL)return INFEASIBLE;//如果线性表不存在，返回线性表不存在的错误代码
    int i;
    WHITE;
    printf("线性表中的元素为：");
    for(i=0;i<L.length;i++){//遍历线性表中的元素，依次显示每个元素（支持负数），每个元素间空一格
        if(i > 0) printf(" ");
        printf("%d",L.elem[i]);
      
    }
    printf("\n");//输出换行符
    return OK;//返回操作成功的代码
}

// 遍历输出调用的visit函数
void visit(int elem){
    WHITE;
    printf("%d ", elem);
}

//13.最大连续子数组和：初始条件是线性表L已存在且非空，请找出一个具有最大和的连续子数组（子数组最少包含一个元素），操作结果是其最大和
void MaxSubArray(SqList L){
    if(L.elem==NULL){RED;printf("线性表不存在，无法计算最大连续子数组和！\n");return;}//如果线性表不存在，输出错误信息并返回
    if(L.length==0){RED;printf("线性表为空，无法计算最大连续子数组和！\n");return;}
    int max_sum = L.elem[0], current_sum = L.elem[0];//初始化最大和为第一个元素，当前和也为第一个元素
    // 记录最大子数组的起止位置（可选）
    int start = 0, end = 0, temp_start = 0;
    
    for(int i=1;i<L.length;i++){//从第二个元素开始遍历线性表（支持负数）
        if(current_sum < 0){//如果当前和小于0，说明之前的子数组和对后续元素没有贡献，重新开始一个新的子数组
            current_sum = L.elem[i];
            temp_start = i;
        }else{
            current_sum += L.elem[i];//否则，将当前元素加入当前和中
        }
        
        if(current_sum > max_sum){//更新最大和
            max_sum = current_sum;
            start = temp_start;
            end = i;
        }
    }
    WHITE;
    printf("线性表最大连续子数组和为：%d\n", max_sum);
    printf("该子数组为：");
    for(int i=start; i<=end; i++){
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

//14.和为k的子数组个数：初始条件是线性表L已存在且非空，操作结果是输出和为k的子数组个数（支持负数）
void SubArrayNum(SqList L , int k){
    if(L.elem==NULL){RED;printf("线性表不存在，无法计算和为k的子数组个数！\n");return;}
    if(L.length==0){RED;printf("线性表为空，无法计算和为k的子数组个数！\n");return;}
    
    int count = 0;
    // 暴力枚举所有子数组（简单实现，支持负数）
    for(int i=0; i<L.length; i++){
        int sum = 0;
        for(int j=i; j<L.length; j++){
            sum += L.elem[j];
            if(sum == k){
                count++;
            }
        }
    }
    WHITE;
    printf("线性表中和为%d的子数组个数为：%d\n", k, count);
}

//15.顺序表排序：初始条件是线性表L已存在，操作结果是对线性表进行升序排序（支持负数）
void sortList(SqList &L){
    if(L.elem==NULL){RED;printf("线性表不存在，无法排序！\n");return;}
    if(L.length<=1){return;}//长度为0或1无需排序
    
    // 冒泡排序（支持负数）
    for(int i=0; i<L.length-1; i++){
        for(int j=0; j<L.length-1-i; j++){
            if(L.elem[j] > L.elem[j+1]){
                // 交换元素
                ElemType temp = L.elem[j];
                L.elem[j] = L.elem[j+1];
                L.elem[j+1] = temp;
            }
        }
    }
}

//16.添加线性表到集合：初始条件是集合未满，操作结果是将新线性表添加到集合中
status AddList(LISTS &Lists,char ListName[]){
    // 检查集合是否已满
    if(Lists.length >= Lists.listsize){
        RED;printf("线性表集合已满，无法添加新表！\n");
        return ERROR;
    }
    // 检查表名是否重复
    if(LocateList(Lists, ListName) != -1){
        RED;printf("线性表名称【%s】已存在！\n", ListName);
        return ERROR;
    }
    // 初始化新线性表
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L.elem = NULL;
    if(InitList(Lists.elem[Lists.length].L) != OK){
        return ERROR;
    }
    Lists.length++;//集合长度加1
    return OK;
}

//17.从集合中删除线性表：初始条件是线性表存在于集合中，操作结果是删除该线性表
status RemoveList(LISTS &Lists,char ListName[]){
    int index = LocateList(Lists, ListName);
    if(index == -1){
        return ERROR;//表不存在
    }
    // 销毁线性表
    DestroyList(Lists.elem[index].L);
    // 移动后续元素
    for(int i=index; i<Lists.length-1; i++){
        Lists.elem[i] = Lists.elem[i+1];
    }
    Lists.length--;//集合长度减1
    return OK;
}

//18.在集合中查找线性表：初始条件是集合已初始化，操作结果是返回线性表下标，不存在返回-1
int LocateList(LISTS &Lists,char ListName[]){
    for(int i=0; i<Lists.length; i++){
        if(strcmp(Lists.elem[i].name, ListName) == 0){
            return i;//找到，返回下标
        }
    }
    return -1;//未找到
}

//19.显示集合中的线性表：初始条件是集合已初始化，操作结果是输出所有线性表名称
void showLists(LISTS Lists){
    WHITE;
    if(Lists.length == 0){
        printf("当前线性表集合为空！\n");
        return;
    }
    printf("当前线性表集合包含以下表：\n");
    for(int i=0; i<Lists.length; i++){
        printf("  %d. %s\n", i+1, Lists.elem[i].name);
    }
}

//20.将线性表保存到文件：初始条件是线性表存在，操作结果是将元素保存到文件（支持负数）
status SaveList(SqList L,char FileName[]){
    if(L.elem==NULL)return INFEASIBLE;
    FILE *fp = fopen(FileName, "w");
    if(fp == NULL)return ERROR;
    // 写入元素个数
    fprintf(fp, "%d\n", L.length);
    // 写入每个元素（支持负数）
    for(int i=0; i<L.length; i++){
        fprintf(fp, "%d ", L.elem[i]);
    }
    fclose(fp);
    return OK;
}

//21.线性表去重：初始条件是线性表存在，操作结果是删除重复元素（支持负数）
status RemoveDuplicates(SqList &L){
    if(L.elem==NULL)return INFEASIBLE;
    if(L.length<=1)return OK;//无重复可能
    
    // 去重逻辑（支持负数）
    int new_len = 1;//至少保留第一个元素
    for(int i=1; i<L.length; i++){
        int is_dup = 0;
        // 检查当前元素是否与已保留元素重复
        for(int j=0; j<new_len; j++){
            if(L.elem[i] == L.elem[j]){
                is_dup = 1;
                break;
            }
        }
        if(!is_dup){
            L.elem[new_len] = L.elem[i];
            new_len++;
        }
    }
    L.length = new_len;//更新长度
    return OK;
}

//22.线性表反转：初始条件是线性表存在，操作结果是反转元素顺序（支持负数）
status ReverseList(SqList &L){
    if(L.elem==NULL)return INFEASIBLE;
    if(L.length<=1)return OK;//无需反转
    
    int left = 0, right = L.length-1;
    while(left < right){
        // 交换左右元素
        ElemType temp = L.elem[left];
        L.elem[left] = L.elem[right];
        L.elem[right] = temp;
        left++;
        right--;
    }
    return OK;
}

//23.合并两个线性表：初始条件是两个线性表存在，操作结果是将L2元素追加到L1末尾（支持负数）
status MergeLists(SqList &L1, SqList L2){
    if(L1.elem==NULL || L2.elem==NULL)return INFEASIBLE;
    if(L2.length == 0)return OK;//L2为空无需合并
    
    // 扩展L1容量（如果需要）
    int need_size = L1.length + L2.length;
    if(need_size > L1.listsize){
        ElemType *newbase = (ElemType *)realloc(L1.elem, need_size * sizeof(ElemType));
        if(newbase == NULL)return ERROR;
        L1.elem = newbase;
        L1.listsize = need_size;
    }
    // 复制L2元素到L1末尾
    memcpy(L1.elem + L1.length, L2.elem, L2.length * sizeof(ElemType));
    L1.length += L2.length;
    return OK;
}

//24.求所有线性表交集：初始条件是集合中有至少2个线性表，操作结果是返回所有表的交集（支持负数）
status IntersectLists(LISTS Lists, SqList &Intersect){
    // 初始化交集表
    if(InitList(Intersect) != OK)return ERROR;
    ClearList(Intersect);//清空初始的随机值
    
    // 取第一个表作为基准
    SqList base = Lists.elem[0].L;
    if(base.length == 0)return OK;//基准表为空，交集为空
    
    // 遍历基准表的每个元素（支持负数）
    for(int i=0; i<base.length; i++){
        ElemType elem = base.elem[i];
        // 检查该元素是否存在于所有其他表中
        int exist_in_all = 1;
        for(int j=1; j<Lists.length; j++){
            if(LocateElem(Lists.elem[j].L, elem) == 0){
                exist_in_all = 0;
                break;
            }
        }
        // 如果存在于所有表中，且未加入交集，则添加
        if(exist_in_all && LocateElem(Intersect, elem) == 0){
            ListInsert(Intersect, Intersect.length+1, elem);
        }
    }
    return OK;
}

//25.从文件读取线性表：初始条件是文件存在且格式正确，操作结果是创建线性表（支持负数）
status ReadListFromFile(SqList &L, char FileName[]){
    FILE *fp = fopen(FileName, "r");
    if(fp == NULL)return ERROR;   
    // 读取元素个数
    int len;
    if(fscanf(fp, "%d", &len) != 1) {
        fclose(fp);
        return ERROR;
    }
    if(len <= 0) {
        fclose(fp);
        return ERROR;
    }
    
    // 初始化线性表
    if(L.elem != NULL)free(L.elem);
    L.elem = (ElemType *)malloc(len * sizeof(ElemType));
    if(L.elem == NULL) {
        fclose(fp);
        return OVERFLOW;
    }
    L.listsize = len;
    L.length = len;
    
    // 读取元素（支持负数）
    for(int i=0; i<len; i++){
        if(fscanf(fp, "%d", &L.elem[i]) != 1) {
            free(L.elem);
            L.elem = NULL;
            fclose(fp);
            return ERROR;
        }
    }
    fclose(fp);
    return OK;
}