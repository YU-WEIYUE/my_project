#include<bits/stdc++.h>
using namespace std;
int b;
int a[130][130];
int s[130][130];
int ans=-9999;
int main(){
    cin>>b;
    for(int i=1;i<=b;i++){
        for(int j=1;j<=b;j++){
            cin>>a[i][j];
            s[i][j] = a[i][j] + s[i-1][j] + s[i][j-1] - s[i-1][j-1];
        }
    }
    for(int i=1;i<=b;i++){
        for(int j=1;j<=b;j++){
            for(int x=i;x<=b;x++){
                for(int y=j;y<=b;y++){
                    int temp = s[x][y] - s[i-1][y] - s[x][j-1] + s[i-1][j-1];
                    if(temp>ans)ans=temp;
                }
            }
        }
    }
    cout<<ans;

}