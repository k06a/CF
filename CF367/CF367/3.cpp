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
#include <numeric>

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

template<typename T>
vector<size_t> sort_indexes(const vector<T> &v) {
    
    // initialize original index locations
    vector<size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0);
    
    // sort indexes based on comparing values in v
    sort(idx.begin(), idx.end(),
         [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});
    
    return idx;
}

//

int64_t walk_left(vector<pair<int,string> > &v, vector<string> &inv, int last, int from) {
    int64_t cost = v[last].first;
    for (int i = last-1; i >= from-1 && i >= 0; i--) {
        string next_inv = inv[i+1];
        
        if (v[i].second <= next_inv) {
            return cost;
        }
        
        bool left = (inv[i] <= next_inv);
        if (left) {
            if (i >= from) {
                cost += v[i].first;
            }
        } else {
            return -1;
        }
    }
    
    return cost;
}

int64_t walk_right(vector<pair<int,string> > &v, vector<string> &inv) {
    int last_unchanged_i = 0;
    bool last_reversed = false;
    int64_t cost = 0;
    for (int i = 1; i < v.size(); i++) {
        string prev = last_reversed ? inv[i-1] : v[i-1].second;
        string prev_inv = last_reversed ? v[i-1].second : inv[i-1];
        
        if (prev <= v[i].second) {
            last_reversed = false;
            continue;
        }
        
        bool left = (prev_inv <= v[i].second);
        bool right = (prev <= inv[i]);
        if (left && right) {
            int64_t left_cost = walk_left(v, inv, i-1, last_unchanged_i);
            if (left_cost != -1 && left_cost <= v[i].first && !last_reversed) {
                cost += left_cost;
                last_unchanged_i = i;
            } else {
                cost += v[i].first;
                last_unchanged_i = i+1;
                last_reversed = true;
            }
        } else if (left) {
            if (last_reversed) {
                return -1;
            }
            int64_t left_cost = walk_left(v, inv, i-1, last_unchanged_i);
            if (left_cost == -1) {
                return -1;
            }
            cost += left_cost;
            last_unchanged_i = i;
        } else if (right) {
            cost += v[i].first;
            last_unchanged_i = i+1;
            last_reversed = true;
        } else {
            return -1;
        }
    }
    
    return cost;
}

//

int main_file(string const& filename);

int main(int argc, const char * argv[])
{
    ios_base::sync_with_stdio(false);
    
#ifndef ONLINE_JUDGE
    string base = __FILE__;
    base.replace(base.length()-3, 3, "txt");
    for (int i = 0; i < 10; i++) {
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
    
    int n;
    cin >> n;
    
    vector<pair<int,string> > v(n);
    vector<string> inv(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
    }
    for (int i = 0; i < n; i++) {
        cin >> v[i].second;
        inv[i] = string(v[i].second.rbegin(), v[i].second.rend());
    }
  
    cout << walk_right(v, inv);
    
    return 0;
}
