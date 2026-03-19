#include<iostream>
using namespace std;
int n,m;
int find(int x,int *arr){
    if(arr[x]!=x){
        arr[x]=find(arr[x],arr);
    }
    return arr[x];
}
void merge(int x,int y,int *arr){
    int rootx=find(x,arr),rooty=find(y,arr);
    if(rootx!=rooty){
        arr[rootx]=rooty;
    }
}
int main(){
    cin>>n;
    while(n){
        cin>>m;
        int parent[1001];
        for(int i=1;i<=n;i++)parent[i]=i;
        for(int i=1;i<=m;i++){
            int a,b;cin>>a>>b;
            merge(a,b,parent);

        }
        int cnt=0;
        for(int i=1;i<=n;i++){
            if(parent[i]==i)cnt++;
        }
        cout<<cnt-1<<endl;
        cin>>n;
    }
}