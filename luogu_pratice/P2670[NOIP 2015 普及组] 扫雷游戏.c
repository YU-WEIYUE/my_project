#include <stdio.h>
#include<stdlib.h>
int res[105][105];
int map[105][105];
int main(){
    int m, n;
    char c;
    scanf("%d %d", &m, &n);getchar();
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            scanf("%c",&c);
            if(c=='*'){ 
                map[i][j]=-1;
                res[i+1][j+1]++;
                res[i+1][j]++;

                res[i+1][j-1]++;
                res[i][j+1]++;
                res[i][j-1]++;
                res[i-1][j+1]++;
                res[i-1][j]++;
                res[i-1][j-1]++;
            }
        }
        getchar();
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(map[i][j]==-1){
                printf("*");
                continue;
            }
            printf("%d",res[i][j]);
        }
        printf("\n");
    }
}
