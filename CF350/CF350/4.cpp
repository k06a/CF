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
    for (int i = 0; i < 6; i++) {
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
    
    int64_t n, k;
    cin >> n >> k;
    vector<int64_t> va(n);
    for (int i = 0; i < n; i++) {
        cin >> va[i];
    }
    vector<int64_t> vb(n);
    for (int i = 0; i < n; i++) {
        cin >> vb[i];
    }
    
    //
    
    vector<pair<int,double> > vk(n);
    for (int i = 0; i < n; i++) {
        vk[i] = make_pair(i, vb[i] * 1.0 / va[i]);
    }
    
    sort(vk.begin(), vk.end(), [](const pair<int,double> &p1, const pair<int,double> &p2) {
        return p1.second < p2.second;
    });
    
    int64_t height = vk[0].second;
    int64_t rowWeight = 0;
    for (int i = 0; i < n; i++) {
        int64_t index = vk[i].first;
        
        int64_t need = va[index] - vb[index]%va[index];
        if (need > 0 && need < va[index] && k >= need + rowWeight) {
            k -= need + rowWeight;
            height++;
        }
        rowWeight += va[index];
        
        int64_t needRows = (i + 1 < n) ? (vk[i+1].second - height) : k;
        int64_t haveRows = min(k/rowWeight, needRows);
        if (haveRows) {
            k -= haveRows*rowWeight;
            height += haveRows;
        }
    }
    
    cout << height;
}
