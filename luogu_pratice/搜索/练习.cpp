#include<iostream>
#include<vector>
using namespace std;
char map[401][401];
int z,k,q1;
vector<int>key;
int main(){
    cin>>z;
    memset(map,'#',sizeof(map));
    for(int i=1;i<=z;i++)for(int j=1;j<=z;j++)cin>>map[i][j];
    cin>>k;
    for(int i=0;i<k;i++){
        cin>>q1;
        key.push_back(q1);
    }
    reverse(key.begin(),key.end());
     
}