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

int main(int argc, const char * argv[])
{
#ifdef DEBUG
    fstream cin("/Users/k06a/Projects/CF336/CF336/1.txt");
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
