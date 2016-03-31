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

void main_file(string const &filename);

int main(int argc, const char *argv[]) {
#ifdef DEBUG
  string base = __FILE__;
  base.replace(base.length() - 3, 3, "txt");
  for (int i = 0; i < 3; i++) {
    string filename = base;
    filename.insert(filename.length() - 4, 1, 'a' + i);
    main_file(filename);
    cout << endl;
  }
#else
  main_file("");
#endif
}

pair<int, int> get_any(vector<vector<int>> &vv) {
  for (int i = 0; i < vv.size(); i++) {
    for (int j = 0; j < vv[i].size(); j++) {
      if (vv[i][j]) {
        return make_pair(i, j);
      }
    }
  }
  return make_pair(-1, -1);
}

void main_file(string const &filename) {
#ifdef DEBUG
  ifstream cin(filename);
  if (!cin)
    return;
#endif

#define x first
#define y second

  int n, m, k;
  cin >> n >> m >> k;

  vector<vector<int>> vv(n);
  for (int i = 0; i < n; i++) {
    vv[i].resize(m);
    for (int j = 0; j < m; j++) {
      cin >> vv[i][j];
    }
  }

  while (true) {
    pair<int, int> any = get_any(vv);
    if (any.x < 0 && any.y < 0) {
      break;
    }

    vector<vector<int>> ll(n);
    for (int i = 0; i < n; i++) {
      ll[i].resize(m);
    }
    set<pair<int, int>> q;
    q.insert(any);
    int count = 0;
    while (q.size()) {
      pair<int, int> p = *q.begin();
      q.erase(q.begin());
      count++;
      if (vv[p.x][p.y] && !ll[p.x][p.y]) {
        ll[p.x][p.y] = vv[p.x][p.y];
        vv[p.x][p.y] = 0;

        if (p.x > 0 && vv[p.x - 1][p.y]) {
          q.insert(make_pair(p.x - 1, p.y));
        }
        if (p.y > 0 && vv[p.x][p.y - 1]) {
          q.insert(make_pair(p.x, p.y - 1));
        }
        if (p.x < n - 1 && vv[p.x + 1][p.y]) {
          q.insert(make_pair(p.x + 1, p.y));
        }
        if (p.y < m - 1 && vv[p.x][p.y + 1]) {
          q.insert(make_pair(p.x, p.y + 1));
        }
      }
    }

    int minus = 0;
    while (k % (count - minus)) {
      minus++;
    }
    count -= minus;

    int countLessK = 0;
    bool existExactK = false;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        countLessK += (ll[i][j] < (k / count));
        existExactK = existExactK || (ll[i][j] == (k / count));
      }
    }
    if (countLessK > minus || !existExactK) {
      continue;
    }

    cout << "YES" << endl;
    for (int t = 0; t < minus - countLessK; t++) {
      any = get_any(ll);
      ll[any.x][any.y] = 0;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (ll[i][j] >= k / count) {
          cout << (k / count) << ' ';
        } else {
          cout << 0 << ' ';
        }
      }
      cout << endl;
    }
    return;
  }

  cout << "NO";
}
