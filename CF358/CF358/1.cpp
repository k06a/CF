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
    
    int64_t n, m;
    cin >> n >> m;
    
    int64_t ostat = 0;
    for (int i = 1; i <= n%5; i++) {
        for (int j = 1; j <= m%5; j++) {
            if ((i+j)% 5 == 0) {
                ostat++;
            }
        }
    }
    
    int64_t sum = (n/5)*(m/5)*5;
    sum += (n%5)*(m/5);
    sum += (m%5)*(n/5);
    sum += ostat;
    
    cout << sum;
    return 0;
}
