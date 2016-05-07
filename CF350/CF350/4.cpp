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
    
    int64_t n, k;
    cin >> n >> k;
    vector<int64_t> va(n);
    vector<int64_t> vb(n);
    cin >> va >> vb;
    
    //
    
    vector<pair<int,double> > vk(n);
    for (int i = 0; i < n; i++) {
        vk[i] = make_pair(i, vb[i] * 1.0 / va[i]);
    }
    
    sort(vk.begin(), vk.end(), [](const pair<int,double> &p1, const pair<int,double> &p2) {
        return p1.second < p2.second;
    });
    
    int64_t height = vk[0].second;
    int64_t rowWeight = 0;
    for (int i = 0; i < n; i++) {
        int64_t index = vk[i].first;
        
        int64_t need = va[index] - vb[index]%va[index];
        int64_t h = ceil(vk[i].second) - height;
        if (need > 0 && need < va[index] && k >= need + h*rowWeight) {
            k -= need + h*rowWeight;
            height += h;
        } else if (vk[i].second < height) {
            height--;
            break;
        }
        rowWeight += va[index];
        
        int64_t needRows = (i + 1 < n) ? (vk[i+1].second - height) : k;
        int64_t haveRows = min(k/rowWeight, needRows);
        if (haveRows) {
            k -= haveRows*rowWeight;
            height += haveRows;
        }
    }
    
    cout << height;
    return 0;
}
