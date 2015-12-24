#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <map>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, const char * argv[])
{
    //fstream cin("/Users/k06a/Projects/CF336/CF336/1.txt");
    
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
