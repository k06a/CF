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

struct Node {
    int64_t weight;
    int parent;
    map<int,int64_t> children;
    size_t children_count;
    bool done;
    
    Node() : weight(), parent(-1), children(), children_count(), done() {}
};

size_t count_elements(int index, vector<Node> &nodes) {
    size_t cnt = nodes[index].children.size();
    for (auto it = nodes[index].children.begin(),
             end = nodes[index].children.end(); it != end; ++it)
    {
        cnt += count_elements(it->first, nodes);
    }
    nodes[index].children_count = cnt;
    return cnt;
}

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
    
    vector<Node> nodes(n);
    for (int i = 0 ; i < n; i++) {
        cin >> nodes[i].weight;
    }
    
    for (int i = 1; i < n; i++) {
        int p, c;
        cin >> p >> c;
        p--;
        nodes[p].children[i] = c;
        nodes[i].parent = p;
    }
    
    // Fill children_count
    
    count_elements(0, nodes);
    
    // Algo
    
    int removed = 0;
    list<pair<int,list<int64_t> > > indexes;
    indexes.push_back(make_pair(0,list<int64_t>()));
    while (indexes.size() > 0) {
        int index = indexes.front().first;
        list<int64_t> &weightsOrig = indexes.front().second;
        
        
        for (auto it = nodes[index].children.begin(),
                 end = nodes[index].children.end(); it != end; ++it)
        {
            list<int64_t> weights = weightsOrig;
            weights.push_back((weights.size() ? weights.back() : 0) + it->second);
            
            bool flag = false;
            int64_t vichet = 0;
            for (auto wi = weights.begin(),
                 end = weights.end(); wi != end; ++wi)
            {
                int64_t maxWeight = weights.back();
                int64_t weight = maxWeight - vichet;
                if (weight > nodes[it->first].weight) {
                    flag = true;
                    break;
                }
                vichet += *wi;
            }
            
            if (flag) {
                removed += nodes[it->first].children_count + 1;
                continue;
            }
            
            if (!nodes[it->first].done) {
                indexes.push_back(make_pair(it->first, weights));
                nodes[it->first].done = true;
            }
        }
        
        indexes.erase(indexes.begin());
    }
    
    cout << removed;
    return 0;
}
