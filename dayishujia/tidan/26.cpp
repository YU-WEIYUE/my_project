#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int main() {
    int n;
    cin >> n;
    unordered_set<string> s;
    while (n--) {
        string str;
        cin >> str;
        s.insert(str);
    }
    cout << s.size() << endl;
    return 0;
}