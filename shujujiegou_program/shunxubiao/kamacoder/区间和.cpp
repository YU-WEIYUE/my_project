#include<stdio.h>
#include<stdlib.h>
int main(){
    int n;scanf("%d", &n);
    int *arr = (int*)malloc(n * sizeof(int));
    int *sum =(int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
        if(i==0)sum[i]=arr[i];
        else sum[i]=sum[i-1]+arr[i];
    }
    while(1){
        int a,b;scanf("%d%d", &a, &b);
        if(a==0)printf("%d\n",sum[b]);
        else printf("%d\n",sum[b]-sum[a-1]);
    }
}