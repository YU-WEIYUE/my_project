#include <bits/stdc++.h>
#include <unordered_map>
#include <cstdio>
using namespace std;
#define ll long long
#define itn int
unordered_map<string,int>mp;
string name;
int score;
int main(){
    int q;cin>>q;
    int op;
    while(q--){
        cin>>op;
        switch(op){
            case 1:{
                cin>>name>>score;
                mp[name]=score;
                break;
            }
            case 2:{
                cin>>name;
                if(mp.find(name)==mp.end())printf("Not found\n");
                else printf("%d\n",mp[name]);
                break;
            }
            case 3:{
                cin>>name;
                mp.erase(name);
                break;
            }
            case 4:{
                printf("%d\n",(int)mp.size());
            }
        }
    }
}