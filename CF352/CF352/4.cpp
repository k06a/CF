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
    
    int n, k;
    cin >> n >> k;
    
    vector<int> v(n);
    cin >> v;
    
    sort(v.begin(), v.end(), [](int a, int b) {
        return a > b;
    });
    
    int j = 0;
    int vj = 0;
    int t = 0;
    int maxx = 0;
    for (int i = 0; i < n-1 && k > 0; i++) {
        int want = (i+1)*(v[i]-v[i+1]);
        int got = min(want, k);
        v[i] -= got-i*(v[i]-v[i+1]);
        t += got;
        k -= got;
        maxx = max(maxx, v[i]);
        j = i;
        vj = v[i];
    }
    
    if (k) {
        v.back() -= k/v.size();
        t = k;
        k = 0;
    }
    
    int w = 0;
    int minx = 1000000000;
    for (int i = n-1; i >= 1 && t > 0; i--) {
        int want = (n-1-i)*((i>j?v[i-1]:vj)-v[i]);
        int got = min(want, t);
        v[i] += got-(n-2-i)*((i>j?v[i-1]:vj)-v[i]);
        w += got;
        t -= got;
        minx = min(minx, v[i]);
    }
    
    cout << maxx-minx;
    return 0;
}
