#include <iostream>
using namespace std;
char map[12][12];//先上，有障碍*顺时针转
int F[2],C[2];
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
int _time=0;
int dirFF=0,dirCC=0;
void moveC(){
    if(map[C[0]+dx[dirCC]][C[1]+dy[dirCC]]=='*'){
        dirCC=(dirCC+1)%4;
        return;
    }
    C[0]+=dx[dirCC],C[1]+=dy[dirCC];
}
void moveF(){
    if(map[F[0]+dx[dirFF]][F[1]+dy[dirFF]]=='*'){
        dirFF=(dirFF+1)%4;
        return;
    }
    F[0]+=dx[dirFF],F[1]+=dy[dirFF];
}
int main(){
    for(int i=0;i<12;i++)map[0][i]=map[11][i]='*';
    for(int i=1;i<11;i++)map[i][0]=map[i][11]='*';
    for(int i=1;i<11;i++){
        for(int j=1;j<11;j++){
            cin>>map[i][j];
            if(map[i][j]=='F'){
                F[0]=i;F[1]=j;
            }
            if(map[i][j]=='C'){
                C[0]=i;C[1]=j;
            }
        }
    }
    while(_time<=160000){
        moveF();
        moveC();
        _time++;
        if(F[0]==C[0]&&F[1]==C[1]){
            cout<<_time;
            return 0;
        }
    }
    cout<<0;
    return 0;

}