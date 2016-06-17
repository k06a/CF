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
#include <functional>

using namespace std;

template<typename T1, typename T2>
istream &operator >>(istream &stream, pair<T1,T2> &p) {
    stream >> p.first >> p.second;
    return stream;
}

template<typename T1, typename T2>
ostream &operator <<(ostream &stream, const pair<T1,T2> &p) {
    stream << p.first << ' ' << p.second;
    return stream;
}

template<typename T>
istream &operator >>(istream &stream, vector<T> &vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        stream >> vec[i];
    }
    return stream;
}

template<typename T>
ostream &operator <<(ostream &stream, const vector<T> &vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        if (i) {
            stream << ' ';
        }
        stream << vec[i];
    }
    return stream;
}

template<typename T>
class MapSmartAccessorWrapper {
    T &m;
public:
    MapSmartAccessorWrapper(T &m) : m(m) {
    }
    typename T::mapped_type & operator[] (const typename T::key_type &key) {
        return m[key];
    }
    typename T::mapped_type operator[] (const typename T::key_type &key) const {
        auto it = m.find(key);
        if (it == m.end()) {
            typedef typename T::mapped_type mapped_type;
            return mapped_type();
        }
        return it->second;
    }
};

template<typename TKey, typename TValue>
MapSmartAccessorWrapper<map<TKey,TValue> > operator++ (map<TKey,TValue> &m, int i) {
    return m;
}

template<typename TKey, typename TValue>
MapSmartAccessorWrapper<unordered_map<TKey,TValue> > operator++ (unordered_map<TKey,TValue> &m, int i) {
    return m;
}

//

struct Node {
    int w;
    int i, j;
    
    Node(int w = 0, int i = 0, int j = 0) : w(w), i(i), j(j) {}
};

int main_file(string const& filename);

int main(int argc, const char * argv[])
{
    ios_base::sync_with_stdio(false);
    
#ifndef ONLINE_JUDGE
    string base = __FILE__;
    base.replace(base.length()-3, 3, "txt");
    for (int i = 0; i < 3; i++) {
        string filename = base;
        filename.insert(filename.length()-4, 1, 'a'+i);
        main_file(filename);
        cout << endl;
    }
}

int main_file(string const& filename)
{
    ifstream cin(filename);
    if (!cin || cin.peek() == -1)
        return 0;
#endif
    
    int n, m, p;
    cin >> n >> m >> p;
    
    vector<vector<int> > a(n);
    for (int i = 0; i < n; i++) {
        a[i].resize(m);
    }
    cin >> a;
    
    vector<list<pair<int,int> > > pairsByNumber(p+1);
    pairsByNumber[0].push_back(make_pair(0,0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pairsByNumber[a[i][j]].push_back(make_pair(i,j));
        }
    }
    
    const int OriginShift = -1;
    vector<vector<int> > weights;
    weights.resize(n);
    for (int row = 0; row < n; row++) {
        weights[row].resize(m, OriginShift);
    }
    
    for (int i = 1; i <= p; i++) {
        for (const pair<int,int> &next : pairsByNumber[i]) {
            int &newWeightRef = weights[next.first][next.second];
            
            for (const pair<int,int> &prev : pairsByNumber[i-1]) {
                int &weightRef = weights[prev.first][prev.second];
                int w = weightRef + abs(prev.first - next.first) + abs(prev.second - next.second);
                if (newWeightRef == -1 || w < newWeightRef) {
                    newWeightRef = w;
                }
            }
        }
    }
    
    pair<int,int> last = pairsByNumber[p].front();
    cout << weights[last.first][last.second] - OriginShift;
    return 0;
}
