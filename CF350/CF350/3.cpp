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
    
    int n;
    cin >> n;
    vector<int> va(n);
    cin >> va;
    
    int m;
    cin >> m;
    vector<int> vb(m);
    vector<int> vc(m);
    cin >> vb >> vc;
    
    //
    
    unordered_map<int, int> langs;
    langs.reserve(n*2);
    for (int i = 0; i < n; i++) {
        langs[va[i]]++;
    }
    
    //
    
    auto langs_ = langs++;
    
    int max_i = 0;
    int max_listen = 0;
    int max_read = 0;
    for (int i = 0; i < m; i++) {
        int listen = langs_[vb[i]];
        int read = langs_[vc[i]];
        if (listen > max_listen || (listen == max_listen && read > max_read)) {
            max_listen = listen;
            max_read = read;
            max_i = i;
        }
    }
    
    cout << max_i+1;
    return 0;
}
