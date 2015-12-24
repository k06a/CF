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
    
    int n, s;
    cin >> n >> s;
    
    vector<int> v(s+1);
    for (int i = 0 ; i < n; i++) {
        int f, t;
        cin >> f >> t;
        v[f] = max(v[f], t);
    }
    
    int now = 0;
    for (int i = s; i >= 0; i--) {
        now += (i?1:0) + max(0, v[i] - now);
        //cout << now << endl;
    }
    
    cout << now;
}
