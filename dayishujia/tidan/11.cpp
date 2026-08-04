#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define for(x) for(ll i=0;i<x;i++)
vector<char>s;
ll qwe;
void count11(){
    int w=0,l=0;
    for(qwe){
        if(s[i]=='W')w++;
        else l++;
        if((w>=11||l>=11)&&abs(l-w)>=2){
            printf("%d:%d\n",w,l);
            w=0,l=0;
        }
    }
    printf("%d:%d\n",w,l);
}
void count21(){
    int w=0,l=0;
    for(qwe){
        if(s[i]=='W')w++;
        else l++;
        if((w>=21||l>=21)&&abs(l-w)>=2){
            printf("%d:%d\n",w,l);
            w=0,l=0;
        }
    }
    printf("%d:%d\n",w,l);
}
int main(){
    char ch;
    while(cin>>ch){
        if(ch=='E')break;
        else if(ch=='W'||ch=='L')s.push_back(ch);
    }
    qwe=s.size();
    count11();
    cout<<endl;
    count21();
}