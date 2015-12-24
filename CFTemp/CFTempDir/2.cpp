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
    
    string a, b;
    cin >> a >> b;
    
    vector<int> a1(a.length());
    for (int i = 0; i < a.length(); i++) {
        a1[i] = (a[i] == '1'?1:0) + (i?(a1[i-1]):0);
    }
    
    vector<int> b1(b.length());
    for (int i = 0; i < b.length(); i++) {
        b1[i] = (b[i] == '1'?1:0) + (i?(b1[i-1]):0);
    }
    
    int64_t sum = 0;
    for (size_t i = 0; i < a.length(); i++) {
        size_t j = b.length()-a.length()+i;
        size_t x1 = b1[j] - (i?b1[i-1]:0);
        if (a[i] == '0') {
            sum += x1;
        } else {
            sum += (j-(i-1))-x1;
        }
    }
    
    cout << sum;
}
