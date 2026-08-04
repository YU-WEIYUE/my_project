/*----------头文件的引入---------*/
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include <time.h>
#include <climits>
using namespace std;

/*---------- 预定义宏与常量 ----------*/
#undef OVERFLOW
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20

typedef int status;
typedef int KeyType; 

/*---------- 数据结构定义 ----------*/
typedef enum {DG,DN,UDG,UDN} GraphKind;

typedef struct {
    KeyType  key;
    char others[20];
} VertexType; //顶点类型定义

typedef struct ArcNode {         //表结点类型定义
    int adjvex;              //顶点位置编号 
    struct ArcNode  *nextarc;	   //下一个表结点指针
} ArcNode;

typedef struct VNode{				//头结点及其数组类型定义
    VertexType data;       	//顶点信息
    ArcNode *firstarc;      	 //指向第一条弧
} VNode,AdjList[MAX_VERTEX_NUM];

typedef  struct {  //邻接表的类型定义
    AdjList vertices;     	 //头结点数组
    int vexnum,arcnum;   	  //顶点数、弧数
    GraphKind  kind;        //图的类型
} ALGraph;

// -------------------------- 多图集合管理 --------------------------
typedef struct {
    struct {
        char name[30]; // 图的名称
        ALGraph G;     // 图结构
    } elem[10];       // 最多存储10个图
    int length;       // 图的个数
} LISTS;

LISTS Lists = {0};   // 全局图集合

/*---------- 全局变量 ----------*/
int visited[MAX_VERTEX_NUM];

/*---------- 控制台颜色控制宏 ----------*/
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
#define GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

/*---------- 所有函数声明 ----------*/
void visit(VertexType v);
status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
status ClearGraph(ALGraph &G);
status GraphEmpty(ALGraph G);
int LocateVex(ALGraph G,KeyType u);
status PutVex(ALGraph &G,KeyType u,VertexType value);
int FirstAdjVex(ALGraph G,int u); // ✅ 修正：参数为顶点位序
int NextAdjVex(ALGraph G,int v,int w); // ✅ 修正：参数为顶点位序
status InsertVex(ALGraph &G,VertexType v);
status DeleteVex(ALGraph &G,KeyType v);
status InsertArc(ALGraph &G,KeyType v,KeyType w);
status DeleteArc(ALGraph &G,KeyType v,KeyType w);
void DFS(ALGraph &G, int v, void (*visit)(VertexType));
status DFSTraverse(ALGraph &G, void (*visit)(VertexType));
status BFSTraverse(ALGraph &G, void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
void PrintGraph(ALGraph G);
int GetDegree(ALGraph G, KeyType v);
void ShowConnectComponents(ALGraph G);
vector<int> BFSShortestPath(ALGraph G, KeyType start);
vector<int> VerticesSetLessThanK(ALGraph G, KeyType v, int k);
int ShortestPathLength(ALGraph G, KeyType v, KeyType w);
void clearInputBuffer();

void show();
void showplus();
void showLists(LISTS Lists);
int LocateList(LISTS &Lists, char ListName[]);

// -------------------------- 主函数 --------------------------
int main() {
    srand((unsigned)time(NULL));
    int choice = 1;
    int currentIndex = -1; // 当前选中的图下标，-1表示未选中
    Lists.length = 0;      // 初始化图集合为空

    VertexType V[MAX_VERTEX_NUM], v;
    KeyType VR[MAX_VERTEX_NUM][2];
    KeyType v1, v2;
    char fileName[50], graphName[30];

    while (choice) {
        system("cls"); // 清屏
        show();        // 显示主菜单

        // 高亮显示当前选中的图
        if(currentIndex != -1) {
            YELLOW;
            printf("\n");
            printf("╔═══════════════════════════════════════════════════════════╗\n");
            printf("                    当前选中图：%s                          \n", Lists.elem[currentIndex].name);
            printf("╚═══════════════════════════════════════════════════════════╝\n");
        }

        GREEN;
        printf("\n请输入您的选择：");
        YELLOW;
        scanf("%d",&choice);
        clearInputBuffer();

        switch(choice) {
            // ========== 系统操作 ==========
            case 0:
                GREEN;
                printf("感谢使用图管理系统！再见！\n");
                // 释放所有图的内存
                for (int i = 0; i < Lists.length; i++) {
                    ClearGraph(Lists.elem[i].G);
                }
                printf("输入任意键退出...");
                _getch();
                return 0;

            // ========== 多图集合管理 ==========
            case 1:{//查看当前图集合中有哪些图
                showLists(Lists);
                break;}

            case 2:{//创建新图
                if (Lists.length >= 10) {
                    RED;
                    printf("错误：图集合已满（最多10个）！\n");
                    WHITE;
                    break;
                }
                GREEN;
                printf("请输入要创建的图名称：");
                YELLOW;
                scanf("%29s", graphName);
                clearInputBuffer();
                GREEN;
                printf("请输入顶点（格式：key others，输入-1结束）：\n");
                printf("示例：5 线性表 8 集合 7 二叉树 6 无向图 -1\n");
                int i = 0;
                while (1) {
                    YELLOW;
                    scanf("%d", &V[i].key);
                    if (V[i].key == -1) break;
                    scanf("%19s", V[i].others);
                    i++;
                    if (i >= MAX_VERTEX_NUM) {
                        RED;
                        printf("错误：顶点数量超过上限（%d个）！\n", MAX_VERTEX_NUM);
                        WHITE;
                        break;
                    }
                }
                clearInputBuffer();
                GREEN;
                printf("请输入边（格式：v1 v2，输入-1 -1结束）：\n");
                printf("示例：5 6 5 7 6 7 7 8 -1 -1\n");
                i = 0;
                while (1) {
                    YELLOW;
                    scanf("%d %d", &VR[i][0], &VR[i][1]);
                    if (VR[i][0] == -1 && VR[i][1] == -1) break;
                    i++;
                    if (i >= MAX_VERTEX_NUM * MAX_VERTEX_NUM) {
                        RED;
                        printf("错误：边数量超过上限！\n");
                        WHITE;
                        break;
                    }
                }
                clearInputBuffer();

                // 初始化新图
                ALGraph newG;
                newG.vexnum = 0;
                newG.arcnum = 0;
                newG.kind = UDG;
                for (int j = 0; j < MAX_VERTEX_NUM; j++) {
                    newG.vertices[j].firstarc = NULL;
                }

                status res = CreateGraph(newG, V, VR);
                if (res == OK) {
                    strcpy(Lists.elem[Lists.length].name, graphName);
                    Lists.elem[Lists.length].G = newG;
                    Lists.length++;
                    WHITE;printf("图【%s】创建成功！\n", graphName);
                    currentIndex = Lists.length - 1; // 自动选中新图
                }
                else{RED;printf("图【%s】创建失败！错误码：%d\n", graphName, res);}
                break;
            }

            case 3:{//选中一个图进行操作
                char treeName[30];
                GREEN;
                printf("请输入要选中的图名称：");
                YELLOW;
                scanf("%29s", treeName);
                clearInputBuffer();
                
                currentIndex = LocateList(Lists, treeName);
                
                if(currentIndex != -1){
                    WHITE;printf("图【%s】选中成功！现在可以对其进行操作了！\n", Lists.elem[currentIndex].name);
                }
                else{RED;printf("图【%s】不存在！\n", treeName);}
                break;
            }

            // ========== 图基本操作 ==========
            case 4://销毁当前选中的图
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个图！\n");break;}
                if(DestroyGraph(Lists.elem[currentIndex].G)==OK){
                    // 从集合中移除
                    for(int i=currentIndex; i<Lists.length-1; i++){
                        Lists.elem[i] = Lists.elem[i+1];
                    }
                    Lists.length--;
                    WHITE;printf("图【%s】销毁成功！\n", Lists.elem[currentIndex].name);
                    currentIndex = -1; // 销毁后置为未选中
                }
                else{RED;printf("图不存在，销毁失败！\n");}
                break;
            
            case 5:{//清空当前选中的图
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个图！\n");break;}
                if(ClearGraph(Lists.elem[currentIndex].G)==OK){WHITE;printf("图【%s】清空成功！\n", Lists.elem[currentIndex].name);}
                else{RED;printf("图不存在，无法清空！\n");}
                break;
            }

            case 6:{//判断当前选中的图是否为空
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个图！\n");break;}
                if(GraphEmpty(Lists.elem[currentIndex].G)){RED;printf("图【%s】为空！\n", Lists.elem[currentIndex].name);}
                else {WHITE;printf("图【%s】不为空！\n", Lists.elem[currentIndex].name);}
                break;
            }

            case 7:{//求当前选中的图的顶点数
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个图！\n");break;}
                WHITE;printf("图【%s】顶点数为：%d\n", Lists.elem[currentIndex].name, Lists.elem[currentIndex].G.vexnum);
                break;
            }

            case 8:{//求当前选中的图的边数
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个图！\n");break;}
                WHITE;printf("图【%s】边数为：%d\n", Lists.elem[currentIndex].name, Lists.elem[currentIndex].G.arcnum);
                break;
            }

            // ✅ 新增：基本功能区第9项 - 获得第一邻接点
            case 9:{
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个图！\n");break;}
                KeyType uKey;
                GREEN;
                printf("请输入顶点key：");
                YELLOW;
                scanf("%d", &uKey);
                clearInputBuffer();
                
                int uPos = LocateVex(Lists.elem[currentIndex].G, uKey);
                if(uPos == -1) {
                    RED;printf("错误：顶点%d不存在！\n", uKey);
                    break;
                }
                
                int adjPos = FirstAdjVex(Lists.elem[currentIndex].G, uPos);
                if(adjPos == -1) {
                    YELLOW;printf("顶点%d没有邻接顶点！\n", uKey);
                } else {
                    WHITE;printf("顶点%d的第一个邻接顶点是：%d %s\n", 
                           uKey, 
                           Lists.elem[currentIndex].G.vertices[adjPos].data.key,
                           Lists.elem[currentIndex].G.vertices[adjPos].data.others);
                }
                break;
            }

            // ✅ 新增：基本功能区第10项 - 获得下一邻接点
            case 10:{
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个图！\n");break;}
                KeyType vKey, wKey;
                GREEN;
                printf("请输入顶点v的key：");
                YELLOW;
                scanf("%d", &vKey);
                clearInputBuffer();
                GREEN;
                printf("请输入邻接顶点w的key：");
                YELLOW;
                scanf("%d", &wKey);
                clearInputBuffer();
                
                int vPos = LocateVex(Lists.elem[currentIndex].G, vKey);
                int wPos = LocateVex(Lists.elem[currentIndex].G, wKey);
                
                if(vPos == -1 || wPos == -1) {
                    RED;printf("错误：顶点不存在！\n");
                    break;
                }
                
                int nextPos = NextAdjVex(Lists.elem[currentIndex].G, vPos, wPos);
                if(nextPos == -1) {
                    YELLOW;printf("顶点%d是顶点%d的最后一个邻接顶点！\n", wKey, vKey);
                } else {
                    WHITE;printf("顶点%d相对于%d的下一个邻接顶点是：%d %s\n", 
                           vKey, wKey,
                           Lists.elem[currentIndex].G.vertices[nextPos].data.key,
                           Lists.elem[currentIndex].G.vertices[nextPos].data.others);
                }
                break;
            }

            // ========== 顶点操作（序号自动顺延） ==========
            case 11:{//插入顶点
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个图！\n");break;}
                printf("请输入新顶点（key others）：");
                scanf("%d %19s", &v.key, &v.others);
                clearInputBuffer();
                if (InsertVex(Lists.elem[currentIndex].G, v) == OK) {
                    WHITE;printf("顶点插入成功！\n");
                } else {
                    RED;printf("顶点插入失败（重复key/顶点数达上限）！\n");
                }
                break;
            }

            case 12:{//删除顶点
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个图！\n");break;}
                printf("请输入要删除的顶点key：");
                scanf("%d", &v1);
                clearInputBuffer();
                if (DeleteVex(Lists.elem[currentIndex].G, v1) == OK) {
                    WHITE;printf("顶点删除成功！\n");
                } else {
                    RED;printf("顶点删除失败（不存在/删除最后一个顶点）！\n");
                }
                break;
            }

            case 13:{//修改顶点信息
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个图！\n");break;}
                GREEN;
                printf("请输入原顶点key：");
                YELLOW;
                scanf("%d", &v1);
                clearInputBuffer();
                GREEN;
                printf("请输入新顶点信息（key others）：");
                YELLOW;
                scanf("%d %19s", &v.key, &v.others);
                clearInputBuffer();
                if (PutVex(Lists.elem[currentIndex].G, v1, v) == OK) {
                    WHITE;printf("顶点信息修改成功！\n");
                } else {
                    RED;printf("顶点修改失败（原顶点不存在/新key重复）！\n");
                }
                break;
            }

            // ========== 边操作（序号自动顺延） ==========
            case 14:{//插入边
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个图！\n");break;}
                GREEN;
                printf("请输入要插入的边（v1 v2）：");
                YELLOW;
                scanf("%d %d", &v1, &v2);
                clearInputBuffer();
                if (InsertArc(Lists.elem[currentIndex].G, v1, v2) == OK) {
                    WHITE;printf("边插入成功！\n");
                } else {
                    RED;printf("边插入失败（顶点不存在/重复边/自环）！\n");
                }
                break;
            }

            case 15:{//删除边
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个图！\n");break;}
                GREEN;
                printf("请输入要删除的边（v1 v2）：");
                YELLOW;
                scanf("%d %d", &v1, &v2);
                clearInputBuffer();
                if (DeleteArc(Lists.elem[currentIndex].G, v1, v2) == OK) {
                    WHITE;printf("边删除成功！\n");
                } else {
                    RED;printf("边删除失败（顶点不存在/边不存在/自环）！\n");
                }
                break;
            }

            // ========== 遍历操作（序号自动顺延） ==========
            case 16:{//深度优先遍历
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个图！\n");break;}
                WHITE;printf("深度优先遍历结果：");
                if (DFSTraverse(Lists.elem[currentIndex].G, visit) == OK) {
                    printf("\n");
                } else {
                    RED;printf("遍历失败（图为空）！\n");
                }
                break;
            }

            case 17:{//广度优先遍历
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个图！\n");break;}
                WHITE;printf("广度优先遍历结果：");
                if (BFSTraverse(Lists.elem[currentIndex].G, visit) == OK) {
                    printf("\n");
                } else {
                    RED;printf("遍历失败（图为空）！\n");
                }
                break;
            }

            // ========== 文件操作（序号自动顺延） ==========
            case 18:{//保存图到文件
                if(currentIndex == -1){RED;printf("请先使用功能键 3 选中一个图！\n");break;}
                GREEN;
                printf("请输入保存文件名：");
                YELLOW;
                scanf("%49s", fileName);
                clearInputBuffer();
                if (SaveGraph(Lists.elem[currentIndex].G, fileName) == OK) {
                    WHITE;printf("图【%s】已保存到文件【%s】！\n", Lists.elem[currentIndex].name, fileName);
                } else {
                    RED;printf("文件保存失败！\n");
                }
                break;
            }

            case 19:{//从文件加载图
                if (Lists.length >= 10) {
                    RED;printf("图集合已满！\n");break;
                }
                GREEN;
                printf("请输入加载的文件名：");
                YELLOW;
                scanf("%49s", fileName);
                clearInputBuffer();
                GREEN;
                printf("请给加载的图命名：");
                YELLOW;
                scanf("%29s", graphName);
                clearInputBuffer();

                ALGraph newG;
                ClearGraph(newG);
                if(LoadGraph(newG, fileName) == OK){
                    strcpy(Lists.elem[Lists.length].name, graphName);
                    Lists.elem[Lists.length].G = newG;
                    Lists.length++;
                    currentIndex = Lists.length - 1;
                    WHITE;printf("加载成功！已自动选中！\n");
                }else{
                    RED;printf("加载失败！文件不存在或格式错误！\n");
                }
                break;
            }

            // ========== 附加功能（序号自动顺延） ==========
            case 20:{//附加功能菜单
                int plusLoop = 1;
                while(plusLoop) {
                    system("cls");
                    showplus();
                    if(currentIndex != -1) {
                        YELLOW;
                        printf("\n 当前主菜单选中图：%s\n", Lists.elem[currentIndex].name);
                    }

                    GREEN;
                    printf("\n请输入您的选择：");
                    int pluschoice;
                    YELLOW;
                    scanf("%d", &pluschoice);
                    clearInputBuffer();

                    switch(pluschoice) {
                        case 0: // 返回主菜单
                        plusLoop = 0;
                        break;

                        case 1: { // 打印邻接表
                            if(currentIndex == -1){RED;printf(" 请先在主菜单选中一个图！\n");break;}
                            PrintGraph(Lists.elem[currentIndex].G);
                            break;
                        }

                        case 2: { // 求顶点的度
                            if(currentIndex == -1){RED;printf(" 请先在主菜单选中一个图！\n");break;}
                            GREEN;
                            printf("请输入顶点key：");
                            YELLOW;
                            scanf("%d", &v1);
                            clearInputBuffer();
                            int degree = GetDegree(Lists.elem[currentIndex].G, v1);
                            if(degree == -1){
                                RED;printf("顶点不存在！\n");
                            }else{
                                WHITE;printf("顶点%d的度为：%d\n", v1, degree);
                            }
                            break;
                        }

                        case 3: { // 显示连通分量
                            if(currentIndex == -1){RED;printf(" 请先在主菜单选中一个图！\n");break;}
                            ShowConnectComponents(Lists.elem[currentIndex].G);
                            break;
                        }

                        case 4: { // 距离小于k的顶点集合
                            if(currentIndex == -1){RED;printf(" 请先在主菜单选中一个图！\n");break;}
                            KeyType v;
                            int k;
                            GREEN;
                            printf("请输入顶点key：");YELLOW;
                            scanf("%d", &v);
                            clearInputBuffer();GREEN;
                            printf("请输入距离k：");YELLOW;
                            scanf("%d", &k);
                            clearInputBuffer();
                            
                            vector<int> result = VerticesSetLessThanK(Lists.elem[currentIndex].G, v, k);
                            if(result.empty()) {
                                YELLOW;printf("没有找到距离小于%d的顶点！\n", k);
                            } else {
                                WHITE;printf("与顶点%d距离小于%d的顶点有：", v, k);
                                for(int i=0; i<result.size(); i++) {
                                    printf("%d ", result[i]);
                                }
                                printf("\n");
                            }
                            break;
                        }

                        case 5: { // 顶点间最短路径长度
                            if(currentIndex == -1){RED;printf(" 请先在主菜单选中一个图！\n");break;}
                            KeyType v, w;GREEN;
                            printf("请输入起点顶点key：");YELLOW;
                            scanf("%d", &v);
                            clearInputBuffer();GREEN;
                            printf("请输入终点顶点key：");YELLOW;
                            scanf("%d", &w);
                            clearInputBuffer();
                            
                            int length = ShortestPathLength(Lists.elem[currentIndex].G, v, w);
                            if(length == -2) {
                                RED;printf("错误：起点或终点顶点不存在！\n");
                            } else if(length == -1) {
                                RED;printf("顶点%d到顶点%d不可达！\n", v, w);
                            } else {
                                WHITE;printf("顶点%d到顶点%d的最短路径长度为：%d\n", v, w, length);
                            }
                            break;
                        }

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

// -------------------------- 清空输入缓冲区函数 --------------------------
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// -------------------------- 菜单函数 --------------------------
void show(){
    BLUE;
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("                                        欢迎使用图管理系统                                              \n");       
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n\n");
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━  多图集合管理 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("1. 查看当前图集合中有哪些图\n");
    printf("2. 创建新图\n");
    printf("3. 选中一个图进行操作\n");
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━  图基本操作 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("4. 销毁当前选中的图\n");
    printf("5. 清空当前选中的图\n");
    printf("6. 判断当前选中的图是否为空\n");
    printf("7. 求当前选中的图的顶点数\n");
    printf("8. 求当前选中的图的边数\n");
    printf("9. 获得第一邻接点\n"); // ✅ 新增
    printf("10. 获得下一邻接点\n"); // ✅ 新增
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━  顶点操作 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("11. 插入顶点\n");
    printf("12. 删除顶点\n");
    printf("13. 修改顶点信息\n");
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━  边操作 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("14. 插入边\n");
    printf("15. 删除边\n");
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━  遍历操作 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("16. 深度优先遍历\n");
    printf("17. 广度优先遍历\n");
    BLUE;
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━  文件操作 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    GREEN;
    printf("18. 保存图到文件\n");
    printf("19. 从文件加载图\n");
    printf("20. 附加功能\n");
    GREEN;
    printf("0. 退出系统\n");
}

void showplus(){
    BLUE;   
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("                                        欢迎使用附加功能菜单                                              \n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("                                                                              Powered by: CS2503班——U202514774\n\n");
    GREEN;
    printf("1. 打印邻接表\n");
    printf("2. 求顶点的度\n");
    printf("3. 显示连通分量\n");
    printf("4. 距离小于k的顶点集合\n");
    printf("5. 顶点间最短路径长度\n");
    printf("0. 返回主菜单\n");
}

// -------------------------- 多图集合管理函数 --------------------------
void showLists(LISTS Lists) {
    if (Lists.length == 0) {
        YELLOW;
        printf("当前图集合为空！\n");
        WHITE;
        return;
    }
    GREEN;
    printf("当前共有 %d 个图：\n", Lists.length);
    for (int i = 0; i < Lists.length; i++) {
        printf("  %d. %s\n", i+1, Lists.elem[i].name);
    }
    WHITE;
}

int LocateList(LISTS &Lists, char ListName[]){
    for(int i=0;i<Lists.length;i++){
        if(strcmp(Lists.elem[i].name, ListName)==0)return i;
    }
    return -1;
}

// -------------------------- 核心功能函数实现 --------------------------
void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2])
{
    G.kind=UDG;
    G.vexnum=0;
    G.arcnum=0;
    int i=0;
    
    // 处理顶点
    while(1){
        if(V[i].key==-1) break;
        if(G.vexnum >= MAX_VERTEX_NUM) return ERROR;
        
        // 检查顶点重复
        for(int j=0;j<G.vexnum;j++){
            if(G.vertices[j].data.key == V[i].key)
                return ERROR;
        }
        
        G.vertices[G.vexnum].data = V[i];
        G.vertices[G.vexnum].firstarc = NULL;
        G.vexnum++;
        i++;
    }
    if(G.vexnum==0)return ERROR;
    // 处理边
    i=0;
    while(1){
        KeyType v1=VR[i][0];
        KeyType v2=VR[i][1];
        
        if(v1==-1 && v2==-1) break;
        
        // 自环边非法
        if(v1 == v2) return ERROR;
        
        // 查找顶点下标
        int p1=-1,p2=-1;
        for(int j=0;j<G.vexnum;j++){
            if(G.vertices[j].data.key == v1) p1=j;
            if(G.vertices[j].data.key == v2) p2=j;
        }
        
        // 顶点不存在
        if(p1==-1 || p2==-1) return ERROR;
        
        // 检查重复边
        ArcNode *temp = G.vertices[p1].firstarc;
        while(temp != NULL){
            if(temp->adjvex == p2){
                return ERROR;
            }
            temp = temp->nextarc;
        }
        
        // 创建边节点（头插法）
        ArcNode *s1 = (ArcNode*)malloc(sizeof(ArcNode));
        s1->adjvex = p2;
        s1->nextarc = G.vertices[p1].firstarc;
        G.vertices[p1].firstarc = s1;
        
        ArcNode *s2 = (ArcNode*)malloc(sizeof(ArcNode));
        s2->adjvex = p1;
        s2->nextarc = G.vertices[p2].firstarc;
        G.vertices[p2].firstarc = s2;
        
        G.arcnum++;
        i++;
    }
    
    return OK;
}

status DestroyGraph(ALGraph &G)
{
    ClearGraph(G);
    return OK;
}

status ClearGraph(ALGraph &G)
{
    ArcNode *p, *temp;
    
    // 遍历所有顶点，逐个释放每个顶点的邻接表
    for (int i = 0; i < G.vexnum; i++) {
        p = G.vertices[i].firstarc;
        while (p != NULL) {
            temp = p->nextarc;
            free(p);
            p = temp;
        }
        G.vertices[i].firstarc = NULL;
    }
    
    // 重置图的核心元数据
    G.vexnum = 0;
    G.arcnum = 0;
    G.kind = UDG;
    
    return OK;
}

status GraphEmpty(ALGraph G)
{
    return G.vexnum == 0 ? TRUE : FALSE;
}

int LocateVex(ALGraph G,KeyType u)
{
    for (int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key==u){
            return i;
        }
    }
    return -1;
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
{
    int pos = LocateVex(G, u);
    if (pos == -1) {
        return ERROR;
    }
    
    // 检查新关键字是否与其他顶点重复
    for (int i = 0; i < G.vexnum; i++) {
        if (i != pos && G.vertices[i].data.key == value.key) {
            return ERROR;
        }
    }
    
    G.vertices[pos].data = value;
    return OK;
}

// ✅ 严格符合规范：参数u是顶点位序，返回邻接顶点位序
int FirstAdjVex(ALGraph G,int u)
{
    if(u < 0 || u >= G.vexnum) return -1; // 位序越界
    if(G.vertices[u].firstarc == NULL) return -1;
    return G.vertices[u].firstarc->adjvex;
}

// ✅ 严格符合规范：参数v和w是顶点位序，返回下一个邻接顶点位序
int NextAdjVex(ALGraph G,int v,int w)
{
    if(v < 0 || v >= G.vexnum || w < 0 || w >= G.vexnum) return -1; // 位序越界
    ArcNode *p = G.vertices[v].firstarc;
    while(p != NULL){
        if(p->adjvex == w){
            if(p->nextarc != NULL){
                return p->nextarc->adjvex;
            }else{
                return -1;
            }
        }
        p = p->nextarc;
    }
    
    return -1; // w不是v的邻接顶点
}

status InsertVex(ALGraph &G,VertexType v)
{
    for(int i=0;i<G.vexnum;i++){
        if(v.key==G.vertices[i].data.key)return ERROR;
    }
    if(G.vexnum>=MAX_VERTEX_NUM)return ERROR;
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
}

status DeleteVex(ALGraph &G,KeyType v)
{
    int pos = LocateVex(G, v);
    if (pos == -1) return ERROR;

    ArcNode *p, *q;

    // 释放被删顶点自己的所有邻边
    p = G.vertices[pos].firstarc;
    while (p != NULL) {
        q = p->nextarc;
        free(p);
        p = q;
        G.arcnum--;
    }
    G.vertices[pos].firstarc = NULL;

    // 删除所有其他顶点中指向pos的边
    for (int i = 0; i < G.vexnum; i++) {
        if (i == pos) continue;
        
        // 处理头节点是pos的情况
        while (G.vertices[i].firstarc != NULL && G.vertices[i].firstarc->adjvex == pos) {
            q = G.vertices[i].firstarc;
            G.vertices[i].firstarc = q->nextarc;
            free(q);
        }
        
        // 处理链表中间和尾部是pos的情况
        p = G.vertices[i].firstarc;
        while (p != NULL && p->nextarc != NULL) {
            if (p->nextarc->adjvex == pos) {
                q = p->nextarc;
                p->nextarc = q->nextarc;
                free(q);
            } else {
                p = p->nextarc;
            }
        }
    }

    // 顶点数组前移覆盖
    for (int i = pos; i < G.vexnum - 1; i++) {
        G.vertices[i] = G.vertices[i + 1];
    }
    G.vexnum--;

    // 不允许空图，删除最后一个顶点视为失败
    if (G.vexnum == 0) {
        return ERROR;
    }

    // 更新所有边的下标
    for (int i = 0; i < G.vexnum; i++) {
        p = G.vertices[i].firstarc;
        while (p != NULL) {
            if (p->adjvex > pos) {
                p->adjvex--;
            }
            p = p->nextarc;
        }
    }

    return OK;
}

status InsertArc(ALGraph &G,KeyType v,KeyType w)
{
    int posv=LocateVex(G,v);
    int posw=LocateVex(G,w);
    if (posv == -1 || posw == -1 || posv == posw)return ERROR;
    ArcNode *p = G.vertices[posv].firstarc;
    while (p != NULL) {
        if (p->adjvex == posw)
            return ERROR; // 边已存在
        p = p->nextarc;
    }
    ArcNode *s1 = (ArcNode*)malloc(sizeof(ArcNode));
    s1->adjvex = posw;
    s1->nextarc = G.vertices[posv].firstarc;
    G.vertices[posv].firstarc = s1;
    ArcNode *s2 = (ArcNode*)malloc(sizeof(ArcNode));
    s2->adjvex = posv;
    s2->nextarc = G.vertices[posw].firstarc;
    G.vertices[posw].firstarc = s2;
    G.arcnum++;
    return OK;
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
{
    int posv=LocateVex(G,v);
    int posw=LocateVex(G,w);
    if(posv == -1 || posw == -1 || posv == posw) return ERROR;
    ArcNode *p, *q;
    int found = 0;

    // 删除 posv -> posw
    while(G.vertices[posv].firstarc != NULL && G.vertices[posv].firstarc->adjvex == posw){
        q = G.vertices[posv].firstarc;
        G.vertices[posv].firstarc = q->nextarc;
        free(q);
        found = 1;
    }
    p = G.vertices[posv].firstarc;
    while(p != NULL && p->nextarc != NULL){
        if(p->nextarc->adjvex == posw){
            q = p->nextarc;
            p->nextarc = q->nextarc;
            free(q);
            found = 1;
            break;
        }
        p = p->nextarc;
    }

    // 删除 posw -> posv (无向图必须双向删除)
    while(G.vertices[posw].firstarc != NULL && G.vertices[posw].firstarc->adjvex == posv){
        q = G.vertices[posw].firstarc;
        G.vertices[posw].firstarc = q->nextarc;
        free(q);
    }
    p = G.vertices[posw].firstarc;
    while(p != NULL && p->nextarc != NULL){
        if(p->nextarc->adjvex == posv){
            q = p->nextarc;
            p->nextarc = q->nextarc;
            free(q);
            break;
        }
        p = p->nextarc;
    }

    if(!found) return ERROR;
    
    G.arcnum--;
    return OK;
}

void DFS(ALGraph &G, int v, void (*visit)(VertexType)) {
    visit(G.vertices[v].data);
    visited[v] = 1;

    ArcNode *p = G.vertices[v].firstarc;
    while (p != NULL) {
        int w = p->adjvex;
        if (!visited[w]) {
            DFS(G, w, visit);
        }
        p = p->nextarc;
    }
}

status DFSTraverse(ALGraph &G, void (*visit)(VertexType))
{
    if(G.vexnum == 0) return ERROR;
    
    int i;
    for (i = 0; i < G.vexnum; i++) {
        visited[i] = 0;
    }
    for (i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            DFS(G, i, visit);
        }
    }
    return OK;
}

status BFSTraverse(ALGraph &G, void (*visit)(VertexType))
{
    if(G.vexnum == 0) return ERROR;
    
    int i, j;
    int queue[MAX_VERTEX_NUM], front = 0, rear = 0;

    for (i = 0; i < G.vexnum; i++)
        visited[i] = 0;

    for (i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            visited[i] = 1;
            visit(G.vertices[i].data);
            queue[rear++] = i;

            while (front != rear) {
                j = queue[front++];
                ArcNode *p = G.vertices[j].firstarc;

                while (p != NULL) {
                    int k = p->adjvex;
                    if (!visited[k]) {
                        visited[k] = 1;
                        visit(G.vertices[k].data);
                        queue[rear++] = k;
                    }
                    p = p->nextarc;
                }
            }
        }
    }

    return OK;
}

status SaveGraph(ALGraph G, char FileName[])
{
    FILE *fp = fopen(FileName, "w");
    if(fp == NULL) return ERROR;

    fprintf(fp, "%d\n", G.vexnum);

    for(int i=0; i<G.vexnum; i++){
        fprintf(fp, "%d %s\n", G.vertices[i].data.key, G.vertices[i].data.others);
    }

    for(int i=0; i<G.vexnum; i++){
        ArcNode *p = G.vertices[i].firstarc;
        int cnt = 0;
        ArcNode *tmp = p;
        while(tmp != NULL){
            cnt++;
            tmp = tmp->nextarc;
        }
        fprintf(fp, "%d", cnt);
        while(p != NULL){
            fprintf(fp, " %d", G.vertices[p->adjvex].data.key);
            p = p->nextarc;
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return OK;
}

status LoadGraph(ALGraph &G, char FileName[])
{
    FILE *fp = fopen(FileName, "r");
    if(fp == NULL) return ERROR;

    G.kind = UDG;
    G.arcnum = 0;

    fscanf(fp, "%d", &G.vexnum);

    for(int i=0; i<G.vexnum; i++){
        fscanf(fp, "%d %s", &G.vertices[i].data.key, G.vertices[i].data.others);
        G.vertices[i].firstarc = NULL;
    }

    for(int i=0; i<G.vexnum; i++){
        int cnt;
        fscanf(fp, "%d", &cnt);
        for(int j=0; j<cnt; j++){
            int key;
            fscanf(fp, "%d", &key);
            int pos = -1;
            for(int k=0; k<G.vexnum; k++){
                if(G.vertices[k].data.key == key){
                    pos = k;
                    break;
                }
            }
            if(pos == -1) continue;

            ArcNode *s = (ArcNode*)malloc(sizeof(ArcNode));
            s->adjvex = pos;
            s->nextarc = NULL;

            if(G.vertices[i].firstarc == NULL){
                G.vertices[i].firstarc = s;
            }else{
                ArcNode *r = G.vertices[i].firstarc;
                while(r->nextarc != NULL) r = r->nextarc;
                r->nextarc = s;
            }
            G.arcnum++;
        }
    }

    G.arcnum /= 2;

    fclose(fp);
    return OK;
}

void PrintGraph(ALGraph G) {
    YELLOW;
    printf("\n===== 图的邻接表 =====\n");
    WHITE;
    for (int i = 0; i < G.vexnum; i++) {
        printf("顶点 %d(%s): ", G.vertices[i].data.key, G.vertices[i].data.others);
        ArcNode *p = G.vertices[i].firstarc;
        while (p != NULL) {
            printf("%d -> ", G.vertices[p->adjvex].data.key);
            p = p->nextarc;
        }
        printf("NULL\n");
    }
    printf("顶点数：%d，边数：%d\n", G.vexnum, G.arcnum);
}

// -------------------------- 附加功能函数 --------------------------
int GetDegree(ALGraph G, KeyType v) {
    int pos = LocateVex(G, v);
    if(pos == -1) return -1;
    
    int degree = 0;
    ArcNode *p = G.vertices[pos].firstarc;
    while(p != NULL) {
        degree++;
        p = p->nextarc;
    }
    return degree;
}

void ShowConnectComponents(ALGraph G) {
    if(G.vexnum == 0) {
        RED;printf("图为空！\n");
        return;
    }
    
    int i, componentCount = 0;
    for (i = 0; i < G.vexnum; i++) {
        visited[i] = 0;
    }
    
    YELLOW;
    printf("\n===== 连通分量 =====\n");
    WHITE;
    for (i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            componentCount++;
            printf("连通分量%d：", componentCount);
            DFS(G, i, visit);
            printf("\n");
        }
    }
    printf("总共有%d个连通分量\n", componentCount);
}

// 辅助函数：BFS求单源最短路径
vector<int> BFSShortestPath(ALGraph G, KeyType start) {
    int startPos = LocateVex(G, start);
    vector<int> dist(G.vexnum, -1); // -1表示不可达
    
    if(startPos == -1) {
        return dist;
    }

    int queue[MAX_VERTEX_NUM];
    int front = 0, rear = 0;
    
    dist[startPos] = 0;
    queue[rear++] = startPos;

    while(front != rear) {
        int u = queue[front++];
        ArcNode *p = G.vertices[u].firstarc;
        
        while(p != NULL) {
            int v = p->adjvex;
            if(dist[v] == -1) {
                dist[v] = dist[u] + 1;
                queue[rear++] = v;
            }
            p = p->nextarc;
        }
    }

    return dist;
}

// 距离小于k的顶点集合
vector<int> VerticesSetLessThanK(ALGraph G, KeyType v, int k) {
    vector<int> result;
    int vPos = LocateVex(G, v);
    
    if(vPos == -1) {
        RED;printf("错误：顶点%d不存在！\n", v);
        return result;
    }
    
    if(k <= 0) {
        RED;printf("错误：距离k必须大于0！\n");
        return result;
    }

    vector<int> dist = BFSShortestPath(G, v);
    
    for(int i=0; i<G.vexnum; i++) {
        if(dist[i] != -1 && dist[i] < k) {
            result.push_back(G.vertices[i].data.key);
        }
    }

    return result;
}

// 顶点间最短路径长度
int ShortestPathLength(ALGraph G, KeyType v, KeyType w) {
    int vPos = LocateVex(G, v);
    int wPos = LocateVex(G, w);
    
    if(vPos == -1 || wPos == -1) {
        return -2; // -2表示顶点不存在
    }
    
    if(v == w) {
        return 0;
    }

    vector<int> dist = BFSShortestPath(G, v);
    return dist[wPos]; // -1表示不可达
}