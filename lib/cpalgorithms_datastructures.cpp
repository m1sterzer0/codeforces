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

//////////////////////////////////////////////////
//
// SECTION A: FUNDAMENTALS
//
//////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// SUBSECTION A1: MINIMUM STACK/MINIMUM QUEUE
// https://cp-algorithms.com/data_structures/stack_queue_modification.html
////////////////////////////////////////////////////////////

// * The idea here is to augment the stack and queue structures so that
//   we can still access elements as before, but now we can also access the minimum
//   element within the data structure.
//
// * The stack modification is easy -- here we just need to store both the element and the minimum when we pop each element on.

struct minStack {
    stack<pair<ll,ll>> st;
    bool empty() { return st.empty(); }
    size_t size() { return st.size(); }
    ll top() { return st.top().first; }
    ll minimum() {
        if (st.empty()) return LONG_LONG_MAX; 
        return st.top().second;
    }
    void push(ll x) { 
        if (st.empty()) st.push({x,x});
        else {
            ll minEle = st.top().second;
            if (x < minEle) minEle = x;
            st.push({x,minEle});
        }
    }
    void pop() { st.pop(); }
};

// The page goes on to describe some incomplete data structures that allow us to access the min but NOT the elements.
// The third option, though, gives us a full featured minQueue implemented as 2 minStacks.  This one we code below.

struct minQueue {
    minStack st1;
    minStack st2;
    bool empty() { return st1.empty() && st2.empty(); }
    size_t size() { return st1.size() + st2.size(); }
    ll top() {
        if (st2.empty()) copyover();
        return st2.top();
    }
    ll minimum() { return min(st1.minimum(),st2.minimum()); }
    void push(ll x) { st1.push(x); }
    void pop() {
        if (st2.empty()) copyover();
        st2.pop();
    }
    void copyover() {
        while (!st1.empty()) {
            ll x = st1.top();
            st1.pop();
            st2.push(x);
        }
    }
};

// Clearly, the minQueue can be used to find the maximum subarray minimum for a fixed length.


////////////////////////////////////////////////////////////
// SUBSECTION A2: SPARSE TABLE
// https://cp-algorithms.com/data_structures/stack_queue_modification.html
////////////////////////////////////////////////////////////

// This works on immutable data.
// Idea is that we will store the answers for all subarrays of length 2^k.
// For associative queries, we get O(log n) access time (not great)
// However, for idempotent queries (queries of functions where f(x,x) = x -- min() and max() are key examples), we can do the query in O(1).

struct sparseTableMin {
    ll n; ll k;
    vector<vector<ll>> st;
    vector<ll> mylog;
    sparseTableMin(vector<ll> &a) { init(a); }
    void init(vector<ll> &a) {
        n = a.size();
        k = 1; ll ks = 1;
        while (n > ks) { k++; ks *= 2; }

        st.resize(n);
        REP(i,n) st[i].assign(k,0LL);
        REP(i,n) st[i][0] = a[i];
        ll offset = 1;
        FOR(j,1,k) {
            for (ll i = 0; i+offset < n; i++) { st[i][j] = min(st[i][j-1],st[i+offset][j-1]); }
            offset *= 2;
        }

        mylog.assign(n+1,0LL);
        mylog[1] = 0;
        FORE(i,2,n) mylog[i] = 1LL + mylog[i/2];
    }

    ll rmq(ll l, ll r) {
        ll j = mylog[r-l+1];
        ll minimum = min(st[l][j], st[r-(1<<j)+1][j]);
        return minimum;
    }
};

// The key drawback is that this only really works for idempotent functions.  For associative functions, we need a more complex data structure.  Two examples
// * Disjoint Sparse Table (https://discuss.codechef.com/questions/117696/tutorial-disjoint-sparse-table)
// * Sqrt Tree (https://cp-algorithms.com/data_structures/sqrt-tree.html) -- covered below.



//////////////////////////////////////////////////
//
// SECTION B: TREES
//
//////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// SUBSECTION B1: Disjoint Set Union
// https://cp-algorithms.com/data_structures/disjoint_set_union.html
////////////////////////////////////////////////////////////

// Operations we want to support:
// * addSet(v)  -- creates a one element set with element v
// * join(u,v) -- takes 
// * find(u)    -- finds the "name" or "leader" of the set containing u.
// Union find can do this in "almost constant" time (Inverse ackerman function)

struct unionFind {
    vector<ll> parent;
    vector<ll> nodeSize;
    vector<ll> scratch;

    void addSet(ll v) {
        if (parent.size() <= v+1) { parent.resize(v+1,-1LL); nodeSize.resize(v+1,0LL); }
        parent[v] = v; nodeSize[v] = 1;
    }

    ll find(ll v) {
        while (v != parent[v]) { scratch.push_back(v); v = parent[v]; }
        for (auto s : scratch) parent[s] = v;
        scratch.clear();
        return v;
    }

    ll size(ll v) {
        ll u = find(v);
        return nodeSize[u];
    }

    void join(ll u, ll v) {
        u = find(u);
        v = find(v);
        if (u == v) return;
        if (nodeSize[u] < nodeSize[v]) swap(u,v);
        parent[v] = u;
        nodeSize[u] += nodeSize[v];
        nodeSize[v] = 0; // Not necessary, but helps to have a way to find if a node is a parent.
    } 
};

// APPLICATIONS:
// * Connected components in a graph (very straightforward -- add the vertices and join the edges)
// * Connected components in an image -- can optimize and process this a row at a time to save memory
// * You can store additional information for each set and aggregate with unions
//   Example: painting subarrays with colors, and wanting to find the final color of each cell.
//        We reverse queries and color cells.  When we color cell, we change the parent to point to the
//        cell to the right.  We also store side information of the leftmost uncolored cell from our cell
//        on to the right.  See below for code.

struct unionFindPaintingSubarray {
    ll L;
    vector<vector<ll>> query;
    vector<ll> parent;
    vector<ll> answer;
    vector<ll> scratch;
    vector<ll> nextUncolored; //NEW
    vector<ll> nodeSize;

    void doit() {
        parent.assign(L+1,0LL);
        answer.assign(L+1,0LL);        
        nextUncolored.assign(L+1,0LL); 
        nodeSize.assign(L+1,1LL);
        REP(i,L) { 
            parent[i] = i; 
            nextUncolored[i] = i;
        }

        for (ll i = (ll) query.size()-1; i >= 0; i--) {
            ll l,r,c;
            l = query[i][0];
            r = query[i][1];
            c = query[i][2];
            for (ll v = nextUncolored[find(l)]; v <= r; v = nextUncolored[find(v)]) { 
                answer[v] = c;
                join(v,v+1);
            }
        }
    }

    ll find(ll v) {
        while (v != parent[v]) { scratch.push_back(v); v = parent[v]; }
        for (auto s : scratch) parent[s] = v;
        scratch.clear();
        return v;
    }

    void join(ll u, ll v) {
        u = find(u);
        v = find(v);
        if (u == v) return;
        if (nodeSize[u] < nodeSize[v]) swap(u,v);
        parent[v] = u;
        nodeSize[u] += nodeSize[v];
        nextUncolored[u] = max(nextUncolored[v],nextUncolored[u]); //NEW
        nodeSize[v] = 0; // Not necessary, but helps to have a way to find if a node is a parent.
    } 
};

// * Support distance up to representative (see web page for details)
// * Computing the parity of the paths to the leader. (see web page for details)


// * Offline RMQ in O(alpha(n)) // Arpa's Trick
//   -- Read all the queries and sort the queries by the R.
//   -- Use a unionFind stucture and a stack to give the min as a function of L.

struct unionFindRMQQuery { ll L; ll R; ll idx; };
bool operator< (const unionFindRMQQuery &a, const unionFindRMQQuery &b) { return a.R < b.R; }
struct unionFindRMQ {
    vector<ll> parent;
    vector<ll> nodeSize;
    vector<ll> scratch;
    vector<ll> minVal;

    void doit(vector<ll> &a, deque<unionFindRMQQuery> &q, vector<ll> &ans) {
        stack<ll> s;
        ll n = (ll) a.size();
        minVal.assign(n,LONG_LONG_MAX);
        parent.assign(n,0);
        nodeSize.assign(n,1);
        ans.resize(q.size());
        sort(q.begin(),q.end());
        reverse(q.begin(),q.end());
        REP(i,n) {
            parent[i] = i;
            while (!s.empty() && a[i] < a[s.top()]) {
                join(i,s.top());
                minVal[find(i)] = a[i];
                s.pop();
            }
            s.push(i);
            while (!q.empty() && q.back().R == i) {
                ans[q.back().idx] = minVal[find(q.back().L)];
                q.pop_back();
            }
        }
    }

    ll find(ll v) {
        while (v != parent[v]) { scratch.push_back(v); v = parent[v]; }
        for (auto s : scratch) parent[s] = v;
        scratch.clear();
        return v;
    }

    void join(ll u, ll v) {
        u = find(u);
        v = find(v);
        if (u == v) return;
        if (nodeSize[u] < nodeSize[v]) swap(u,v);
        parent[v] = u;
        nodeSize[u] += nodeSize[v];
        nodeSize[v] = 0; // Not necessary, but helps to have a way to find if a node is a parent.
    } 
};

// * Offline LCA in O(alpha(n)) on average (in an upcoming session)
// * Storing the DSU explicityly in a set list (see the web page)
// * Storing the DSU by maintaining a clear tree structure / Online bridge finding in O(alpha(n)) on average (see the web page)

////////////////////////////////////////////////////////////
// SUBSECTION B2: Fenwick Tree
// https://cp-algorithms.com/data_structures/fenwick.html
////////////////////////////////////////////////////////////

// One-index BIT array
struct BIT1 {
    ll n;
    vector<ll> arr;
    BIT1(ll nin) { n = nin; arr.assign(n+1,0LL); }
    void add(ll x, ll v) {
        for (ll xx = x; xx <= n; xx += (xx & -xx)) arr[xx] += v;
    }
    ll query(ll x) {
        ll ans = 0;
        for (ll xx = x; xx > 0; xx -= (xx & -xx)) ans += arr[xx];
        return ans;
    }
    ll query(ll l, ll r) { return query(r) - query(l-1);  }
};

// Zero-indexed BIT array -- just add one internally
struct BIT0 {
    ll n;
    vector<ll> arr;
    BIT0(ll nin) { n = nin; arr.assign(n+1,0LL); }
    void add(ll x, ll v) {
        for (ll xx = x+1; xx <= n; xx += (xx & -xx)) arr[xx] += v;
    }
    ll query(ll x) {
        ll ans = 0;
        for (ll xx = x+1; xx > 0; xx -= (xx & -xx)) ans += arr[xx];
        return ans;
    }
    ll query(ll l, ll r) { return query(r) - query(l-1);  }
};

// 2-D One-index BIT
struct BIT12D {
    ll n; ll m;
    vector<vector<ll>> arr;

    BIT12D(ll nin, ll min) {
        n = nin;
        m = min;
        arr.resize(n+1);
        FORE(i,0,n) { arr[i].assign(m+1,0LL); }
    } 

    // Updates all rectangles from x,y to n,m with value (add or xor both work)
    void add(ll x, ll y, ll v) {
        for (ll xx = x; xx <= n; xx += (xx & -xx)) {
            for (ll yy = y; yy <= m; yy += (yy & -yy)) {
                arr[xx][yy] += v;
            }
        }
        return;
    }

    ll query(ll x, ll y) {
        ll ans = 0;
        for (ll xx = x; xx > 0; xx -= (xx & -xx)) {
            for (ll yy = y; yy > 0; yy -= (yy & -yy)) {
                ans += arr[xx][yy];
            }
        }
        return ans;
    }
};

// Point updates and range queries -- regular BIT
// Range updates and point queries
//    If you want to increment [l,r] by m, do an add(l,m) and add(r+1,-m) and do queries as normal.
// Range updates and range queries

struct BIT1RANGE {
    ll n;
    vector<ll> arr1;
    vector<ll> arr2;
    BIT1RANGE(ll nin) { n = nin; arr1.assign(n+1,0LL); arr2.assign(n+1,0LL); }
    void add(ll l, ll r, ll v) {
        ll v2 = v * (l-1);
        ll v3 = v * r;
        for (ll xx = l;   xx <= n; xx += (xx & -xx)) { arr1[xx] += v; arr2[xx] += v2; }
        for (ll xx = r+1; xx <= n; xx += (xx & -xx)) { arr1[xx] -= v; arr2[xx] -= v3; }
    }

    ll query(ll x) {
        ll q1 = 0;
        ll q2 = 0;
        for (ll xx = x; xx > 0; xx -= (xx & -xx)) { q1 += arr1[xx]; q2 += arr2[xx]; }
        return q1 * x - q2;
    }

    ll query(ll l, ll r) { return query(r) - query(l-1);  }
};


////////////////////////////////////////////////////////////
// SUBSECTION B3: Sqrt Decomposition
// https://cp-algorithms.com/data_structures/sqrt_decomposition.html
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// SUBSECTION B4: Segment Tree
// https://cp-algorithms.com/data_structures/segment_tree.html
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// SUBSECTION B5: Treap
// https://cp-algorithms.com/data_structures/treap.html
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// SUBSECTION B6: Sqrt Tree
// https://cp-algorithms.com/data_structures/sqrt-tree.html
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// SUBSECTION B7: Randomized Heap
// https://cp-algorithms.com/data_structures/randomized_heap.html
////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
//
// SECTION C: ADVANCED
//
//////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// SUBSECTION C1: Deleting from a data structure in O(T(n)logn)
// https://cp-algorithms.com/data_structures/deleting_in_log_n.html
////////////////////////////////////////////////////////////




int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    return 0;
}
