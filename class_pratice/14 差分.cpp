#include<iostream>
using namespace std;
int a[2100][2100],d[2100][2100];
int n,m;
void insert(int x1,int y1,int x2,int y2){
    d[x1][y1]++;
    d[x1][y2+1]--;
    d[x2+1][y1]--;
    d[x2+1][y2+1]++;
}
int main(){
    cin>>n>>m;
    while(m--){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        insert(x1,y1,x2,y2);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            a[i][j]=d[i][j]+a[i-1][j]+a[i][j-1]-a[i-1][j-1];
            cout<<(a[i][j]&1);//偶数次表示还是原来的0
        }
        cout<<endl;
    }
    return 0;
}
