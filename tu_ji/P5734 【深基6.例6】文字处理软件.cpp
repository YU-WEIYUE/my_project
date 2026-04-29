#include <iostream>
using namespace std;
int op, a, b, q;
string s, str;
int main()
{
	cin >> q >> s;
	for (int i = 1; i <= q; i++)
	{
		cin >> op;
		if (op == 1)
		{
			cin >> str;
			s += str;
			cout << s << endl;
		}
		else if (op == 2)
		{
			cin >> a >> b;
			s = s.substr(a, b);
			cout << s << endl;
		}
		else if (op == 3)
		{
			cin >> a >> str;
			s.insert(a, str);
			cout << s << endl;
		}
		else
		{
			cin >> str;
			int tmp = s.find(str);
			if (tmp == string::npos)
				cout << -1 << endl;
			else
				cout << tmp << endl;
		}
	}
}
