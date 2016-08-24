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
struct MapSmartAccessorWrapper {
    const T *m;

    MapSmartAccessorWrapper(T *m = NULL)
        : m(m) {
    }
    typename T::mapped_type operator[](const typename T::key_type &key) const {
        auto it = m->find(key);
        if (it == m->end()) {
            typedef typename T::mapped_type mapped_type;
            return mapped_type();
        }
        return it->second;
    }
};

template <typename TKey, typename TValue>
MapSmartAccessorWrapper<map<TKey, TValue>> operator++(const map<TKey, TValue> &m, int i) {
    static MapSmartAccessorWrapper<map<TKey, TValue>> accessor;
    accessor.m = &m;
    return accessor;
}

template <typename TKey, typename TValue>
MapSmartAccessorWrapper<unordered_map<TKey, TValue>> operator++(unordered_map<TKey, TValue> &m, int i) {
    static MapSmartAccessorWrapper<unordered_map<TKey, TValue>> accessor;
    accessor.m = &m;
    return accessor;
}

//

struct Result {
    int a00, a01, a10, a11;
    int r0, r1, r2;
    bool fail;

    Result(bool fail = false,
           int a00 = 0, int a01 = 0, int a10 = 0, int a11 = 0,
           int r0 = 0, int r1 = 0, int r2 = 0)
        : a00(a00), a01(a01), a10(a10), a11(a11), r0(r0), r1(r1), r2(r2), fail(fail) {
    }
};

map<int, map<int, map<int, map<int, Result *>>>> buff;

Result f(int a00, int a01, int a10, int a11,
         int r0, int r1, int r2) {

    Result *buffered = buff++ [a00]++ [a01]++ [a10]++ [a11];
    if (buffered) {
        return *buffered;
    }

    if (a00 < 0 || a01 < 0 || a10 < 0 || a11 < 0) {
        return true;
    }

    Result res1;
    if (a01 || a10 || a11) {
        res1 = f(a00, a01 - r0, a10 - r2, a11 - r1, r0, r1 + 1, r2);
    }

    if (a11 && !res1.fail) {
        return buff[a00][a01][a10][a11] = new Result(res1);
    }

    if (a01) {
        if (!res1.fail) {
            return buff[a00][a01][a10][a11] = new Result(res1);
        }
        return buff[a00][a01][a10][a11] = new Result(f(a00 - r0 - r2, a01 - r1, a10, a11, r0 + 1, r1, r2));
    }

    if (a10) {
        if (!res1.fail) {
            return buff[a00][a01][a10][a11] = new Result(res1);
        }
        return buff[a00][a01][a10][a11] = new Result(f(a00 - r0 - r2, a01, a10 - r1, a11, r0, r1, r2 + 1));
    }

    if (a00) {
        Result res0 = f(a00 - r0 - r2, a01 - r1, a10, a11, r0 + 1, r1, r2);
        if (!res0.fail) {
            return buff[a00][a01][a10][a11] = new Result(res0);
        }
        Result res2 = f(a00 - r0 - r2, a01, a10 - r1, a11, r0, r1, r2 + 1);
        if (!res2.fail) {
            return buff[a00][a01][a10][a11] = new Result(res2);
        }
    }

    return Result(!(a00 == 0 && a01 == 0 && a10 == 0 && a11 == 0),
                  a00, a01, a10, a11, r0, r1, r2);
}

//

int main_file(string const &filename);

int main(int argc, const char *argv[]) {
    ios_base::sync_with_stdio(false);

#ifndef ONLINE_JUDGE
    string base = __FILE__;
    base.replace(base.length() - 3, 3, "txt");
    for (int i = 0; i < 10; i++) {
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

    int a00, a01, a10, a11;
    cin >> a00 >> a01 >> a10 >> a11;

    int r0 = 0;
    int r1 = 0;
    int r2 = 0;

    if (a01 && r0 == 0) {
        r0++;
    }
    if (a10 && r2 == 0) {
        r2++;
        if (r0) {
            a00--;
        }
    }

    if (!a00 && !a01 && !a10 && !a11) {
        cout << 0;
        return 0;
    }

    Result res = f(a00, a01, a10, a11, r0, r1, r2);
    if (res.fail) {
        cout << "Impossible";
        return 0;
    }

    for (int i = 0; i < res.r0; i++) {
        cout << 0;
    }
    for (int i = 0; i < res.r1; i++) {
        cout << 1;
    }
    for (int i = 0; i < res.r2; i++) {
        cout << 0;
    }
    return 0;
}
