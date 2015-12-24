#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <map>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, const char * argv[])
{
    //fstream cin("/Users/k06a/Projects/CF336/CF336/1.txt");
    
    string a, b;
    cin >> a >> b;
    
    vector<int> a1(a.length());
    for (int i = 0; i < a.length(); i++) {
        a1[i] = (a[i] == '1'?1:0) + (i?(a1[i-1]):0);
    }
    
    vector<int> b1(b.length());
    for (int i = 0; i < b.length(); i++) {
        b1[i] = (b[i] == '1'?1:0) + (i?(b1[i-1]):0);
    }
    
    int64_t sum = 0;
    for (size_t i = 0; i < a.length(); i++) {
        size_t j = b.length()-a.length()+i;
        size_t x1 = b1[j] - (i?b1[i-1]:0);
        if (a[i] == '0') {
            sum += x1;
        } else {
            sum += (j-(i-1))-x1;
        }
    }
    
    cout << sum;
}
