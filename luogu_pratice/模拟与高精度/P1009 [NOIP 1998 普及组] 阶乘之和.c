#include<stdio.h>
#include<stdlib.h>
int **arr;
int main(){
    int n;
    scanf("%d",&n);
    arr=(int**)malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++){
        arr[i]=(int*)malloc(sizeof(int)*70);
    }
    memset(arr,0,sizeof(int)*n*70);
    arr[0][0]=1;
    for(int i=1;i<n;i++){
        int carry=0;
        
    }
    for(int i=0;i<n;i++){
        free(arr[i]);
    }
    free(arr);
    return 0;
}
