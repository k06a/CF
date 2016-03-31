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

  vector<multimap<int, string>> vv(m);

  for (int i = 0; i < n; i++) {
    string name;
    int region, value;
    cin >> name >> region >> value;
    vv[region - 1].insert(make_pair(value, name));
  }

  for (int i = 0; i < m; i++) {
    auto it = vv[i].rbegin();
    int v2 = (++it)->first;
    if (vv[i].size() > 2 && (++it)->first == v2) {
      cout << "?" << endl;
      continue;
    }
    it = vv[i].rbegin();
    cout << vv[i].rbegin()->second << " " << (++it)->second << endl;
  }
}
