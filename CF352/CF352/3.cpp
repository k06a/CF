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
    
    int ax, ay, bx, by, tx, ty;
    cin >> ax >> ay >> bx >> by >> tx >> ty;
    
    int n;
    cin >> n;
    
    struct Point {
        double x;
        double y;
        double d;
    };
    
    vector<Point> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].x >> v[i].y;
        v[i].d = sqrt(pow(v[i].x - tx,2) + pow(v[i].y - ty,2));
    }
    
    int best_a = -1;
    int best_b = -1;
    double best_a_profit = -numeric_limits<double>::max();
    double best_b_profit = -numeric_limits<double>::max();
    for (int i = 0; i < n; i++) {
        double profit_a = v[i].d - sqrt(pow(v[i].x - ax,2) + pow(v[i].y - ay,2));
        if (profit_a > best_a_profit) {
            best_a_profit = profit_a;
            best_a = i;
        }
        
        double profit_b = v[i].d - sqrt(pow(v[i].x - bx,2) + pow(v[i].y - by,2));
        if (profit_b > best_b_profit) {
            best_b_profit = profit_b;
            best_b = i;
        }
    }
    
    if (best_a == best_b && best_a >= 0 && best_b >= 0) {
        int best_b_new = -1;
        double best_b_profit_new = -numeric_limits<double>::max();
        for (int i = 0; i < n; i++) {
            if (i == best_a) {
                continue;
            }
            
            double profit_b = v[i].d - sqrt(pow(v[i].x - bx,2) + pow(v[i].y - by,2));
            if (profit_b > best_b_profit_new) {
                best_b_profit_new = profit_b;
                best_b_new = i;
            }
        }
        
        int best_a_new = -1;
        double best_a_profit_new = -numeric_limits<double>::max();
        for (int i = 0; i < n; i++) {
            if (i == best_b) {
                continue;
            }
            
            double profit_a = v[i].d - sqrt(pow(v[i].x - ax,2) + pow(v[i].y - ay,2));
            if (profit_a > best_a_profit_new) {
                best_a_profit_new = profit_a;
                best_a_new = i;
            }
        }
        
        if (best_a_profit + best_b_profit_new > best_b_profit + best_a_profit_new) {
            best_b = best_b_new;
            best_b_profit = best_b_profit_new;
        }
        else {
            best_a = best_a_new;
            best_a_profit = best_a_profit_new;
        }
    }
    
    double sum = 0;
    
    if (best_a >= 0 && best_b >= 0 && best_a_profit < 0 && best_b_profit < 0) {
        sum -= max(best_a_profit, best_b_profit);
    }
    else {
        if (best_a >= 0) {
            sum -= best_a_profit;
        }
        if (best_b >= 0) {
            sum -= best_b_profit;
        }
    }
    
    for (int i = 0 ; i < n; i++) {
        sum += v[i].d*2;
    }
    
    printf("%.12f", sum);
    return 0;
}
