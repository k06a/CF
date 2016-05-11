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

//

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
    
/*#ifndef ONLINE_JUDGE
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
#endif*/
    
    const double eps = 0.00000001;
    const int n = 5;
    
    vector<pair<int,int> > v(n);
    cin >> v;
    
    int indexes[] = {0,1,3,4,2};
    for (int i = 0; i < 120; i++) {
        
        bool allPositive = true;
        bool allNegative = true;
        double angleSum = 0;
        bool noneParallel = true;
        
        for (int j = 0; j < n; j++) {
            pair<int,int> p1 = v[indexes[(j+0)%n]];
            pair<int,int> p2 = v[indexes[(j+1)%n]];
            pair<int,int> p3 = v[indexes[(j+2)%n]];
            pair<int,int> p4 = v[indexes[(j+3)%n]];
            
            pair<int,int> v12(p2.first - p1.first, p2.second - p1.second);
            pair<int,int> v23(p3.first - p2.first, p3.second - p2.second);
            pair<int,int> v34(p4.first - p3.first, p4.second - p3.second);
            
            double cs = v12.first*v23.second - v12.second*v23.first;
            allPositive = allPositive && (cs > eps);
            allNegative = allNegative && (-cs > eps);
            double angle = acos((v12.first*v23.first + v12.second*v23.second)/sqrt(pow(v12.first,2)+pow(v12.second,2))/sqrt(pow(v23.first,2)+pow(v23.second,2)));
            angleSum += angle;
            
            double cs2 = v12.first*v34.second - v12.second*v34.first;
            noneParallel = noneParallel && (abs(cs2) > eps);
            
            if (!allPositive && !allNegative) {
                break;
            }
        }
        
        if ((allPositive || allNegative) && noneParallel &&
            ((angleSum >= 3*M_PI-eps && angleSum <= 3*M_PI+eps) ||
             (angleSum >= 2*M_PI-eps && angleSum <= 2*M_PI+eps))) {
            cout << "Yes";
            return 0;
        }
        
        /*cout << indexes[0] << indexes[1] << indexes[2] << indexes[3] << indexes[4] << ':'
             << allPositive << ' '
             << allNegative << ' '
             << noneParallel << ' '
             << angleSum << endl;*/
        next_permutation(&indexes[0], &indexes[n]);
    }
    
    cout << "No";
    return 0;
}
