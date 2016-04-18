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
    
    int n;
    cin >> n;
    
    while (n--) {
        string line;
        cin >> line;
        
        string s = line.substr(line.find('\'') + 1);
        int64_t y = stoll(s);
        
        // 1: 198'9 - 199'8
        // 2: 19'99 - 20'98
        // 3: 2'099 - 3'098
        // 4: '3099 - 1'3098
        // 5: '13099 - '113098
        // 6: '113099 - '1113098
        // 7: '1113099 - '11113098
        // 8: '11113099 - '111113098
        // 9: '111113099 - '1111113098
        
        string ans = [&](){
            switch (s.size()) {
                case 1:
                    return (y >= 9) ? "198" : "199";
                case 2:
                    return (y >= 99) ? "19" : "20";
                case 3:
                    return (y >= 99) ? "2" : "3";
                case 4:
                    return (y >= 3099) ? "" : "1";
                case 5:
                    return (y >= 13099) ? "" : "1";
                case 6:
                    return (y >= 113099) ? "" : "1";
                case 7:
                    return (y >= 1113099) ? "" : "1";
                case 8:
                    return (y >= 11113099) ? "" : "1";
                case 9:
                    return (y >= 111113099) ? "" : "1";
                default:
                    return  "";
            }
        }();
        cout << ans << s << endl;
    }
}
