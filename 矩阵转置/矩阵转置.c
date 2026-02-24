#include<stdio.h>
#include<stdlib.h>
typedef struct {
    int i,j;
    int v;
}triple;
typedef struct {
    triple data[100];
    int m,n,t;
}trilist;


void readin(trilist *t){
    int i;
    scanf("%d%d%d",&t->m,&t->n,&t->t);//输入行数、列数、非零元素个数
    for(i=0;i<t->t;i++){
        scanf("%d%d%d",&t->data[i].i,&t->data[i].j,&t->data[i].v);//输入非零元素的行号、列号、值
    }
}

trilist tansmat(trilist m){
    trilist n;
    n.m=m.n;
    n.n=m.m;
    n.t=m.t;
    if(m.t){
        int q=1,col,p;//q为n中非零元素的个数，col为m中列号，p为m中非零元素的个数
        for(col=1;col<=m.n;col++){//扫描m的每一列
            for(p=0;p<m.t;p++){//扫描m中所有非零元素
                if(m.data[p].j==col){//如果m中非零元素的列号等于col
                    n.data[q].i=m.data[p].j;
                    n.data[q].j=m.data[p].i;
                    n.data[q].v=m.data[p].v;
                    q++;
                }
            }
        }
   }
    return n;
}

trilist fasttansmat(trilist m){
    trilist n;int num[100],posggg[100];
    n.m=m.n;
    n.n=m.m;
    n.t=m.t;
    if(m.t){
        int col,t,p,q;
        for(col=1;col<=m.n;col++) num[col]=0;//num数组记录m中每一列的非零元素个数
        for(t=0;t<m.t;t++) num[m.data[t].j]++;//统计m中每一列的非零元素个数
    }
    
}