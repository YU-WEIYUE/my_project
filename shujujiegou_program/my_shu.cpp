/*----------头文件的引入---------*/
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include <time.h>
#include <climits>
using namespace std;

/*----------预定义-----------*/

//定义布尔类型TRUE和FALSE
#undef OVERFLOW 
#define TRUE 1
#define FALSE 0

//定义函数返回值类型
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//数据元素类型定义
typedef int status;
typedef int KeyType;

// 二叉树结点数据类型定义
typedef struct {
    KeyType key; // 结点关键字
    char others[20]; // 数据
} TElemType;

// 二叉链表结点的定义
typedef struct BiTNode {
    TElemType data; // 结点数据
    struct BiTNode *lchild, *rchild; // 左右子树指针
} BiTNode, *BiTree;

// 二叉树的集合类型定义
typedef struct {
// 元素的集合
    struct {
        char name[30]; // 标识元素的名称
        BiTree T; // 二叉树
    } elem[10]; // 最多存储 10 个元素
    int length; // 元素个数
} LISTS;

LISTS Lists = {0}; // 二叉树集合的定义 Lists


void visit(BiTree T){//访问函数：打印结点的关键字
    printf("%d ",T->data.key);
}
void printSpaces(int n) {// 辅助函数：打印n个空格
    if(n <= 0) return;
    for(int i=0; i<n; i++) printf(" ");
}

//定义字体颜色切换
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
#define GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

/*---- 函数申明 ----*/
status CreateBiTree(BiTree &T, TElemType definition[]);  //创建
status DestroyBiTree(char treeName[]);  //销毁
status ClearBiTree(BiTree &T);  //清空
status BiTreeEmpty(BiTree &T);  //判空
int BiTreeDepth(BiTree T);   //求深度
BiTNode* LocateNode(BiTree T, KeyType e);   //查找结点
status Assign(BiTree &T, KeyType e, TElemType value);  //结点赋值
BiTNode* GetSibling(BiTree T, KeyType e);  //获得兄弟结点
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);  //插入结点
status DeleteNode(BiTree &T, KeyType e);  //删除结点
status PreOrderTraverse(BiTree T, void(*visit)(BiTree));  //前序遍历
status InOrderTraverse(BiTree T, void(*visit)(BiTree));  //中序遍历
status PostOrderTraverse(BiTree T, void(*visit)(BiTree));  //后续遍历
status LevelOrderTraverse(BiTree T, void(*visit)(BiTree));  //层序遍历
status SaveBiTree(BiTree T, char FileName[]);  //保存到文件
status LoadBiTree(BiTree &T, char FileName[]); // 从文件加载
int MaxPathSum(BiTree T);  //最大路径和
BiTree LowestCommonAncestor(BiTree T, int e1, int e2);  //最近公共祖先
BiTree InvertTree(BiTree T);  //翻转二叉树
BiTree findfather(BiTree root, KeyType e);  //找到父节点
int countsons(BiTree T, KeyType e);  //统计子节点个数
void show();  //显示菜单界面
void showplus();  //显示附加功能菜单界面
void showLists(LISTS Lists);  //显示集合中有哪些二叉树
int LocateList(LISTS &Lists,char ListName[]);  //在集合中查找二叉树，返回下标
void searchmostBST(BiTree T);//二叉搜索树中的众数
status CreateBiTreeHelper(BiTree &T, TElemType definition[], int &i); 
void printSpaces(int n);  // 打印n个空格
void drawTree(BiTree T);  // 绘制二叉树结构
void huffmanEncode01(const char str[]);//哈夫曼编码01字符串


//主函数
int main(){
    srand((unsigned)time(NULL));//设置随机数种子
    int choice=1;//记录用户选择
    
    // 用下标记录当前选中的二叉树，-1表示未选中
    int currentIndex = -1; 
    
    Lists.length=0;//初始化二叉树集合长度为0，表示集合中没有默认二叉树

    while(choice){
        system("cls"); // 清屏
        show(); //显示菜单界面
        
        // 高亮显示当前选中的二叉树名
        if(currentIndex != -1) {
            YELLOW;
            printf("\n");
            printf("╔═══════════════════════════════════════════════════════════╗\n");
            printf("                    当前选中二叉树：%s                          \n", Lists.elem[currentIndex].name);
            printf("╚═══════════════════════════════════════════════════════════╝\n");
        }
        
        GREEN;
        printf("\n请输入您的选择：");

        YELLOW;
        scanf("%d",&choice);//获取用户选择
        getchar(); // 吸收换行符

        switch(choice){
            // ========== 系统操作 ==========
            case 0:
                //退出系统
                GREEN;
                printf("感谢使用二叉树管理系统！再见！\n");
                // 释放所有二叉树内存，防止内存泄漏
                for (int i = 0; i < Lists.length; i++) {
                    ClearBiTree(Lists.elem[i].T);
                }
                printf("输入任意键退出...");
                _getch();
                return 0;

            // ========== 多二叉树集合管理 ==========
            case 1:{//查看当前二叉树集合中有哪些二叉树
                showLists(Lists);
                break;}

            case 2:{//创建新一个二叉树
                if (Lists.length >= 10) {
                    RED;
                    printf("错误：二叉树集合已满（最多10个）！\n");
                    WHITE;
                    break;
                }
                char treeName[30];
                GREEN;
                printf("请输入要创建的二叉树名称：");
                YELLOW;
                scanf("%29s",treeName);
                getchar();
                
                TElemType def[1000];
                printf("请输入先序遍历序列（格式：key others，0表示空节点，-1结束）：\n");
                int i = 0;
                while (1) {
                    scanf("%d", &def[i].key);
                    if (def[i].key == -1) break;
                    if (def[i].key != 0) {
                        scanf("%19s", def[i].others);
                    } else {
                        strcpy(def[i].others, "NULL");
                    }
                    i++;
                    if (i >= 1000) {
                        RED;
                        printf("错误：节点数量超过上限（1000个）！\n");
                        WHITE;
                        break;
                    }
                }
                def[i].key = -1;
                
                status res = CreateBiTree(Lists.elem[Lists.length].T, def);
                if (res == OK) {
                    strcpy(Lists.elem[Lists.length].name, treeName);
                    Lists.length++;
                    WHITE;printf("二叉树【%s】创建成功！\n",treeName);
                    currentIndex = Lists.length - 1; // 自动选中新树
                }
                else{RED;printf("二叉树【%s】创建失败！错误码：%d\n",treeName, res);}
                break;
            }

            case 3:{//查找一个二叉树和进行操作
                char treeName[30];
                GREEN;
                printf("请输入要查找的二叉树名称：");
                YELLOW;
                scanf("%29s",treeName);
                
                // 查找下标
                currentIndex = LocateList(Lists, treeName);
                
                if(currentIndex != -1){
                    WHITE;printf("二叉树【%s】查找成功！现在可以对其进行操作了！\n", Lists.elem[currentIndex].name);
                }
                else{RED;printf("二叉树【%s】查找失败！\n",treeName);}
                break;
            }

            // ========== 二叉树基本操作 ==========
            case 4://销毁当前选中的二叉树
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                if(DestroyBiTree(Lists.elem[currentIndex].name)==OK){
                    WHITE;printf("二叉树【%s】销毁成功！\n", Lists.elem[currentIndex].name);
                    currentIndex = -1; // 销毁后置为未选中
                }
                else{RED;printf("二叉树不存在，销毁失败！\n");}
                break;
            
            case 5:{//清空当前选中的二叉树
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                if(ClearBiTree(Lists.elem[currentIndex].T)==OK){WHITE;printf("二叉树【%s】清空成功！\n", Lists.elem[currentIndex].name);}
                else{RED;printf("二叉树不存在，无法清空！\n");}
                break;
            }

            case 6:{//判断当前选中的二叉树是否为空
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                if(BiTreeEmpty(Lists.elem[currentIndex].T)){RED;printf("二叉树【%s】为空！\n", Lists.elem[currentIndex].name);}
                else {WHITE;printf("二叉树【%s】不为空！\n", Lists.elem[currentIndex].name);}
                break;
            }

            case 7:{//求当前选中的二叉树的深度
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                int depth=BiTreeDepth(Lists.elem[currentIndex].T);
                WHITE;printf("二叉树【%s】深度为：%d\n", Lists.elem[currentIndex].name, depth);
                break;
            }

            // ========== 二叉树遍历操作 ==========
            case 8:{//前序遍历当前选中的二叉树
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                WHITE;printf("前序遍历结果：");
                PreOrderTraverse(Lists.elem[currentIndex].T, visit);
                printf("\n");
                break;
            }

            case 9:{//中序遍历当前选中的二叉树
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                WHITE;printf("中序遍历结果：");
                InOrderTraverse(Lists.elem[currentIndex].T, visit);
                printf("\n");
                break;
            }

            case 10:{//后序遍历当前选中的二叉树
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                WHITE;printf("后序遍历结果：");
                PostOrderTraverse(Lists.elem[currentIndex].T, visit);
                printf("\n");
                break;
            }

            case 11:{//层序遍历当前选中的二叉树
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                WHITE;printf("层序遍历结果：");
                LevelOrderTraverse(Lists.elem[currentIndex].T, visit);
                printf("\n");
                break;
            }

            // ========== 二叉树单节点操作 ==========
            case 12:{//查找关键字为e的结点
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                KeyType e;
                GREEN;
                printf("请输入要查找的关键字e：");
                YELLOW;
                scanf("%d", &e);
                if (LocateNode(Lists.elem[currentIndex].T, e) != NULL) {
                    WHITE;printf("找到关键字为%d的结点\n", e);
                } else {
                    RED;printf("未找到关键字为%d的结点\n", e);
                }
                break;
            }               

            case 13:{//为关键字为e的结点赋值
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                KeyType e;
                TElemType value;
                GREEN;
                printf("请输入要修改的结点关键字e：");
                YELLOW;
                scanf("%d", &e);
                GREEN;
                printf("请输入新的关键字和数据（key others）：");
                YELLOW;
                scanf("%d %19s", &value.key, value.others);
                
                status res = Assign(Lists.elem[currentIndex].T, e, value);
                if (res == OK) {
                    WHITE;printf("结点赋值成功！\n");
                } else if (res == INFEASIBLE) {
                    RED;printf("赋值失败：新关键字已存在！\n");
                } else {
                    RED;printf("赋值失败：未找到该结点！\n");
                }
                break;
            }          

            case 14:{//获得关键字为e的结点的兄弟结点
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                KeyType e;
                GREEN;
                printf("请输入要获取兄弟结点的关键字e：");
                YELLOW;
                scanf("%d", &e);
                
                BiTNode* sibling = GetSibling(Lists.elem[currentIndex].T, e);
                if (sibling != NULL) {
                    WHITE;printf("关键字为%d的结点的兄弟结点是：%d\n", e, sibling->data.key);
                } else {
                    RED;printf("关键字为%d的结点没有兄弟结点或结点不存在！\n", e);
                }
                break;
            }

            case 15:{//插入结点
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                KeyType e;
                int LR;
                TElemType c;
                GREEN;
                printf("请输入待插入结点的关键字和数据（key others）：");
                YELLOW;
                scanf("%d %19s", &c.key, c.others);
                GREEN;
                printf("请输入父结点关键字e（插入为根结点请输入-1）：");
                YELLOW;
                scanf("%d", &e);
                
                if (e == -1) {
                    LR = -1;
                } else {
                    GREEN;
                    printf("请输入插入位置（0=左孩子，1=右孩子）：");
                    YELLOW;
                    scanf("%d", &LR);
                }
                
                status res = InsertNode(Lists.elem[currentIndex].T, e, LR, c);
                if (res == OK) {
                    WHITE;printf("结点%d插入成功！\n", c.key);
                } else if (res == INFEASIBLE) {
                    RED;printf("插入失败：关键字已存在！\n");
                } else {
                    RED;printf("插入失败：父结点不存在或位置无效！\n");
                }
                break;
            }
            
            case 16:{//找到关键字为e的结点的父亲结点
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                KeyType e;
                GREEN;
                printf("请输入要查找父亲结点的关键字e：");
                YELLOW;
                scanf("%d", &e);
                
                BiTNode* father = findfather(Lists.elem[currentIndex].T, e);
                if (father != NULL) {
                    WHITE;printf("关键字为%d的结点的父亲结点是：%d\n", e, father->data.key);
                } else {
                    RED;printf("关键字为%d的结点是根结点或结点不存在！\n", e);
                }
                break;
            }

            case 17:{//统计关键字为e的结点的子节点个数
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                KeyType e;
                GREEN;
                printf("请输入要统计子节点个数的关键字e：");
                YELLOW;
                scanf("%d", &e);
                
                int sons = countsons(Lists.elem[currentIndex].T, e);
                if (sons == -1) {
                    RED;printf("结点不存在！\n");
                } else {
                    WHITE;printf("关键字为%d的结点有%d个子节点\n", e, sons);
                }
                break;
            }

            // ========== 二叉树高级功能 ==========
            case 18:{//求二叉树的最大路径和
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                int maxSum = MaxPathSum(Lists.elem[currentIndex].T);
                WHITE;printf("二叉树的最大路径和为：%d\n", maxSum);
                break;
            }
                
            case 19:{//求两个结点的最近公共祖先
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                KeyType e1, e2;
                GREEN;
                printf("请输入第一个结点的关键字：");
                YELLOW;
                scanf("%d", &e1);
                GREEN;
                printf("请输入第二个结点的关键字：");
                YELLOW;
                scanf("%d", &e2);
                
                BiTree lca = LowestCommonAncestor(Lists.elem[currentIndex].T, e1, e2);
                if (lca != NULL) {
                    WHITE;printf("结点%d和结点%d的最近公共祖先是：%d\n", e1, e2, lca->data.key);
                } else {
                    RED;printf("至少有一个结点不存在！\n");
                }
                break;
            }

            case 20:{//翻转二叉树
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                InvertTree(Lists.elem[currentIndex].T);
                WHITE;printf("二叉树翻转成功！\n");
                break;
            }

            // ========== 系统操作 ==========
            case 21:{//将当前选中的二叉树保存到文件中
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                char fileName[30];
                GREEN;
                printf("请输入要保存的文件名：");
                YELLOW;
                scanf("%29s",fileName);
                if(SaveBiTree(Lists.elem[currentIndex].T, fileName)==OK){
                    WHITE;printf("二叉树【%s】已保存到文件【%s】！\n", Lists.elem[currentIndex].name, fileName);
                }else{
                    RED;printf("文件保存失败！\n");
                }
                break;
            }

            case 22:{//附加功能
                int plusLoop = 1;
                while(plusLoop) {
                system("cls");
                showplus();
                // 提示当前选中的二叉树（如果有）
                if(currentIndex != -1) {
                    YELLOW;
                    printf("\n 当前主菜单选中二叉树：%s\n", Lists.elem[currentIndex].name);
                }

                GREEN;
                printf("\n请输入您的选择：");
                int pluschoice;
                YELLOW;
                scanf("%d", &pluschoice);
                getchar();

                switch(pluschoice) {
                    case 0: // 返回主菜单
                    plusLoop = 0;
                    break;

                    case 1: // 1. 绘制二叉树
                    if(currentIndex == -1){RED;printf(" 请先在主菜单选中一个二叉树！\n");break;}
                    printf("\n\n");
                    drawTree(Lists.elem[currentIndex].T);
                    break;

                    case 2: // 2. 搜索二叉树中的众数
                    if(currentIndex == -1){RED;printf(" 请先在主菜单选中一个二叉树！\n");break;}
                    searchmostBST(Lists.elem[currentIndex].T);
                    break;

                    case 3: // 3. 哈夫曼编码01字符串
                    char inputStr[100];
                    GREEN; printf("请输入要编码的字符串：");
                    YELLOW; gets(inputStr);
                    huffmanEncode01(inputStr);
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

            // ========== 新增：删除节点功能 ==========
            case 23:{
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个二叉树！\n");break;}
                KeyType e;
                GREEN;
                printf("请输入要删除的节点关键字：");
                YELLOW;
                scanf("%d", &e);
                if(DeleteNode(Lists.elem[currentIndex].T, e) == OK){
                    WHITE;printf("节点 %d 删除成功！\n", e);
                }else{
                    RED;printf("删除失败：节点不存在！\n");
                }
                break;
            }

            // ========== 新增：从文件加载二叉树 ==========
            case 24:{
                if (Lists.length >= 10) {
                    RED;printf("二叉树集合已满！\n");break;
                }
                char fileName[30], treeName[30];
                GREEN;
                printf("请输入加载的文件名：");
                YELLOW;scanf("%s", fileName);
                GREEN;
                printf("请给加载的二叉树命名：");
                YELLOW;scanf("%s", treeName);

                BiTree newT = NULL;
                if(LoadBiTree(newT, fileName) == OK){
                    strcpy(Lists.elem[Lists.length].name, treeName);
                    Lists.elem[Lists.length].T = newT;
                    Lists.length++;
                    currentIndex = Lists.length - 1;
                    WHITE;printf("加载成功！已自动选中！\n");
                }else{
                    RED;printf("加载失败！文件不存在或格式错误！\n");
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

//菜单
void show(){
    BLUE;
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("                                        欢迎使用二叉树管理系统                                              \n");       
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n\n");
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━  多二叉树表集合管理 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("1. 查看当前二叉树集合中有哪些二叉树\n");
    printf("2. 创建新一个二叉树\n");
    printf("3. 选中一个二叉树进行操作\n");
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━  二叉树基本操作 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("4. 销毁当前选中的二叉树\n");
    printf("5. 清空当前选中的二叉树\n");
    printf("6. 判断当前选中的二叉树是否为空\n");
    printf("7. 求当前选中的二叉树的深度\n");
    printf("8. 前序遍历当前选中的二叉树\n");
    printf("9. 中序遍历当前选中的二叉树\n");
    printf("10. 后序遍历当前选中的二叉树\n");
    printf("11. 层序遍历当前选中的二叉树\n");
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━  二叉树单节点操作 ━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("12.查找关键字为e的结点\n");
    printf("13.为关键字为e的结点赋值\n");
    printf("14.获得关键字为e的结点的兄弟结点\n");
    printf("15.插入结点\n");
    printf("16.找到关键字为e的结点的父亲结点\n");
    printf("17.统计关键字为e的结点的子节点个数\n");
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━  二叉树高级功能 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("18.求二叉树的最大路径和\n");
    printf("19.求两个结点的最近公共祖先\n");
    printf("20.翻转二叉树\n");
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━  文件与节点操作 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("21.保存二叉树到文件\n");
    printf("22.附加功能\n");
    printf("23.删除节点\n");
    printf("24.从文件加载二叉树\n");
    GREEN;
    printf("0.退出系统\n");

}
void showplus(){
    BLUE;   
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("                                        欢迎使用附加功能菜单                                              \n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("                                                                              Powered by: CS2503班——U202514774\n\n");
    GREEN;
    printf("1.绘制二叉树\n");
    printf("2.搜索二叉树中的众数\n");
    printf("3.哈夫曼编码01字符串\n");
    printf("0.返回主菜单\n");
}
//功能函数实现
// 辅助函数：递归创建二叉树
status CreateBiTreeHelper(BiTree &T, TElemType definition[], int &i) {
    // 递归出口：序列遍历结束
    if (definition[i].key == -1) {
        T = NULL;
        return OK;
    }

    // 空节点
    if (definition[i].key == 0) {
        T=NULL;
        i++;
        return OK;
    }

    // 创建节点
    T = (BiTree)malloc(sizeof(BiTNode));
    if (T == NULL) {
        return OVERFLOW; // 内存分配失败
    }
    T->lchild = NULL;
    T->rchild = NULL;
    T->data = definition[i];
    i++;

    // 递归创建左右子树
    status leftStatus = CreateBiTreeHelper(T->lchild, definition, i);
    if (leftStatus != OK) {
        free(T); // 左子树创建失败，释放当前节点
        return leftStatus;
    }

    status rightStatus = CreateBiTreeHelper(T->rchild, definition, i);
    if (rightStatus != OK) {
        ClearBiTree(T->lchild); // 右子树创建失败，释放左子树
        free(T); // 释放当前节点
        return rightStatus;
    }

    return OK;
}

// 主创建函数
status CreateBiTree(BiTree &T, TElemType definition[]) {
    // 第一步：检查数据合法性
    int len = 0;
    // 先计算数组长度，防止越界
    while (definition[len].key != -1) {
        len++;
        if (len > 1000) { // 防止无限循环，设置最大长度
            return INFEASIBLE;
        }
    }

    // 检查重复关键字
    for (int j = 0; j < len; j++) {
        if (definition[j].key == 0) continue;
        for (int k = j + 1; k < len; k++) {
            if (definition[k].key == 0) continue;
            if (definition[j].key == definition[k].key) {
                return INFEASIBLE; // 重复关键字
            }
        }
    }

    // 第二步：递归创建二叉树
    int i = 0;
    status result = CreateBiTreeHelper(T, definition, i);
    
    // 如果创建失败，确保T为NULL
    if (result != OK) {
        T = NULL;
    }
    
    return result;
}

status DestroyBiTree(char treeName[]){//2.销毁二叉树
    int index = LocateList(Lists, treeName);
    if(index == -1) return ERROR; // 未找到
    
    // 1. 销毁二叉树
    ClearBiTree(Lists.elem[index].T);
    // 2. 从集合中移除
    for(int i=index; i<Lists.length-1; i++){
        Lists.elem[i] = Lists.elem[i+1];
    }
    Lists.length--;
    return OK;
}

status ClearBiTree(BiTree &T){//3.清空
    if(T==NULL)return OK;
    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);
    free(T);
    T=NULL;
    return OK;
}

status BiTreeEmpty(BiTree &T){//4.判空
    if(T==NULL)return TRUE;
    else return FALSE;
}

int BiTreeDepth(BiTree T){//5.求深度
    if(T==NULL)return 0;
    int l=BiTreeDepth(T->lchild);
    int r=BiTreeDepth(T->rchild);
    return max(l,r)+1;
}

BiTNode* LocateNode(BiTree T, KeyType e){//6.查找结点
    if(T==NULL)return NULL;
    if(T->data.key==e)return T;
    BiTNode* p=LocateNode(T->lchild,e);
    if(p!=NULL)return p;
    return LocateNode(T->rchild,e);
}

status Assign(BiTree &T, KeyType e, TElemType value){//7.结点赋值
    if(value.key != e && LocateNode(T, value.key) != NULL){
    return INFEASIBLE; // 新关键字已存在
}
    BiTNode* p=LocateNode(T,e);
    if(p==NULL)return ERROR;
    p->data=value;
    return OK;
}

BiTNode* GetSibling(BiTree T, KeyType e){//8.获得兄弟结点
    if(T==NULL)return NULL;
    if(T->lchild!=NULL&&T->lchild->data.key==e){
        return T->rchild;
    }
    if(T->rchild!=NULL&&T->rchild->data.key==e){
        return T->lchild;
    }
    BiTNode*p=GetSibling(T->lchild,e);
    if(p!=NULL)return p;
    return GetSibling(T->rchild,e);
}

//插入结点：函数名称是InsertNode(T,e,LR,c)；初始条件是二叉树T存在，e是和T中结点关键字类型相同的给定值，LR为0或1，c是待插入结点；操作结果是根据LR为0或者1，插入结点c到T中，作为关键字为e的结点的左或右孩子结点，结点e的原有左子树或右子树则为结点c的右子树；
//特殊情况，c插入作为根结点？可以考虑LR为-1时，作为根结点插入，原根结点作为c的右子树。

status InsertNode(BiTree &T, KeyType e, int LR, TElemType c){//9.插入结点
    // 先处理插入为新根的情况（即使T为空也可以）
    if(LocateNode(T, c.key) != NULL){
    return INFEASIBLE; // 关键字已存在
}
    if(LR == -1){
        BiTree newnode=(BiTree)malloc(sizeof(BiTNode));
        if(newnode == NULL) return OVERFLOW;
        newnode->data=c;
        newnode->lchild=NULL;
        newnode->rchild=T;
        T=newnode;
        return OK;
    }
    
    if(T == NULL) return ERROR; // 非根节点插入，树为空则失败
    BiTNode* p = LocateNode(T, e);
    if(p == NULL) return ERROR;
    
    BiTree newnode=(BiTree)malloc(sizeof(BiTNode));
    if(newnode == NULL) return OVERFLOW;
    newnode->data=c;
    newnode->lchild=NULL;
    
    if(LR==0){
        newnode->rchild=p->lchild;
        p->lchild=newnode;
    }else if(LR==1){
        newnode->rchild=p->rchild;
        p->rchild=newnode;
    }else{
        free(newnode); // 释放已分配的内存
        return ERROR;
    }
    
    return OK;
}

status DeleteNode(BiTree &T, KeyType e){//10.删除结点
    BiTree p=LocateNode(T,e);
    int sons=countsons(T,e);
    if(p==NULL)return ERROR;
    BiTree father=findfather(T,e);
    if(sons==0){  // 叶子节点
    if(father == NULL){ // 根节点（整棵树只有一个节点）
        free(p);
        T = NULL;
    }else if(father->lchild == p){
        free(p);
        father->lchild = NULL; // 必须将父节点指针置空
    }else{
        free(p);
        father->rchild = NULL; // 必须将父节点指针置空
    }
    return OK;
}
    else if(sons==1){
        BiTree newnode=p->lchild?p->lchild:p->rchild;
        if(!father){
            free(p);
            p=NULL;
            T=newnode;
            return OK;
        }
        else if(father->lchild==p){
            father->lchild=newnode;
        }
        else{
            father->rchild=newnode;
        }
        free(p);
        p=NULL;
        return OK;
    }
    else{
        BiTree newnode=p->lchild;
        if(!father){
            T=newnode;
        }
        else if(father->lchild==p){
            father->lchild=newnode;
        }
        else{
            father->rchild=newnode;
        }
        BiTree q=newnode;
        while(q->rchild){
            q=q->rchild;
        }
        q->rchild=p->rchild;
        free(p);p=NULL;
        return OK;
    }
}

status PreOrderTraverse(BiTree T, void(*visit)(BiTree)){//11.前序遍历
    if(T==NULL)return OK;
    visit(T);
    PreOrderTraverse(T->lchild,visit);
    PreOrderTraverse(T->rchild,visit);
    return OK;
}

status InOrderTraverse(BiTree T, void(*visit)(BiTree)){//12.中序遍历
    if(T==NULL)return OK;
    InOrderTraverse(T->lchild,visit);
    visit(T);
    InOrderTraverse(T->rchild,visit);
    return OK;
}

status PostOrderTraverse(BiTree T, void(*visit)(BiTree)){//13.后序遍历
    if(T==NULL)return OK;
    PostOrderTraverse(T->lchild,visit);
    PostOrderTraverse(T->rchild,visit);
    visit(T);
    return OK;
}

status LevelOrderTraverse(BiTree T, void(*visit)(BiTree)){//14.层序遍历
    if(T==NULL)return OK;
    queue<BiTree> q;
    q.push(T);
    while(!q.empty()){
        BiTree p=q.front();
        q.pop();
        visit(p);
        if(p->lchild)q.push(p->lchild);
        if(p->rchild)q.push(p->rchild);
    }
    return OK;
}

status SaveBiTree(BiTree T, char FileName[]){//15.保存到文件
    if(T==NULL)return ERROR;
    FILE* fp=fopen(FileName,"w");
    if(fp==NULL)return ERROR;
    queue<BiTree> q;
    q.push(T);
    while(!q.empty()){
        BiTree p=q.front();
        q.pop();
        fprintf(fp,"%d %s\n",p->data.key,p->data.others);
        if(p->lchild)q.push(p->lchild);
        else fprintf(fp,"0 NULL\n"); // 空节点也保存两个字段
        if(p->rchild)q.push(p->rchild);
        else fprintf(fp,"0 NULL\n"); // 空节点也保存两个字段
    }
    fclose(fp);
    return OK;
}

// ====================== 修复：纯C++98兼容 从文件加载二叉树 ======================
status LoadBiTree(BiTree &T, char FileName[]) {
    FILE *fp = fopen(FileName, "r");
    if (!fp) return ERROR;

    int key;
    char name[20];
    // C++98要求>>之间必须有空格
    vector<pair<int, string> > nodes;

    // 读取所有节点数据
    while (fscanf(fp, "%d %s", &key, name) == 2) {
        nodes.push_back(make_pair(key, string(name)));
    }
    fclose(fp);

    if (nodes.empty()) return ERROR;

    // 清空原有树
    ClearBiTree(T);

    // 根节点
    if (nodes[0].first == 0) {
        T = NULL;
        return OK;
    }

    T = (BiTree)malloc(sizeof(BiTNode));
    if (!T) return OVERFLOW;
    T->data.key = nodes[0].first;
    strcpy(T->data.others, nodes[0].second.c_str());
    T->lchild = NULL;
    T->rchild = NULL;

    queue<BiTree> q;
    q.push(T);
    int idx = 1;

    // 层序构建二叉树（和保存格式完全对应）
    while (!q.empty() && idx < nodes.size()) {
        BiTree cur = q.front();
        q.pop();

        // 左孩子
        int lkey = nodes[idx].first;
        string lname = nodes[idx].second;
        idx++;

        // 右孩子
        int rkey = -1;
        string rname = "";
        if (idx < nodes.size()) {
            rkey = nodes[idx].first;
            rname = nodes[idx].second;
            idx++;
        }

        // 创建左孩子
        if (lkey != 0) {
            cur->lchild = (BiTree)malloc(sizeof(BiTNode));
            cur->lchild->data.key = lkey;
            strcpy(cur->lchild->data.others, lname.c_str());
            cur->lchild->lchild = NULL;
            cur->lchild->rchild = NULL;
            q.push(cur->lchild);
        } else {
            cur->lchild = NULL;
        }

        // 创建右孩子
        if (rkey != 0) {
            cur->rchild = (BiTree)malloc(sizeof(BiTNode));
            cur->rchild->data.key = rkey;
            strcpy(cur->rchild->data.others, rname.c_str());
            cur->rchild->lchild = NULL;
            cur->rchild->rchild = NULL;
            q.push(cur->rchild);
        } else {
            cur->rchild = NULL;
        }
    }

    return OK;
}
// ==========================================================================

int MaxPathSum(BiTree T){//16.最大路径和
    if(T==NULL)return 0;
    int l=MaxPathSum(T->lchild);
    int r=MaxPathSum(T->rchild);
    return max(max(l,r)+T->data.key,T->data.key);
}

// ====================== 修复完成：功能19 最近公共祖先 ======================
static int g_lca_e1, g_lca_e2;

BiTree lcaHelper(BiTree node) {
    if (node == NULL) return NULL;
    if (node->data.key == g_lca_e1 || node->data.key == g_lca_e2) {
        return node;
    }
    BiTree left = lcaHelper(node->lchild);
    BiTree right = lcaHelper(node->rchild);
    if (left != NULL && right != NULL) return node;
    return left ? left : right;
}

BiTree LowestCommonAncestor(BiTree T, int e1, int e2) {
    if (LocateNode(T, e1) == NULL || LocateNode(T, e2) == NULL) {
        return NULL;
    }
    g_lca_e1 = e1;
    g_lca_e2 = e2;
    return lcaHelper(T);
}
// ==========================================================================

BiTree InvertTree(BiTree T){//18.翻转二叉树
    if(T==NULL)return NULL;
    BiTree temp=T->lchild;
    T->lchild=InvertTree(T->rchild);
    T->rchild=InvertTree(temp);
    return T;
}

BiTree findfather(BiTree root, KeyType e){//19.找到父亲节点
    if(root==NULL)return NULL;
    if(root->data.key==e)return NULL;
    if((root->lchild!=NULL&&root->lchild->data.key==e)||(root->rchild!=NULL&&root->rchild->data.key==e))return root;
    BiTree p=findfather(root->lchild,e);
    if(p!=NULL)return p;
    return findfather(root->rchild,e);
}

int countsons(BiTree T, KeyType e){//20.统计子节点个数
    BiTree p=LocateNode(T,e);
    if(p==NULL)return -1;
    int count=0;
    if(p->lchild!=NULL)count++;
    if(p->rchild!=NULL)count++;
    return count;
}

int LocateList(LISTS &Lists,char ListName[]){//21.在集合中查找二叉树，返回下标
    for(int i=0;i<Lists.length;i++){
        if(strcmp(Lists.elem[i].name,ListName)==0)return i;//找到表名，返回下标
    }
    return -1;//未找到表名，返回-1
}

void searchmostBST(BiTree T){//22.二叉搜索树中的众数
    if(T==NULL)return;
    map<int,int> freq;
    queue<BiTree> q;
    q.push(T);
    while(!q.empty()){
        BiTree p=q.front();
        q.pop();
        freq[p->data.key]++;
        if(p->lchild)q.push(p->lchild);
        if(p->rchild)q.push(p->rchild);
    }
    int maxfreq=0;
    // C++98使用迭代器遍历map，不能用auto和范围for
    map<int,int>::iterator it;
    for(it=freq.begin(); it!=freq.end(); ++it){
        if(it->second>maxfreq)maxfreq=it->second;
    }
    printf("二叉搜索树中众数的出现次数为%d，众数有：", maxfreq);
    for(it=freq.begin(); it!=freq.end(); ++it){
        if(it->second==maxfreq)printf("%d ", it->first);
    }
    printf("\n");
}

void drawTree(BiTree T) {//23.绘制二叉树结构
    if(T == NULL) {
        RED;
        printf("当前二叉树为空，无法绘制！\n");
        WHITE;
        return;
    }

    int depth = BiTreeDepth(T);
    if(depth > 8) {
        YELLOW;
        printf("警告：二叉树深度为%d，超过控制台默认宽度，可能会出现错位！\n", depth);
        WHITE;
    }

    const int NODE_WIDTH = 3; // 每个节点固定占3个字符宽度（适配1-3位整数）
    queue<BiTree> q;
    q.push(T);

    for(int level=1; level<=depth; level++) {
        int levelSize = 1 << (level - 1); // 当前层的节点总数（包括空节点）
        int startPos = ((1 << (depth - level)) - 1) * NODE_WIDTH; // 第一个节点的起始位置
        int spacing = (1 << (depth - level)) * NODE_WIDTH; // 节点之间的间距

        vector<BiTree> currentLevel;
        // 取出当前层所有节点（包括空节点）
        for(int i=0; i<levelSize; i++) {
            BiTree p = q.front();
            q.pop();
            currentLevel.push_back(p);
        }

        // -------------------------- 打印节点行 --------------------------
        YELLOW; // 节点用黄色显示
        int currentCol = 0;
        for(int i=0; i<levelSize; i++) {
            BiTree p = currentLevel[i];
            int targetPos = startPos + i * spacing;
            
            // 打印前置空格，对齐到目标位置
            printSpaces(targetPos - currentCol);
            
            if(p != NULL) {
                printf("%3d", p->data.key); // 右对齐，占3个字符
            } else {
                printSpaces(NODE_WIDTH); // 空节点打印空格占位
            }
            
            currentCol = targetPos + NODE_WIDTH;
        }
        printf("\n");
        WHITE;

        // 最后一层不需要打印连接线
        if(level == depth) break;

        // -------------------------- 打印连接线行 --------------------------
        BLUE; // 连接线用蓝色显示
        currentCol = 0;
        for(int i=0; i<levelSize; i++) {
            BiTree p = currentLevel[i];
            if(p == NULL) continue;

            // 计算父节点中心位置和连接线位置
            int parentCenter = startPos + i * spacing + NODE_WIDTH / 2;
            int leftLinePos = parentCenter - spacing / 4;
            int rightLinePos = parentCenter + spacing / 4;

            // 打印左连接线 '/'
            printSpaces(leftLinePos - currentCol);
            printf(p->lchild != NULL ? "/" : " ");
            currentCol = leftLinePos + 1;

            // 打印右连接线 '\'
            printSpaces(rightLinePos - currentCol);
            printf(p->rchild != NULL ? "\\" : " ");
            currentCol = rightLinePos + 1;
        }
        printf("\n");
        WHITE;

        // 入队下一层节点（空节点也入队，保证结构对齐）
        for(int i=0; i<levelSize; i++) {
            BiTree p = currentLevel[i];
            if(p != NULL) {
                q.push(p->lchild);
                q.push(p->rchild);
            } else {
                q.push(NULL);
                q.push(NULL);
            }
        }
    }

    WHITE; // 恢复默认白色
}

// 哈夫曼树节点结构
typedef struct HuffmanNode {
    char ch;            // 字符
    int weight;         // 权重（出现次数）
    struct HuffmanNode *lchild, *rchild; // 左右子树
} HuffmanNode, *HuffmanTree;

// 哈夫曼编码表项
typedef struct {
    char ch;
    char code[256];     // 编码（最长不超过256位）
} HuffmanCode;

// 比较函数：用于优先队列排序（权重小的在前）
int compareHuffmanNode(const void *a, const void *b) {
    HuffmanNode *nodeA = *(HuffmanNode**)a;
    HuffmanNode *nodeB = *(HuffmanNode**)b;
    return nodeA->weight - nodeB->weight;
}

// 创建哈夫曼树
HuffmanTree createHuffmanTree(char str[]) {
    if (!str || !str[0]) return NULL;

    // 1. 统计字符频率
    int freq[256] = {0};
    int charCount = 0;
    for (int i = 0; str[i]; i++) {
        if (freq[(unsigned char)str[i]] == 0) charCount++;
        freq[(unsigned char)str[i]]++;
    }

    if (charCount == 0) return NULL;

    // 2. 创建初始节点数组
    HuffmanNode **nodes = (HuffmanNode**)malloc(charCount * sizeof(HuffmanNode*));
    int idx = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            nodes[idx] = (HuffmanNode*)malloc(sizeof(HuffmanNode));
            nodes[idx]->ch = (char)i;
            nodes[idx]->weight = freq[i];
            nodes[idx]->lchild = nodes[idx]->rchild = NULL;
            idx++;
        }
    }

    // 3. 构建哈夫曼树
    int n = charCount;
    while (n > 1) {
        // 排序：权重从小到大
        qsort(nodes, n, sizeof(HuffmanNode*), compareHuffmanNode);

        // 取两个权重最小的节点
        HuffmanNode *left = nodes[0];
        HuffmanNode *right = nodes[1];

        // 创建新的父节点
        HuffmanNode *parent = (HuffmanNode*)malloc(sizeof(HuffmanNode));
        parent->ch = '\0'; // 非叶子节点不存储字符
        parent->weight = left->weight + right->weight;
        parent->lchild = left;
        parent->rchild = right;

        // 替换数组中的节点
        nodes[0] = parent;
        for (int i = 1; i < n-1; i++) {
            nodes[i] = nodes[i+1];
        }
        n--;
    }

    HuffmanTree root = nodes[0];
    free(nodes);
    return root;
}

// 递归生成哈夫曼编码
void generateHuffmanCode(HuffmanTree root, char code[], int depth, HuffmanCode codeTable[], int *tableIdx) {
    if (root == NULL) return;

    // 叶子节点：保存编码
    if (root->lchild == NULL && root->rchild == NULL) {
        code[depth] = '\0';
        codeTable[*tableIdx].ch = root->ch;
        strcpy(codeTable[*tableIdx].code, code);
        (*tableIdx)++;
        return;
    }

    // 左分支：0
    code[depth] = '0';
    generateHuffmanCode(root->lchild, code, depth+1, codeTable, tableIdx);

    // 右分支：1
    code[depth] = '1';
    generateHuffmanCode(root->rchild, code, depth+1, codeTable, tableIdx);
}

// 销毁哈夫曼树
void destroyHuffmanTree(HuffmanTree root) {
    if (root == NULL) return;
    destroyHuffmanTree(root->lchild);
    destroyHuffmanTree(root->rchild);
    free(root);
}

// 哈夫曼编码主函数
void huffmanEncode01(const char str[]) {
    if (!str || !str[0]) {
        RED;
        printf("错误：输入字符串为空\n");
        WHITE;
        return;
    }

    WHITE;
    printf("原始字符串：%s\n", str);
    printf("原始长度：%d 字符，共 %d 位（ASCII编码）\n\n", (int)strlen(str), (int)strlen(str)*8);

    // 1. 创建哈夫曼树
    HuffmanTree root = createHuffmanTree((char*)str);
    if (root == NULL) {
        RED;
        printf("哈夫曼树创建失败！\n");
        WHITE;
        return;
    }

    // 2. 生成编码表
    HuffmanCode codeTable[256];
    char code[256];
    int tableIdx = 0;
    generateHuffmanCode(root, code, 0, codeTable, &tableIdx);

    // 3. 输出编码表
    YELLOW;
    printf("字符\t出现次数\t哈夫曼编码\n");
    printf("----------------------------------------\n");
    WHITE;
    int totalBits = 0;
    for (int i = 0; i < tableIdx; i++) {
        char ch = codeTable[i].ch;
        int count = 0;
        for (int j = 0; str[j]; j++) {
            if (str[j] == ch) count++;
        }
        int bits = count * (int)strlen(codeTable[i].code);
        totalBits += bits;

        if (ch == ' ') {
            printf("空格\t%d\t\t%s\n", count, codeTable[i].code);
        } else if (ch == '\n') {
            printf("换行\t%d\t\t%s\n", count, codeTable[i].code);
        } else {
            printf("%c\t%d\t\t%s\n", ch, count, codeTable[i].code);
        }
    }

    // 4. 生成总编码结果
    char totalCode[4096] = {0};
    for (int i = 0; str[i]; i++) {
        for (int j = 0; j < tableIdx; j++) {
            if (codeTable[j].ch == str[i]) {
                strcat(totalCode, codeTable[j].code);
                break;
            }
        }
    }

    // 5. 输出统计信息
    printf("----------------------------------------\n");
    GREEN;
    printf("总编码结果：%s\n", totalCode);
    printf("哈夫曼编码总长度：%d 位\n", totalBits);
    printf("压缩率：%.2f%%\n", (1 - (double)totalBits / (strlen(str)*8)) * 100);
    WHITE;

    // 6. 销毁哈夫曼树
    destroyHuffmanTree(root);
}

void showLists(LISTS Lists) {
    if (Lists.length == 0) {
        YELLOW;
        printf("当前二叉树集合为空！\n");
        WHITE;
        return;
    }
    GREEN;
    printf("当前共有 %d 个二叉树：\n", Lists.length);
    for (int i = 0; i < Lists.length; i++) {
        printf("  %d. %s\n", i+1, Lists.elem[i].name);
    }
    WHITE;
}