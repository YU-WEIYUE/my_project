#include<bits/stdc++.h>
using namespace std;
double dis(double x1, double y1, double x2, double y2) {
	double a, b, c;
	a = x1 - x2;
	b = y1 - y2;
	c = sqrt(a * a + b * b);
	return c;
}
int main() {
	double c = 0, x1, y1, x2, y2, x3, y3;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	c = dis(x1, y1, x2, y2) + dis(x2, y2, x3, y3) + dis(x3, y3, x1, y1);
	printf("%.2lf", c);
	return 0;
}
