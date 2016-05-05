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
    
    string s;
    getline(cin, s);
    s = s.substr(5);
    int n = (int)s.length();
    
    int *ab = new int [n];
    int *abc = new int [n];
    for (int i = 0; i < n-1; i++) {
        ab[i] = (s[i]-'a')*26 + (s[i+1]-'a');
        if (i < n-2) {
            abc[i] = ab[i]*26 + (s[i+2]-'a');
        }
    }
    
    bool *sss2 = new bool [26*26];
    bool *sss3 = new bool [26*26*26];
    bool *ss2 = new bool [26*26];
    bool *ss3 = new bool [26*26*26];
    fill(sss2, sss2+26*26, false);
    fill(sss3, sss3+26*26*26, false);
    fill(ss2, ss2+26*26, false);
    fill(ss3, ss3+26*26*26, false);
    vector<pair<int,int> > v;
    v.reserve(10000);
    int i = n;
    int removed2 = 0;
    int removed3 = 0;
    bool flag;
    do {
        flag = false;
        if (!removed2 && i > 1 && ss2[ab[i-2]] == false) {
            v.push_back(make_pair(i-2,2));
            ss2[ab[i-2]] = true;
            sss2[ab[i-2]] = true;
            i -= 2;
            removed3--;
            flag = true;
        } else if (!removed3 && i > 2 && ss3[abc[i-3]] == false) {
            v.push_back(make_pair(i-3,3));
            ss3[abc[i-3]] = true;
            sss3[abc[i-3]] = true;
            i -= 3;
            removed2--;
            flag = true;
        } /*else if (v.size() && i+v.back().second > 2 && v.back().second == 2 && ss3[abc[i+2-3]] == false) {
            if (v.back().second == 2) {
                ss2[ab[v.back().first]] = false;
            } else {
                ss3[abc[v.back().first]] = false;
            }
            i += v.back().second;
            v.pop_back();
            v.push_back(make_pair(i-3,3));
            ss3[abc[i-3]] = true;
            sss3[abc[i-3]] = true;
            i -= 3;
            needChange = false;
        }*/ else if (v.size()) {
            if (v.back().second == 2) {
                ss2[ab[v.back().first]] = false;
                removed2++;
            } else {
                ss3[abc[v.back().first]] = false;
                removed3++;
            }
            i += v.back().second;
            v.pop_back();
            flag = true;
        }
    }
    while (flag);
    
    vector<string> result;
    char str2[3] = {0};
    for (int i = 0; i < 26*26; i++) {
        if (sss2[i]) {
            str2[0] = i/26+'a';
            str2[1] = i%26+'a';
            result.push_back(str2);
        }
    }
    char str3[4] = {0};
    for (int i = 0; i < 26*26*26; i++) {
        if (sss3[i]) {
            str3[0] = i/26/26+'a';
            str3[1] = i/26%26+'a';
            str3[2] = i%26+'a';
            result.push_back(str3);
        }
    }
    
    sort(result.begin(), result.end());
    
    cout << result.size() << endl;
    for (auto it = result.begin(); it != result.end(); ++it) {
        cout << *it << endl;
    }
}
