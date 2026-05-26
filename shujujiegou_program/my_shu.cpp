/*----------头文件的引入---------*/
#include<bits/stdc++.h>
using namespace std;

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

LISTS Lists; // 二叉树集合的定义 Lists
LISTS Lists = {0};

void visit(BiTree T){
    printf("%d ",T->data.key);
}

//定义字体颜色切换
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
#define GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

/*---- 函数申明 ----*/
status CreateBiTree(BiTree &T, TElemType definition[]);  //创建
status DestroyBiTree(BiTree &T);  //销毁
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
status LoadBiTree(BiTree &T, char FileName[]);  //从文件中加载
int MaxPathSum(BiTree T);  //最大路径和
BiTree LowestCommonAncestor(BiTree T, int e1, int e2);  //最近公共祖先
BiTree InvertTree(BiTree T);  //翻转二叉树
BiTree findfather(BiTree root, KeyType e);  //找到父节点
int countsons(BiTree T, KeyType e);  //统计子节点个数

//主函数
int main(){

}


status CreateBiTree(BiTree &T, TElemType definition[]){//1.构造二叉树

    static int i = 0; // 静态变量，记录当前已经处理到的序列下标
    int j = 0, k = 0; // 循环计数器

    // 第一次调用时，检查数据是否合法
    if (i == 0) {
        // 依次检查每个节点关键字是否合法
        for (j = 0; (definition + j)->key != -1; j++) {
            for (k = j + 1; (definition + k)->key != -1; k++) {
                // 如果有两个关键字相同，且不为0，返回错误
                if ((definition + j)->key == (definition + k)->key && (definition + j)->key != 0)
                    return ERROR;
            }
        }
    }

    // 递归出口：序列遍历结束，T为空值，返回OK
    if ((definition + i)->key == -1) {
        T = NULL;
        i = 0;
        return OK;
    }

    // 如果当前节点为0，表示空结点，无需创建二叉树结点，i自增并返回OK
    if ((definition + i)->key == 0) {
        i++;
        return OK;
    }

    // 创建二叉树结点，分别处理其左右子树，递归构建整棵二叉树
    T = (BiTree)malloc(sizeof(BiTNode));
    T->lchild = NULL;
    T->rchild = NULL;
    T->data = *(definition + i);
    i++;
    CreateBiTree(T->lchild, definition);
    CreateBiTree(T->rchild, definition);
    return OK;
}

status DestroyBiTree(BiTree &T){//2.销毁
    ClearBiTree(T);
    int i=0;
    for(i=0;i<Lists.length;i++){
        if(strcmp(Lists.elem[i].name,T->data.others)==0){
            ClearBiTree(Lists.elem[i].T);
            for(int j=i;j<Lists.length-1;j++){
                Lists.elem[j]=Lists.elem[j+1];
            }
            Lists.length--;
            return OK;
        }
    }
    Lists.length--;

    return ERROR;
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
    if(T == NULL) return ERROR; // 如果树为空，无法插入
    BiTNode* p = LocateNode(T, e); // 查找关键字为e的结点
    if(p == NULL) return ERROR; // 如果没有找到结点，无法插入
    if(LR==0){
        if(p->lchild){BiTree temp=p->lchild;
        p->lchild=(BiTree)malloc(sizeof(BiTNode));
        p->lchild->data=c;
        p->lchild->rchild=temp;}
        else {
            p->lchild=(BiTree)malloc(sizeof(BiTNode));
            p->lchild->data=c;
            p->lchild->rchild=NULL;
        }
    }
    else if(LR==1){
        if(p->rchild){BiTree temp=p->rchild;
        p->rchild=(BiTree)malloc(sizeof(BiTNode));
        p->rchild->data=c;
        p->rchild->rchild=temp;}
        else {
            p->rchild=(BiTree)malloc(sizeof(BiTNode));
            p->rchild->data=c;
            p->rchild->rchild=NULL;
        }
    }
    else if(LR==-1){
        BiTree newnode=(BiTree)malloc(sizeof(BiTNode));
        newnode->data=c;
        newnode->lchild=NULL;
        newnode->rchild=T;
        T=newnode;
    }
    else return ERROR; // LR不合法，无法插入
}

status DeleteNode(BiTree &T, KeyType e){//10.删除结点
    BiTree p=LocateNode(T,e);
    int sons=countsons(T,e);
    if(p==NULL)return ERROR;
    BiTree father=findfather(T,e);
    if(sons==0){  
            free(p);
            p==NULL;
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











BiTree findfather(BiTree root, KeyType e){//20.找到父亲节点
    if(root==NULL)return NULL;
    if(root->data.key==e)return NULL;
    if((root->lchild!=NULL&&root->lchild->data.key==e)||(root->rchild!=NULL&&root->rchild->data.key==e))return root;
    BiTree p=findfather(root->lchild,e);
    if(p!=NULL)return p;
    return findfather(root->rchild,e);
}

int countsons(BiTree T, KeyType e){//21.统计子节点个数
    BiTree p=LocateNode(T,e);
    if(p==NULL)return -1;
    int count=0;
    if(p->lchild!=NULL)count++;
    if(p->rchild!=NULL)count++;
    return count;
}




