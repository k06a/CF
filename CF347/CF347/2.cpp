#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <forward_list>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

void main_file(string const& filename);

int main(int argc, const char * argv[])
{
#ifdef DEBUG
    string base = __FILE__;
    base.replace(base.length()-3, 3, "txt");
    for (int i = 0; i < 3; i++) {
        string filename = base;
        filename.insert(filename.length()-4, 1, 'a'+i);
        main_file(filename);
        cout << endl;
    }
#else
    main_file("");
#endif
}

int gcd(int a, int b)
{
    for (;;)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

int lcm(int a, int b)
{
    int temp = gcd(a, b);
    return temp ? (a / temp * b) : 0;
}

void main_file(string const& filename)
{
#ifdef DEBUG
    ifstream cin(filename);
    if (!cin)
        return;
#endif
    
    string s;
    getline(cin, s);
    
    int n = atoi(s.substr(s.find_last_of(' ')+1).c_str());
    int pluses = (int)count(s.begin(), s.end(), '+') + 1;
    int minuses = (int)count(s.begin(), s.end(), '-');
    
    if (pluses*n - minuses*1 < n || pluses*1-minuses*n > n) {
        cout << "Impossible" << endl;
        return;
    }
    
    vector<int> ps(pluses, n);
    vector<int> ms(minuses, 1);
    
    int sum = pluses * n - minuses * 1;
    for (int i = 0; i < pluses; i++) {
        if (sum > n && ps[i] > 1) {
            int diff = min(sum-n, ps[i]-1);
            ps[i] -= diff;
            sum -= diff;
        }
    }
    for (int i = 0; i < minuses; i++) {
        if (sum > n && ms[i] < n) {
            int diff = min(sum-n, n-ms[i]);
            ms[i] += diff;
            sum -= diff;
        }
    }
    
    int i = 0, j = 0;
    size_t index;
    while ((index = s.find('?')) != string::npos) {
        int sign = (index == 0 || s[index-2] == '+') ? 1 : -1;
    
        int value;
        if (sign > 0) {
            value = ps[i++];
        } else {
            value = ms[j++];
        }
        
        s.replace(index, 1, to_string(value));
    }
    
    cout << "Possible" << endl;
    cout << s << endl;
}
