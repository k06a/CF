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

void main_file(string const& filename);

int main(int argc, const char * argv[])
{
#ifdef DEBUG
    string base = __FILE__;
    base.replace(base.length()-3, 3, "txt");
    for (int i = 0; i < 3; i++) {
        string filename = base;
        filename.insert(filename.length()-4, 1, 'a'+i);
        main_file(filename);
        cout << endl;
    }
#else
    main_file("");
#endif
}

void main_file(string const& filename)
{
#ifdef DEBUG
    ifstream cin(filename);
    if (!cin)
        return;
#endif
    
    int n, m, p;
    cin >> n >> m >> p;
    string s;
    cin >> s;
    string cmd;
    cin >> cmd;
    
    unordered_map<int,int> closers;
    vector<int> mas(n);
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            mas[index] = i;
            index++;
        } else {
            index--;
            closers[i] = mas[index];
            closers[mas[index]] = i;
        }
    }
    
    for (int i = 0; i < m; i++) {
        switch (cmd[i]) {
            case 'L':
                p--;
                break;
                
            case 'R':
                p++;
                break;
                
            case 'D': {
                switch (s[p]) {
                    case '(':
                        s.erase(s.begin()+p, s.begin()+closers[p]+1);
                        break;
                    case ')':
                        s.erase(s.begin()+closers[p], s.begin()+p+1);
                        break;
                }
                cout << s << ' ' << p << endl;
                break;
            }
        }
        
        p = max(0,min((int)s.size()-1,p));
    }
    
    cout << s;
}
