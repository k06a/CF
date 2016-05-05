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
    for (int i = 0; i < 4; i++) {
        string filename = base;
        filename.insert(filename.length()-4, 1, 'a'+i);
        main_file(filename);
        cout << endl;
    }
#else
    main_file("");
#endif
}


void flip(vector<int> &v, int n, int index) {
    uint64_t *ptr = (uint64_t *)&v[index%2];
    for (int i = 0; ptr+i < (void*)&v[n-1]; i++) {
        ptr[i] = (ptr[i] << 32) | (ptr[i] >> 32);
    }
    if (index%2) {
        swap(v[0], v[n-1]);
    }
}

void main_file(string const& filename)
{
#ifdef DEBUG
    ifstream cin(filename);
    if (!cin)
        return;
#endif
    
    int n, q;
    cin >> n >> q;
    
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = i;
    }
    
    int index = 0;
    bool sw = false;
    bool first = true;
    bool even = true;
    for (int i = 0; i < q; i++) {
        int t, x;
        cin >> t;
        
        switch (t) {
            case 1:
                cin >> x;
                if (sw && (first || ((x % 2) != even))) {
                    flip(v, n, index);
                    sw = false;
                    first = false;
                }
                even = (x % 2);
                index = (index - x + n)%n;
                break;
                
            case 2:
                sw = !sw;
                break;
        }
    }
    
    if (sw) {
        flip(v, n, index);
    }
    
    for (int i = 0; i < n; i++) {
        if (i)
            cout << ' ';
        cout << v[(index+i)%n]+1;
    }
}
