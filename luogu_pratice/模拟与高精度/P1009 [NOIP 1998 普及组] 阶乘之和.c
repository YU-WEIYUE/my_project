#include<stdio.h>
#include<stdlib.h>
int main(){
    int n;
    scanf("%d",&n);
    unsigned long long *arr=(unsigned long long*)malloc(sizeof(unsigned long long)*n);
    arr[0]=1;
    unsigned long long sum=1;
    for(int i=1;i<n;i++){
        arr[i]=arr[i-1]*(i+1);
        sum+=arr[i];
    }
    printf("%llu",sum);
    free(arr);
}
