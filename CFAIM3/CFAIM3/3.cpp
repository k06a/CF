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
MapSmartAccessorWrapper<map<TKey, TValue>> operator++(map<TKey, TValue> &m, int i) {
    return m;
}

template <typename TKey, typename TValue>
MapSmartAccessorWrapper<unordered_map<TKey, TValue>> operator++(unordered_map<TKey, TValue> &m, int i) {
    return m;
}

//

char dec(char c) {
    return (c == 'a') ? 'z' : c - 1;
}

string &dec(string &s, const pair<int, int> &p) {
    for (int i = p.first; i <= p.second; i++) {
        s[i] = dec(s[i]);
    }
    return s;
}

//pair<int, int> buffer[100001] = {};

pair<int, int> f(const string &s, size_t n) {
    if (n == 1) {
        return (s[0] == 'a') ? make_pair(0, -1) : make_pair(0, 0);
    }
    pair<int, int> p = f(s, n - 1);
    if (p.second == n - 2) {
        string ss1 = s;
        dec(ss1, p);

        pair<int, int> p2 = make_pair(p.first, p.second + 1);
        string ss2 = s;
        dec(ss2, p2);

        return (ss1 < ss2) ? p : p2;
    }

    if (p.second == -1 && s[n - 1] > 'a') {
        return make_pair(n - 1, n - 1);
    }

    return p;
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

    string s;
    cin >> s;

    int begin = -1;
    int end = -1;
    for (int i = 0; i < s.size(); i++) {
        if (begin == -1 && s[i] != 'a') {
            begin = end = i;
        }
        if (end == i-1) {
            if (dec(s[i]) < s[i]) {
                end = i;
            }
        }
    }
    
    if (end != -1) {
        cout << dec(s, make_pair(begin, end));
    } else {
        cout << dec(s, make_pair(s.size()-1, s.size()-1));
    }
    
//    pair<int, int> p = f(s, s.size());
//    if (p.second != -1) {
//        cout << dec(s, p);
//    }
//    else {
//        cout << dec(s, make_pair(s.size()-1, s.size()-1));
//    }
    return 0;
}
