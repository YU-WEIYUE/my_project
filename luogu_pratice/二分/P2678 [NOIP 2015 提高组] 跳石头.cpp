#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int l,n,m,temp;//距离，原岩石数，移走岩石数
int main(){
    cin>>l>>n>>m;
    vector<int>stones;
    stones.push_back(0);
    for(int i=0;i<n;i++){
        cin>>temp;
        stones.push_back(temp);
    }
    stones.push_back(l);
    int left=0,right=l,ans=0;
    while(left<=right){
        int mid=(left+right)/2;
        int remove=0,prev=0;
        for(int i=1;i<stones.size();i++){
            if(stones[i]-stones[prev]<mid) remove++;
            else prev=i;
        }
        if(remove<=m){
            ans=mid;
            left=mid+1;
        }
        else right=mid-1;
    }
    cout<<ans;
    return 0;

}