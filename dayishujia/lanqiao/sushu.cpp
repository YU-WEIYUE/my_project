#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define itn int
int n,q,o;
int primes[6000000];
int cnt;
const int N=1e8+5;
bool arr[N];
void dig(){
    for(int i=2;i<=n;i++){
        if(!arr[i])primes[cnt++]=i;
        for(int j=0;j<cnt&&i*primes[j]<=n;j++){
            arr[i*primes[j]]=1;
            if (i % primes[j] == 0) break;
        }
    }
}
int main(){
    scanf("%d %d",&n,&q);
    dig();
    for(int i=0;i<q;i++){
        scanf("%d",&o);
        printf("%d\n",primes[o-1]);
    }
}