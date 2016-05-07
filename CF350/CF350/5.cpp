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
    
    int n, m, p;
    cin >> n >> m >> p;
    string s;
    s.resize(n);
    cin >> s;
    string cmd;
    cmd.resize(m);
    cin >> cmd;
    
    vector<int> closers(n);
    vector<int> stk(n);
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            stk[index] = i;
            index++;
        } else {
            index--;
            closers[i] = stk[index];
            closers[stk[index]] = i;
        }
    }
    
    vector<int> vl(n+2);
    vector<int> vr(n+2);
    for (int i = 0; i < n+2; i++) {
        vl[i] = i-1;
        vr[i] = i+1;
    }
    
    for (int i = 0; i < m; i++) {
        switch (cmd[i]) {
            case 'L':
                p = vl[p];
                break;
                
            case 'R':
                p = vr[p];
                break;
                
            case 'D': {
                int a = min(p-1, closers[p-1])+1;
                int b = max(p-1, closers[p-1])+1;
                vr[vl[a]] = vr[b];
                vl[vr[b]] = vl[a];
                p = (vr[b] <= n) ? vr[b] : vl[a];
                //cout << s << ' ' << p << endl;
                break;
            }
        }
    }
    
    string ans;
    for (int i = vr[0]; i <= n; i = vr[i]) {
        ans.push_back(s[i-1]);
    }
    
    cout << ans;
    return 0;
}
