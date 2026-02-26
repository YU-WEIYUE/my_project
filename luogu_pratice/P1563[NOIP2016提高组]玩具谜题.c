#include <stdio.h>
#include <stdlib.h>
int main(){
    long n,m,a,s,ans=1;
    scanf("%ld %ld",&n,&m);
    char *name=(char*)malloc(sizeof(char)*(n+1)*13);
    int *way=(int*)malloc(sizeof(int)*n);
    for(long i=1;i<=n;i++){
        scanf("%d %s",way+i,name+i*13);
    }
    while(m--){
        scanf("%ld%ld",&a,&s);
        ans=(ans+(a^way[ans]?s:n-s))%n,ans=(!ans?n:ans);//第一步判断是向前还是向后走，第二步判断是否越界，越界则回到起点
    }
    printf("%s",name+ans*13);
    free(name);
    free(way);
    return 0;
}
