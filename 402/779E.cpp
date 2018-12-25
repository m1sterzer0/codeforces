#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

struct recipe {
    int var;
    int atype;
    string val;
    int v1;
    int v2;
};

void parseRecords(vector<recipe> &rr, int n) {
    map<string,int> dict;
    int numdict = 1;
    dict["?"] = 0;
    string s1, buf;
    vector<string> s2;
    for (int i = 0; i < n; i++) {       
        getline(cin,s1);
        if (s1.size() < 6) { getline(cin,s1); } //Used for the first line
        s2.clear();
        stringstream ss(s1);
        while (ss >> buf) { s2.push_back(buf); }
        dict[s2[0]] = numdict; numdict++;
        rr[i].var = dict[s2[0]];
        if (s2.size() == 3) {
            rr[i].atype = 0;
            rr[i].val   = s2[2];
        } else {
            rr[i].v1  = dict[s2[2]];
            rr[i].v2  = dict[s2[4]];
            rr[i].atype = (s2[3] == "OR") ? 1 : (s2[3] == "AND") ? 2 : 3;
        }
    }
}

int evalRecipe(vector<recipe> &rr, int pos, bool in) {
    vector<bool> ee(rr.size()+1,false);
    ee[0] = in;
    int res = 0;
    bool temp;
    for (auto r : rr) {
        if (r.atype == 0) {              // Assignment
            temp = (r.val[pos] == '1');
        } else if (r.atype == 1) {       // OR
            temp =  ee[r.v1] || ee[r.v2];
        } else if (r.atype == 2) {       // AND
            temp =  ee[r.v1] && ee[r.v2];
        } else {                         // XOR
            temp = (ee[r.v1] != ee[r.v2]);
        }
        if (temp) { res += 1; }
        ee[r.var] = temp;
    }
    return res;
}


// Key is that the bits are independent from one another and do not interact
void solve() {
    int n,m;  cin >> n >> m;
    vector<recipe> rr(n);
    parseRecords(rr,n);
    string maxans = "";
    string minans = "";
    for (int i = 0; i < m; i++) {
        int a0 = evalRecipe(rr,i,false);
        int a1 = evalRecipe(rr,i,true);
        if (a0 < a1)      { minans += '0'; maxans += '1'; }
        else if (a1 < a0) { minans += '1'; maxans += '0'; }
        else              { minans += '0', maxans += '0'; }
    }
    cout << minans << endl;
    cout << maxans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("779C.in1","r",stdin);
  solve();
  return 0;
}