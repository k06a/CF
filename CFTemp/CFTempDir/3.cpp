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
    vector<int> a(n);
    vector<int> b(n);
    map<int,int> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        m[a[i]] = b[i];
    }

    size_t best = 0;
    for (int f = n-1; f >= 0; f--)
    {
        size_t alive = 1;
        for (auto it = m.find(a[f]); it != m.begin(); --it)
        {
            //cout << 'A';
            alive++;
            int val = it->first - it->second;
            while (it->first >= val) {
                if (it == m.begin()) {
                    //cout << '_';
                    alive--;
                    break;
                } else {
                    //cout << 'B';
                    --it;
                }
            }
            ++it;
        }
        best = max(best, alive);
        //cout << alive << endl;
    }
    
    cout << n - best;
}
