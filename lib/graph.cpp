#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;
#define PB push_back  
#define MP make_pair  
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  
#define REPE(i,n) FORE(i,0,n)  
#define FORSZ(i,a,v) FOR(i,a,SZ(v))  
#define REPSZ(i,v) REP(i,SZ(v)) 



struct unweightedGraph {
    vector<vector<ll>> adj;


};

struct edge { ll v1; ll v2; ll w; };
struct weightedGraph {
    ll minn; ll maxn;
    vector<vector<edge>> adj;

    // E log e version of dijkstra
    void dijkstra(ll start, vector<ll> &ans) {
        vector<bool> visited;
        ans.assign(maxn+1,infll);
        priority_queue<pair<ll,ll>> pq;
        visited.assign(maxn+1,false);
        pq.push({0,start});
        while (!pq.empty()) {
            ll d  = pq.top().first;
            ll nn = pq.top().second;
            if (visited[nn]) continue;
            visited[nn] = true;
            ans[nn] = d;
            for (auto e : adj[nn]) {
                if (visited[e.v2]) continue;
                pq.push({d+e.w, e.v2});
            }
        }
    }

    void bellmanFord(ll start, vector<ll> &ans) {
        vector<edge> edges;
        for (ll nn = minn; nn <= maxn; nn++) {
            for (auto e : adj[nn]) { edges.push_back(e); }
        }
        ans.assign(maxn+1,infll);
        ans[start] = 0LL;
        for (ll v = minn; v <= maxn; v++) {
            for (auto e : edges) {
                if (ans[e.v1] == infll) continue;
                ans[e.v2] = min(ans[e.v2],ans[e.v1]+e.w);
            }
        }
    }

    void bellmanFord2(ll start, vector<ll> &ans, vector<ll> &pred, bool &negCycle) {
        vector<edge> edges;
        for (ll nn = minn; nn <= maxn; nn++) {
            for (auto e : adj[nn]) { edges.push_back(e); }
        }
        ans.assign(maxn+1,infll);
        pred.assign(maxn+1,minn-1);
        ans[start] = 0LL;
        for (ll v = minn; v <= maxn; v++) {
            for (auto e : edges) {
                if (ans[e.v1] == infll) continue;
                ll d2 = ans[e.v1] + e.w;
                if (d2 < ans[e.v2]) { ans[e.v2] = d2; pred[e.v2] = e.v1; }
            }
        }
        negCycle = false;
        for (auto e : edges) {
            if (ans[e.v1] + e.w < ans[e.v2]) negCycle = true;
        }
    }

    void floydWarshall(vector<vector<ll>> &ans) {
        ans.resize(maxn+1);
        for (ll i = minn; i <= maxn; i++) {
            ans[i].assign(maxn+1,infll);
        }

        for (ll nn = minn; nn <= maxn; nn++) {
            for (auto e : adj[nn]) {
                ans[nn][e.v2] = min(ans[nn][e.v2], e.w);
            }
        }

        for (ll k = minn; k <= maxn; k++) {
            for (ll i = minn; i <= maxn; i++) {
                if (ans[i][k] == infll) continue;
                for (ll j = minn; j <= maxn; j++) {
                    if (ans[k][j] == infll) continue;
                    ans[i][j] = min(ans[i][j], ans[i][k] + ans[k][j]);
                }
            }
        }
    }
};