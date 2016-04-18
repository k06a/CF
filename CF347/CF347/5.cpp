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

template <typename T>
vector<size_t> sort_indexes(const vector<T> &v) {
    
    // initialize original index locations
    vector<size_t> idx(v.size());
    for (size_t i = 0; i != idx.size(); ++i) idx[i] = i;
    
    // sort indexes based on comparing values in v
    sort(idx.begin(), idx.end(),
         [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});
    
    return idx;
}

int ball(int solved, int n) {
    if (n/solved-1 >= 32) {
        return 3000;
    }
    return ((int[]){500,1000,1500,2000,2500,3000})[(int)(log(n/solved)/log(2)-1)];
}

pair<int,vector<int> > ranknsolved(vector<vector<int> > &abc, int &additional, int n) {
    vector<int> balls(n, 0);
    vector<int> solo;
    for (int t = 0; t < 3; t++) {
        vector<int> &v = abc[t];
        int solved = (int)count_if(v.begin(), v.end(), bind1st(less<int>(), 0));
        solo.push_back(solved);
        for (int i = 0; i < n; i++) {
            if (v[i] != 0) {
                balls[i] += solved*(250-abs(v[i]))/250;
            }
        }
    }
    
    return make_pair(n - (int)sort_indexes(balls)[0], solo);
}

void main_file(string const& filename)
{
#ifdef DEBUG
    ifstream cin(filename);
    if (!cin)
        return;
#endif
    
    int n;
    vector<vector<int>> abc(3);
    cin >> n;
    for (int t = 0; t < 3; t++) {
        vector<int> &v = abc[t];
        v.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i] >> v[i] >> v[i];
        }
    }
    
    int additional = 0;
    for (int t = 0; t < 3; t++) {
        vector<int> &v = abc[t];
        if (v[0] == 0) {
            for (int i = 1; i < v.size(); i++) {
                if (v[i] < 0) {
                    additional += 100;
                    v[i] = 0;
                }
            }
        }
    }
    
    pair<int,vector<int> > rs = ranknsolved(abc, additional, n);
    if (1024/rs.first == 1024/(rs.first+1)) {
        additional += 100;
    }
    
    cout << n;
}
