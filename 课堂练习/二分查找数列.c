/* 
【题目描述】
小 F 会给出一个长度为 n 的数列 a，并进行以下五种询问：
• 1 x：查询数列中有多少个数刚好等于x 
• 2 x y：查询数列中有多少个数大于等于x并且小于等于y
• 3 x y：查询数列中有多少个数大于等于x 并且小于y
• 4 x y：查询数列中有多少个数大于x并且小于等于y 
• 5 x y：查询数列中有多少个数大于x并且小于y 
【输入格式】
第一行读入两个整数 n, m，表示数列的长度为 n，一共有 m 次询问。
第二行读入 n 个整数表示数列 a。
接下来 m 行，每行输入 p x 或 p x y，表示一个询问，其中 p 表示询问类型。
【输出格式】
对于每次询问输出一行一个整数表示询问的答案。
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

void swap(long *a,long *b){
    long temp=*a;
    *a=*b;
    *b=temp;
}

long binary_left(long *arr,long x,long l,long r){
    if(l==r)return l;//输出下标
    long mid=(l+r)/2;
    if(arr[mid]<x)return binary_left(arr,x,mid+1,r);
    if(arr[mid]>=x)return binary_left(arr,x,l,mid);
    return -1;
}

long binary_right(long *arr,long x,long l,long r){
    if(l==r)return l;//输出下标
    long mid=(l+r)/2;
    if(arr[mid]<=x)return binary_right(arr,x,mid+1,r);
    if(arr[mid]>x)return binary_right(arr,x,l,mid);
    return -1;
}

void sort(long *arr,long int left,long int right){//快速排序
    if(left>=right)return;
    long mid=(left+right)/2;
    long temp=arr[mid];
    long i=left,j=right;
    while(i<=j){
        while(arr[j]>temp)j--;
        while(arr[i]<temp)i++;
        if(i<=j){
            swap(&arr[i],&arr[j]);i++;j--;
        }
    }
    sort(arr,left,j);
    sort(arr,i,right);
}

void fun1(long x,long *arr,long len){
    long left=binary_left(arr,x,0,len);
    long right=binary_right(arr,x,0,len);

    long result=right-left;
    printf("%ld\n",result);
}

void fun2(long x,long y,long *arr,long len){//2 x y：查询数列中有多少个数大于等于x并且小于等于y
    if(x>y){
        printf("0\n");return;
    }
    long left=binary_left(arr,x,0,len);
    long right=binary_right(arr,y,0,len);
    long result=right-left;
    printf("%ld\n",result);
}

void fun3(long x,long y,long *arr,long len){//3 x y：查询数列中有多少个数大于等于x 并且小于y
    if(x>=y){
        printf("0\n");return;
    }
    long left=binary_left(arr,x,0,len);
    long right=binary_left(arr,y,0,len);
    long result=right-left;
    printf("%ld\n",result);
}

void fun4(long x,long y,long *arr,long len){//4 x y：查询数列中有多少个数大于x并且小于等于y 
    if(x>=y){
        printf("0\n");return;
    }
    long left=binary_right(arr,x,0,len);
    long right=binary_right(arr,y,0,len);
    long result=right-left;
    printf("%ld\n",result);
}

void fun5(long x,long y,long *arr,long len){//5 x y：查询数列中有多少个数大于x并且小于y 
    if(x>=y){
        printf("0\n");return;
    }
    long left=binary_right(arr,x,0,len);
    long right=binary_left(arr,y,0,len);
    long result=right-left;
    printf("%ld\n",result);
}

void menu(int a,long *arr,long length){
    long int x,y;
    switch(a){
        case 1:scanf("%ld",&x);fun1(x,arr,length);break;
        case 2:scanf("%ld %ld",&x,&y);fun2(x,y,arr,length);break;
        case 3:scanf("%ld %ld",&x,&y);fun3(x,y,arr,length);break;
        case 4:scanf("%ld %ld",&x,&y);fun4(x,y,arr,length);break;
        case 5:scanf("%ld %ld",&x,&y);fun5(x,y,arr,length);break;
    }

}


int main(){
    long int n,m;
    scanf("%ld %ld",&n,&m);
    long* arr=(long *)malloc(n*sizeof(long));
    if(arr==NULL){
        printf("malloc error");return -1;
    }
    for(long int i=0;i<n;i++){
        scanf("%ld",&arr[i]);
    }

    sort(arr,0,n-1);
    int x;
    
    for(int j=0;j<m;j++){
        scanf("%d",&x);
        menu(x,arr,n);
    }
    free(arr);
    return 0;
}
