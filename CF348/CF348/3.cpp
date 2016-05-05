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

void shift_row(vector<vector<int> > &vv, int n, int m, int r) {
    int tmp = vv[r][m-1];
    for (int i = m-1; i >= 1; i--) {
        vv[r][i] = vv[r][i-1];
    }
    vv[r][0] = tmp;
}

void shift_column(vector<vector<int> > &vv, int n, int m, int c) {
    int tmp = vv[n-1][c];
    for (int i = n-1; i >= 1; i--) {
        vv[i][c] = vv[i-1][c];
    }
    vv[0][c] = tmp;
}

void main_file(string const& filename)
{
#ifdef DEBUG
    ifstream cin(filename);
    if (!cin)
        return;
#endif
    
    int n, m, q;
    cin >> n >> m >> q;
    
    vector<vector<int> > vv(n);
    for (int i = 0; i < n; i++) {
        vv[i].resize(m);
    }
    
    string endl_;
    getline(cin, endl_);
    
    vector<string> vs(q);
    for (int i = q-1; i >= 0; i--) {
        getline(cin, vs[i]);
    }
    
    for (int i = 0; i < q; i++) {
        stringstream ss(vs[i]);
        
        int t, r, c, x;
        ss >> t;
        
        switch (t) {
            case 1:
                ss >> r;
                shift_row(vv, n, m, r-1);
                break;
            
            case 2:
                ss >> c;
                shift_column(vv, n, m, c-1);
                break;
                
            case 3:
                ss >> r >> c >> x;
                vv[r-1][c-1] = x;
                break;
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j)
                cout << ' ';
            cout << vv[i][j];
        }
        cout << endl;
    }
}
