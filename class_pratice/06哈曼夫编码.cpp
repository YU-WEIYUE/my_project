#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;
struct node{
	int w;
	char c;
	int left;
	int right;

	bool operator<(const node& other)const{//重载<,必须写在结构体内
		return w>other.w;//小顶堆
	}
};

vector<node>tree;
vector<string>code;
int cnt;

void dfs(int u,string cur){
	
}
int main(){
	
}