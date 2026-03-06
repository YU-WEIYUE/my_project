#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

int n;

struct tree{
    int left;
    int right;
};
tree arr[1000003];


void dfs(int u,int depth){
    if(u==0)return;
    dfs(arr[left],depth);
}


int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        tree qw;
        cin>>arr[i].left>>arr[i].right;
    }
    int depth=0;


}