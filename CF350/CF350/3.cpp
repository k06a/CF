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
    vector<int> va(n);
    for (int i = 0; i < n; i++) {
        cin >> va[i];
    }
    
    int m;
    cin >> m;
    vector<int> vb(m);
    vector<int> vc(m);
    for (int i = 0; i < m; i++) {
        cin >> vb[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> vc[i];
    }
    
    //
    
    unordered_map<int, int> langs;
    for (int i = 0; i < n; i++) {
        langs[va[i]]++;
    }
    
    //
    
    int max_i = 0;
    int max_listen = 0;
    int max_read = 0;
    for (int i = 0; i < m; i++) {
        int listen = langs[vb[i]];
        int read = langs[vc[i]];
        if (listen > max_listen || (listen == max_listen && read > max_read)) {
            max_listen = listen;
            max_read = read;
            max_i = i;
        }
    }
    
    cout << max_i+1;
}
