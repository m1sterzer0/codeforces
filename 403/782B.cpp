#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

struct person {
    int x; int v;
    friend bool operator<(person x, person y) { return (x.x < y.x) || (x.x == y.x && x.v < y.v); }
};

void eval(vector<person> &p, double meet, double &lefttime, double &righttime) {
    lefttime = 0.0;
    righttime = 0.0;
    for (auto pp : p) {
        if (pp.x < meet) {
            double t = (meet - pp.x) / pp.v;
            if (t > lefttime) { lefttime = t; }
        } else {
            double t = (pp.x - meet) / pp.v;
            if (t > righttime) { righttime = t; }
        }
    }
}

void solve() {
    int n;  cin >> n;
    vector<person> p(n);
    for (int i = 0; i < n; i++) { cin >> p[i].x; }
    for (int i = 0; i < n; i++) { cin >> p[i].v; }
    sort(p.begin(),p.end());
    double left = p.front().x;
    double right = p.back().x;
    if (left == right) { printf("%.8f\n",0.0); return; }
    double lefttime(0.0), righttime(1e9);
    while (righttime - lefttime > 1e-7 || lefttime - righttime > 1e-7) {
        double mid = 0.5*(left+right);
        eval(p,mid,lefttime,righttime);
        if (righttime > lefttime) { left = mid;  }
        else                      { right = mid; }
    }
    printf("%.8f\n",(lefttime+righttime)*0.5);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("782B.in1","r",stdin);
  solve();
  return 0;
}