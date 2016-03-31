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

  int n;
  cin >> n;

#define x first
#define y second

  vector<pair<int, int>> mm(n);
  for (int i = 0; i < n; i++) {
    cin >> mm[i].x >> mm[i].y;
  }

  vector<pair<int, int>> vv(n);
  for (int i = 0; i < n; i++) {
    vv[i].x = mm[(i + 1) % n].x - mm[i].x;
    vv[i].y = mm[(i + 1) % n].y - mm[i].y;
  }

  int k = 0;
  for (int i = 0; i < n; i++) {
    k += ((vv[i].y > 0 && vv[(i + 1) % n].x < 0) ||
          (vv[i].x < 0 && vv[(i + 1) % n].y < 0) ||
          (vv[i].y < 0 && vv[(i + 1) % n].x > 0) ||
          (vv[i].x > 0 && vv[(i + 1) % n].y > 0));
  }

  cout << k;
}
