#include<stdlib.h>
#include<stdio.h>
int main(){
    int m,n;
    printf("%d%d",&m,&n);
    int**map=(int**)malloc(m*sizeof(int*));
    int **sum=(int **)malloc(m*sizeof(int *));
    for(int i=0;i<m;i++){
        map[i]=(int*)malloc(n*sizeof(int));
        sum[i]=(int*)malloc(n*sizeof(int));
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&map[i][j]);
        }
    }
}