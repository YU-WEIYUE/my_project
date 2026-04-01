#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define leng sizeof(struct node)
typedef struct node{
    int data;
    struct node *next;
}Node;

Node *creat1(){//先进先出
    Node *head,*tail,*p;
    int e;
    head=(Node*)malloc(leng);
    tail=head;
    scanf("%d",&e);
    while(e!=-1){
        p=(Node*)malloc(leng);
        p->data=e;
        tail->next=p;
        tail=p;
        scanf("%d",&e);
    }
    head->next=NULL;
    return head;
}

Node *creat2(){//先进后出
    Node *head,*p;
    int e;
    head=(Node*)malloc(leng);
    head->next=NULL;
    scanf("%d",&e);
    while(e!=-1){
        p=(Node*)malloc(leng);
        p->data=e;
        p->next=head->next;
        head->next=p;
        scanf("%d",&e);
    }
    return head;
}

Node* insert1(Node *p,int e){//在p节点后插入一个新节点
    Node *new_node=(Node*)malloc(leng);
    new_node->data=e;
    new_node->next=p->next;
    p->next=new_node;
    return new_node;
}


Node* insert2(Node *head, Node *p, int e){//在p节点前插入一个新节点
    if(head == NULL || p == NULL) return NULL;
    
    Node *pre = head;
    // 找p的前驱节点
    while(pre->next != p && pre->next != NULL){
        pre = pre->next;
    }
    
    // 插入新节点
    Node *new_node = (Node*)malloc(leng);
    new_node->data = e;
    new_node->next = p;
    pre->next = new_node;
    
    return new_node;
}

Node *insert_rise(int e,Node* head){//在有头结点递增链表中加入元素e，保持链表递增
    Node *new_node=(Node*)malloc(leng);
    new_node->data=e;
    Node *p=head;

    while(p->next!=NULL && p->next->data<e){
        p=p->next;
    }
    new_node->next=p->next;
    p->next=new_node;
    return new_node;

}

Node *insert(int e,int i,Node *head){//在链表head的第i个位置插入元素e
    Node *new_node=(Node*)malloc(leng);
    new_node->data=e;
    Node *p=head;
    int j=0;
    while(p!=NULL && j<i-1){
        p=p->next;
        j++;
    }
    if(p==NULL) return NULL;//i超过链表长度
    new_node->next=p->next;
    p->next=new_node;
    return new_node;

}


Node *delete(int e,Node *head){//删除其中元素为e的节点（可能有多个）
    Node *p=head;
    while(p->next!=NULL){
        if(p->next->data==e){
            Node *temp=p->next;
            p->next=temp->next;
            free(temp);
        }
        else    p=p->next;
    }
    return head;
}














int main(){
    return 0;
}
