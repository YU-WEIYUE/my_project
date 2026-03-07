#include<iostream>

using namespace std;
int main()
{
	int t;
	cin>>t;
	BREAK:
	while(t--)
	{
		string a,b;
		cin>>a>>b;
		int l=a.size(),ll=b.size();
		if(abs(l-ll)>=2)cout<<"not similar\n";
		else if(l==ll)
		{
			int s=0;
			for(int i=0;i<l;i++)
				if(a[i]!=b[i])s++;
			if(s<=1)cout<<"similar\n";
			else cout<<"not similar\n";
		}
		else
		{
			if(l<ll)swap(a,b),swap(l,ll);
			int s=0;
			for(int i=0;i<ll;i++)
			{
				if(a[i+s]!=b[i])s++;
				if(a[i+s]!=b[i]&&s)
				{
					cout<<"not similar\n";
					goto BREAK;
				}
			}
			cout<<"similar\n";
		}
	}
	return 0;
}