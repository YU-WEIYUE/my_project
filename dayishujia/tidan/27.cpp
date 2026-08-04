#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define itn int
unordered_map<string,int>id;
int n,m;
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        string w;
        cin>>w;
        id[w]=i;
    }
}