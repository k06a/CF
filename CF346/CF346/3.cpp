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

  set<int> s;
  for (int i = 0; i < n; i++) {
    int b;
    cin >> b;
    s.insert(b);
  }

  vector<int> ans;
  int sum = 0;
  int prev = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    for (int i = prev + 1; i < *it; ++i) {
      if (sum + i > m) {
        goto end;
      }
      sum += i;
      ans.push_back(i);
    }
    prev = *it;
  }
  for (int i = *s.rbegin()+1; sum + i <= m; i++) {
    sum += i;
    ans.push_back(i);
  }
end:
  
  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << ' ';
  }
}
