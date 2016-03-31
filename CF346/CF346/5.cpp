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

void main_file(string const &filename) {
#ifdef DEBUG
  ifstream cin(filename);
  if (!cin)
    return;
#endif

  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> vv(m);
  unordered_multimap<int, int> mm;
  for (int i = 0; i < m; i++) {
    cin >> vv[i].first >> vv[i].second;
    mm.insert(vv[i]);
    mm.insert(make_pair(vv[i].second, vv[i].first));
  }

  int less3 = 0;

  int found;
  do {
    found = 0;
    for (int i = 1; i <= n; i++) {
      if (mm.count(i) == 1) {
        int second = mm.find(i)->second;
        mm.erase(i);
        for (auto it = mm.find(second);
             it != mm.end() && it->first == second;) {
          if (it->second == i) {
            auto it2 = it;
            ++it;
            mm.erase(it2);
            i = second - 1;
          } else {
            ++it;
          }
        }
        if (mm.count(second) == 0) {
          less3++;
        }
        found++;
      }
    }
  } while (found);

  cout << less3;
}
