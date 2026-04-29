#include <iostream>
using namespace std;
int n, cnt;
bool f[5][20];
int zhn(char x){ 
    if('2' <= x && x <= '9') return x - '0';
    if(x == 'A') return 1;
    if(x == 'T') return 10;
    if(x == 'J') return 11;
    if(x == 'Q') return 12;
    if(x == 'K') return 13;
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        char c1, c2;
        cin >> c1 >> c2;
        if(c1 == 'D') f[1][zhn(c2)] = 1;
        else if(c1 == 'C') f[2][zhn(c2)] = 1;
        else if(c1 == 'H') f[3][zhn(c2)] = 1;
        else if(c1 == 'S') f[4][zhn(c2)] = 1;
    }
    for(int i = 1; i <= 4; i++){
        for(int j = 1; j <= 13; j++){
            if(!f[i][j]) cnt++; 
        }
    }
    cout << cnt;
    return 0;

}