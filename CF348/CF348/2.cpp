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

void main_file(string const& filename)
{
#ifdef DEBUG
    ifstream cin(filename);
    if (!cin)
        return;
#endif
    
    int n;
    cin >> n;
    
    string s;
    cin >> s;
    
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        int d;
        cin >> d;
        if (s[i] == '<') {
            v[i] = i-d;
        } else {
            v[i] = i+d;
        }
    }
    
    vector<bool> was(n);
    for (int i = 0; i >= 0 && i < n; i = v[i]) {
        if (was[i]) {
            cout << "INFINITE";
            return;
        }
        was[i] = true;
    }
    
    cout << "FINITE";
}
