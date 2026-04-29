#include<iostream>
#include<cstdio>
using namespace std;
double a,b,c,d,x1,x2,l,r,mid;
int s;
double compute(double x){
    return a*x*x*x+b*x*x+c*x+d;
}
int main(){
    scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
    for(int i=-100;i<100;i++){
        if(s==3)break;
        l=i;r=i+1;
        x1=compute(l);
        x2=compute(r);
        if(!x1){
            printf("%.2lf ",l);s++;
            continue;
        }
        if(x1*x2<0){
            while(r-l>=0.001){
                mid=(l+r)/2.0;
                if(compute(mid)*compute(r)<=0)l=mid;
                else r=mid;
            }
            printf("%.2lf ",r);s++;
        }
        
    }
    return 0;
}