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

pair<int,int> f(int n) {
    int k = n/7*2;
    switch (n%7) {
        case 0: return make_pair(k,k);
        case 1: return make_pair(k,k+1);
        case 2: return make_pair(k,k+2);
        case 3: return make_pair(k,k+2);
        case 4: return make_pair(k,k+2);
        case 5: return make_pair(k,k+2);
        case 6: return make_pair(k+1,k+2);
    }
    return make_pair(0, 0);
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
    
    auto p = f(n);
    cout << p.first << ' ' << p.second;
}
