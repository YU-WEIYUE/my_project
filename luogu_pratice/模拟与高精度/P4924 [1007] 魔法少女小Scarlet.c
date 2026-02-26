#include<stdio.h>
#include<stdlib.h>
int arr[501][501],temp[501][501],a=1;
void spin(){
    int x,y,r,z;
    scanf("%d %d %d %d",&x,&y,&r,&z);//以第 x 行第 y 列为中心的 2r+1 阶矩阵按照某种时针方向旋转，其中 z=0 表示顺时针，z=1 表示逆时针
    switch(z){
        case 0:
            for(int i=x-r;i<=x+r;i++){
                for(int j=y-r;j<=y+r;j++){
                    arr[i][j]=temp[x+r+y-r-j][i-x+r];
                }
            }
            break;
        case 1:
            for(int i=x-r;i<=x+r;i++){
                for(int j=y-r;j<=y+r;j++){
                    arr[i][j]=temp[j-y+r][x+r+i-x]; 
                }
            }
            break;
    }
    
    for(int i=x-r;i<=x+r;i++){
        for(int j=y-r;j<=y+r;j++){
            temp[i][j]=arr[i][j];
        }
    }
}
int main(){
    int n,m;
    scanf("%d %d",&n,&m);

    for(int i=1;i<=n;i++){//init arr
        for(int j=1;j<=n;j++){
            arr[i][j]=a++;
            temp[i][j]=arr[i][j];
        }
    }
    for(int i=0;i<m;i++)spin();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%d ",arr[i][j]);
        }

        printf("\n");
    }
    return 0;
}