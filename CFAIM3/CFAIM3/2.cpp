#include <algorithm>
#include <deque>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T1, typename T2>
istream &operator>>(istream &stream, pair<T1, T2> &p) {
    stream >> p.first >> p.second;
    return stream;
}

template <typename T1, typename T2>
ostream &operator<<(ostream &stream, const pair<T1, T2> &p) {
    stream << p.first << ' ' << p.second;
    return stream;
}

template <typename T>
istream &operator>>(istream &stream, vector<T> &vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        stream >> vec[i];
    }
    return stream;
}

template <typename T>
ostream &operator<<(ostream &stream, const vector<T> &vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        if (i) {
            stream << ' ';
        }
        stream << vec[i];
    }
    return stream;
}

template <typename T>
class MapSmartAccessorWrapper {
    T &m;

  public:
    MapSmartAccessorWrapper(T &m)
        : m(m) {
    }
    typename T::mapped_type &operator[](const typename T::key_type &key) {
        return m[key];
    }
    typename T::mapped_type operator[](const typename T::key_type &key) const {
        auto it = m.find(key);
        if (it == m.end()) {
            typedef typename T::mapped_type mapped_type;
            return mapped_type();
        }
        return it->second;
    }
};

template <typename TKey, typename TValue>
MapSmartAccessorWrapper<map<TKey, TValue>> operator++(map<TKey, TValue> &m,
                                                      int i) {
    return m;
}

template <typename TKey, typename TValue>
MapSmartAccessorWrapper<unordered_map<TKey, TValue>>
    operator++(unordered_map<TKey, TValue> &m, int i) {
    return m;
}

//

int main_file(string const &filename);

int main(int argc, const char *argv[]) {
    ios_base::sync_with_stdio(false);

#ifndef ONLINE_JUDGE
    string base = __FILE__;
    base.replace(base.length() - 3, 3, "txt");
    for (int i = 0; i < 3; i++) {
        string filename = base;
        filename.insert(filename.length() - 4, 1, 'a' + i);
        main_file(filename);
        cout << endl;
    }
}

int main_file(string const &filename) {
    ifstream cin(filename);
    if (!cin || cin.peek() == -1)
        return 0;
#endif

    int n, a;
    cin >> n >> a;

    vector<int> v(n);
    cin >> v;

    sort(v.begin(), v.end());

    if (n == 1) {
        cout << 0;
        return 0;
    }
    
    cout << min(min(abs(a - v[1]) + abs(v.back() - v[1]),
                    abs(a - v.back()) + abs(v.back() - v[1])),
                min(abs(a - v.front()) + abs(v[n - 2] - v.front()),
                    abs(a - v[n - 2]) + abs(v[n - 2] - v.front())));
    return 0;
}
