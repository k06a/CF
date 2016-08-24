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
    
    int n, q;
    cin >> n >> q;
    
    vector<int> app_t(n);
    vector<vector<int> > tec(q, vector<int>(n));
    int64_t unread = 0;
    int max_t = 0;
    for (int i = 0, k = 0; i < q; i++) {
        int act, t;
        cin >> act >> t;
        int x = t - 1;
        
        switch (act) {
            case 1:
                unread++;
                tec[k][x]++;
                k++;
                tec[k] = tec[k-1];
                break;
            
            case 2: {
                int old_t = max(max_t, app_t[x]);
                if (k > old_t) {
                    unread -= tec[k-1][x] - (old_t ? tec[old_t-1][x] : 0);
                }
                app_t[x] = k;
                break;
            }
            
            case 3:
                if (t > max_t) {
                    for (int j = 0; j < n; j++) {
                        int old_t = max(max_t, app_t[j]);
                        if (t > old_t) {
                            unread -= tec[t-1][j] - (old_t ? tec[old_t-1][j] : 0);
                        }
                    }
                    int prev_t = max_t;
                    max_t = t;
                    
                    for (int tt = prev_t; tt < max_t-1; tt++) {
                        tec[tt].clear();
                    }
                }
                break;
        }
        
        cout << unread << endl;
    }
    
    return 0;
}
