#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
struct node{
    int score;
    int num;
}a[200];
int q,n;
bool compare(const node&a,const node&b){
    return a.score>b.score;
}
int main(){
    cin>>q;
    n=1<<q;
    for(int i=0;i<n;i++){
        a[i].num=i+1;
        cin>>a[i].score;
    }
    sort(a,a+n/2,compare);
    sort(a+n/2,a+n,compare);
    a[0].score>a[n/2].score?cout<<a[n/2].num:cout<<a[0].num;
}
