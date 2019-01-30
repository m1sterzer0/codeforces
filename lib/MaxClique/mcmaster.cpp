#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

struct MC {
    ll nmin;
    ll nmax;
    vector<vector<bool>> adjm;
    vector<ll> Cbest;

    void search(ll nminIn, ll nmaxIn, vector<vector<ll>> &adj, vector<ll> &sol) {
        nmin = nminIn;
        nmax = nmaxIn;
        adjm.resize(nmax+1);
        for (ll i = nmin; i <= nmax; i++) { adjm[i].assign(nmax+1,false); }
        for (ll i = nmin; i <= nmax; i++) {
            for (auto j : adj[i]) { adjm[i][j] = true; adjm[j][i] = true; }
        }
        vector<ll> C;
        vector<ll> P;
        Cbest.clear();
        for (ll i = nmin; i <= nmax; i++) P.push_back(i);
        expand(C,P);
        sol = Cbest;
    }

    void expand(vector<ll> &C, vector<ll> &P) {
        while (!P.empty()) {
            if (C.size() + P.size() <= Cbest.size()) return;
            ll v = P.back();
            C.push_back(v);
            if (C.size() > Cbest.size()) { Cbest = C; }
            vector<ll> newP;
            newP.reserve(P.size());
            for (auto p : P) { if (adjm[v][p]) newP.push_back(p); }
            if (!newP.empty()) expand(C,newP);
            C.pop_back();
            P.pop_back();
        }
    }
};

struct MCQVertex { ll idx; ll deg; };
bool operator<(const MCQVertex &a, const MCQVertex &b) {
    return (a.deg > b.deg) || 
           (a.deg == b.deg && a.idx < b.idx);
 }

struct MCQ {
    ll n;
    vector<vector<bool>> adjm;
    vector<vector<ll>>   adjl;
    vector<ll> Q;
    vector<ll> Qmax;
    vector<ll> old2new;
    vector<ll> new2old;
    vector<vector<ll>> C; // Colors
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    ll maxtime;
    bool allDone;


    void search(ll nminIn, ll nmaxIn, vector<vector<ll>> &adj, vector<ll> &sol, ll maxtimeIn=LLONG_MAX) {
	    start = std::chrono::high_resolution_clock::now();
        maxtime = maxtimeIn;
        allDone = false;

        n = nmaxIn-nminIn+1;

        // Rename the nodes so they are from 0 to n-1
        old2new.resize(nmaxIn+1);
        new2old.resize(n);
        for (ll i = 0; i < n; i++) {
            old2new[nminIn+i] = i;
            new2old[i] = nminIn+i;
        }

        // Build the local adjl and adjm
        adjl.resize(n);
        adjm.resize(n);
        C.resize(n+2);
        for (ll i = 0; i < n; i++) { adjm[i].assign(n,false); }
        for (ll i = nminIn; i <= nmaxIn; i++) {
            ll ii = old2new[i];
            for (auto j : adj[i]) { 
                ll jj = old2new[j];
                adjm[ii][jj] = true;
                adjl[ii].push_back(jj);
            }
        }

        // Initially order the vertices by a descending order of degree
        vector<MCQVertex> vv(n);
        for (ll i = 0; i < n; i++) {
            vv[i].idx = i;
            vv[i].deg = (ll) adjl[i].size();
        }
        sort(vv.begin(),vv.end());
        ll maxdeg = vv.front().deg;


        // Setup V and N arrays
        vector<ll> V(n);
        vector<ll> N(n);
        for (ll i = 0; i < n; i++) { V[i] = vv[i].idx; N[V[i]] = (i < maxdeg ? i+1 : maxdeg+1); }

        expand(V,N);

        sol.clear();
        for (auto c : Qmax) { sol.push_back(new2old[c]); }
    }

    void expand(vector<ll> &R, vector<ll> &N) {
	    auto now = std::chrono::high_resolution_clock::now();
        ll duration = std::chrono::duration_cast<std::chrono::milliseconds>(now-start).count();
        allDone = (duration > maxtime);
        vector<ll> Rp;
        vector<ll> Np(n);
        while (!R.empty()) {
            if (allDone) return;
            ll p = R.back();
            if ((ll) Q.size() + N[p] > (ll) Qmax.size()) {
                Q.push_back(p);
                Rp.clear();
                for (auto r : R) { if (adjm[p][r]) Rp.push_back(r); }
                if (!Rp.empty()) {
                    numberSort(Rp,Np);
                    expand(Rp,Np);
                }
                else if (Q.size() > Qmax.size()) { Qmax = Q; }
                Q.pop_back();
            }
            R.pop_back();
        }
    }

    void numberSort(vector<ll> &R, vector<ll> &N) {
        ll maxno = 1;
        C[1].clear();
        C[2].clear();
        for (auto p : R) {
            ll k = 1;
            while (true) {
                ll done = true;
                for (auto c : C[k]) { if (adjm[p][c]) { done = false; break; } }
                if (done) break;
                k++;
            }
            if (k > maxno) { maxno = k; C[maxno+1].clear(); }
            N[p] = k;
            C[k].push_back(p);
        }
        R.clear();
        for (ll k = 1; k <= maxno; k++) {
            for (auto c : C[k]) { R.push_back(c); }
        }
    }
};

struct MCR {
    ll n;
    vector<vector<bool>> adjm;
    vector<vector<ll>>   adjl;
    vector<ll> Q;
    vector<ll> Qmax;
    vector<ll> old2new;
    vector<ll> new2old;
    vector<vector<ll>> C; // Colors
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    ll maxtime;
    bool allDone;

    void search(ll nminIn, ll nmaxIn, vector<vector<ll>> &adj, vector<ll> &sol, ll maxtimeIn=LLONG_MAX) {
	    start = std::chrono::high_resolution_clock::now();
        maxtime = maxtimeIn;
        allDone = false;

        n = nmaxIn-nminIn+1;

        // Rename the nodes so they are from 0 to n-1
        old2new.resize(nmaxIn+1);
        new2old.resize(n);
        for (ll i = 0; i < n; i++) {
            old2new[nminIn+i] = i;
            new2old[i] = nminIn+i;
        }

        // Build the local adjl and adjm
        adjl.resize(n);
        adjm.resize(n);
        C.resize(n+2);
        for (ll i = 0; i < n; i++) { adjm[i].assign(n,false); }
        for (ll i = nminIn; i <= nmaxIn; i++) {
            ll ii = old2new[i];
            for (auto j : adj[i]) { 
                ll jj = old2new[j];
                adjm[ii][jj] = true;
                adjl[ii].push_back(jj);
            }
        }

        vector<ll> V;
        vector<ll> No(n);
        extendedInitialSortNumber(V,No);
        expand(V,No);
        sol.clear();
        for (auto c : Qmax) { sol.push_back(new2old[c]); }
    }

    void extendedInitialSortNumber(vector<ll> &V, vector<ll> &No) {
        vector<ll> R(n);  for (ll i = 0; i < n; i++) { R[i] = i; }
        vector<ll> Rmin;
        vector<ll> degree(n,0);
        for (ll i = 0; i < n; i++) { degree[i] = (ll) adjl[i].size(); }
        vector<ll> origDegree = degree;
        genRmin(R,Rmin,degree);
        while (Rmin.size() != R.size()) {
            ll p = Rmin[0];
            if (Rmin.size() >= 2) p = secondaryChoice(R,Rmin,degree);
            V.push_back(p);
            for (ll i = 0; i < (ll) R.size(); i++) { if (R[i] == p) { R.erase(R.begin()+i); break; } }
            for (auto r : R) { if (adjm[r][p]) degree[r]--; }
            genRmin(R,Rmin,degree);
        }
        numberSort(Rmin,No);
        reverse(Rmin.begin(),Rmin.end());
        for (auto r : Rmin) V.push_back(r);
        reverse(V.begin(),V.end());

        ll maxdeg = *max_element(origDegree.begin(),origDegree.end());
        ll m = -1;
        for (auto r : Rmin) m = max(m,No[r]);
        m = min(m+1,maxdeg+1);
        for (ll i = (ll) Rmin.size(); i < n; i++) {
            No[V[i]] = m;
            m = min(m+1,maxdeg+1);
        }

        bool cliqueFlag = true;
        for (auto r : Rmin) { 
            if (degree[r] != (ll) Rmin.size() - 1) { cliqueFlag = false; break; }
        }
        if (cliqueFlag) Qmax = Rmin;
    }

    void genRmin(vector<ll> &R, vector<ll> &Rmin, vector<ll> &degree) {
        ll mindeg = n+1;
        for (auto r : R) {mindeg = min(mindeg, degree[r]); }
        Rmin.clear();
        for (auto r : R) { if (degree[r] == mindeg) Rmin.push_back(r); }
    }

    ll secondaryChoice(vector<ll> &R, vector<ll> &Rmin, vector<ll> &degree) {
        ll best = 987654321;
        ll ans = -1;
        for (auto r : Rmin) { 
            ll score = 0;
            for (auto rr : R) {
                if (adjm[r][rr]) score += degree[rr];
            }
            if (score < best) {
                best = score;
                ans = r;
            }
        }
        return ans;
    }

    void expand(vector<ll> &R, vector<ll> &N) {
	    auto now = std::chrono::high_resolution_clock::now();
        ll duration = std::chrono::duration_cast<std::chrono::milliseconds>(now-start).count();
        allDone = (duration > maxtime);
        vector<ll> Rp;
        vector<ll> Np(n);
        while (!R.empty()) {
            if (allDone) return;
            ll p = R.back();
            if ((ll) Q.size() + N[p] > (ll) Qmax.size()) {
                Q.push_back(p);
                Rp.clear();
                for (auto r : R) { if (adjm[p][r]) Rp.push_back(r); }
                if (!Rp.empty()) {
                    numberSort(Rp,Np);
                    expand(Rp,Np);
                }
                else if (Q.size() > Qmax.size()) { Qmax = Q; }
                Q.pop_back();
            }
            R.pop_back();
        }
    }

    void numberSort(vector<ll> &R, vector<ll> &N) {
        ll maxno = 1;
        C[1].clear();
        C[2].clear();
        for (auto p : R) {
            ll k = 1;
            while (true) {
                ll done = true;
                for (auto c : C[k]) { if (adjm[p][c]) { done = false; break; } }
                if (done) break;
                k++;
            }
            if (k > maxno) { maxno = k; C[maxno+1].clear(); }
            N[p] = k;
            C[k].push_back(p);
        }
        R.clear();
        for (ll k = 1; k <= maxno; k++) {
            for (auto c : C[k]) { R.push_back(c); }
        }
    }

};

struct MCS {
    ll n;
    vector<vector<bool>> adjm;
    vector<vector<ll>>   adjl;
    vector<ll> Q;
    vector<ll> Qmax;
    vector<ll> old2new;
    vector<ll> new2old;
    vector<vector<ll>> C; // Colors
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    ll maxtime;
    bool allDone;

    void search(ll nminIn, ll nmaxIn, vector<vector<ll>> &adj, vector<ll> &sol, ll maxtimeIn=LLONG_MAX) {
	    start = std::chrono::high_resolution_clock::now();
        maxtime = maxtimeIn;
        allDone = false;

        n = nmaxIn-nminIn+1;

        // Rename the nodes so they are from 0 to n-1
        old2new.resize(nmaxIn+1);
        new2old.resize(n);
        for (ll i = 0; i < n; i++) {
            old2new[nminIn+i] = i;
            new2old[i] = nminIn+i;
        }

        // Build the local adjl and adjm
        adjl.resize(n);
        adjm.resize(n);
        C.resize(n+2);
        for (ll i = 0; i < n; i++) { adjm[i].assign(n,false); }
        for (ll i = nminIn; i <= nmaxIn; i++) {
            ll ii = old2new[i];
            for (auto j : adj[i]) { 
                ll jj = old2new[j];
                adjm[ii][jj] = true;
                adjl[ii].push_back(jj);
            }
        }

        vector<ll> V;
        vector<ll> No(n);
        extendedInitialSortNumber(V,No);
        expand(V,V,No);
        sol.clear();
        for (auto c : Qmax) { sol.push_back(new2old[c]); }
    }

    void extendedInitialSortNumber(vector<ll> &V, vector<ll> &No) {
        vector<ll> R(n);  for (ll i = 0; i < n; i++) { R[i] = i; }
        vector<ll> Rmin;
        vector<ll> degree(n,0);
        for (ll i = 0; i < n; i++) { degree[i] = (ll) adjl[i].size(); }
        vector<ll> origDegree = degree;
        genRmin(R,Rmin,degree);
        while (Rmin.size() != R.size()) {
            ll p = Rmin[0];
            if (Rmin.size() >= 2) p = secondaryChoice(R,Rmin,degree);
            V.push_back(p);
            for (ll i = 0; i < (ll) R.size(); i++) { if (R[i] == p) { R.erase(R.begin()+i); break; } }
            for (auto r : R) { if (adjm[r][p]) degree[r]--; }
            genRmin(R,Rmin,degree);
        }
        numberSort(Rmin,No);
        reverse(Rmin.begin(),Rmin.end());
        for (auto r : Rmin) V.push_back(r);
        reverse(V.begin(),V.end());

        ll maxdeg = *max_element(origDegree.begin(),origDegree.end());
        ll m = -1;
        for (auto r : Rmin) m = max(m,No[r]);
        m = min(m+1,maxdeg+1);
        for (ll i = (ll) Rmin.size(); i < n; i++) {
            No[V[i]] = m;
            m = min(m+1,maxdeg+1);
        }

        bool cliqueFlag = true;
        for (auto r : Rmin) { 
            if (degree[r] != (ll) Rmin.size() - 1) { cliqueFlag = false; break; }
        }
        if (cliqueFlag) Qmax = Rmin;
    }

    void genRmin(vector<ll> &R, vector<ll> &Rmin, vector<ll> &degree) {
        ll mindeg = n+1;
        for (auto r : R) {mindeg = min(mindeg, degree[r]); }
        Rmin.clear();
        for (auto r : R) { if (degree[r] == mindeg) Rmin.push_back(r); }
    }

    ll secondaryChoice(vector<ll> &R, vector<ll> &Rmin, vector<ll> &degree) {
        ll best = 987654321;
        ll ans = -1;
        for (auto r : Rmin) { 
            ll score = 0;
            for (auto rr : R) {
                if (adjm[r][rr]) score += degree[rr];
            }
            if (score < best) {
                best = score;
                ans = r;
            }
        }
        return ans;
    }

    void expand(vector<ll> &Va, vector<ll> &R, vector<ll> &N) {
	    auto now = std::chrono::high_resolution_clock::now();
        ll duration = std::chrono::duration_cast<std::chrono::milliseconds>(now-start).count();
        allDone = (duration > maxtime);
        vector<ll> Vp;
        vector<ll> Rp;
        vector<ll> Np(n);
        while (!R.empty()) {
            if (allDone) return;
            ll p = R.back();
            if ((ll) Q.size() + N[p] > (ll) Qmax.size()) {
                Q.push_back(p);
                Vp.clear();
                for (auto r : Va) { if (adjm[p][r]) Vp.push_back(r); }
                if (!Vp.empty()) {
                    Rp.resize(Vp.size());
                    reNumberSort(Vp,Rp,Np);
                    expand(Vp,Rp,Np);
                }
                else if (Q.size() > Qmax.size()) { Qmax = Q; }
                Q.pop_back();
            }
            R.pop_back();
            for (ll i = 0; i < (ll) Va.size(); i++) { if (Va[i] == p) { Va.erase(Va.begin()+i); break; } }
        }
    }

    void numberSort(vector<ll> &R, vector<ll> &N) {
        ll maxno = 1;
        C[1].clear();
        C[2].clear();
        for (auto p : R) {
            ll k = 1;
            while (true) {
                ll done = true;
                for (auto c : C[k]) { if (adjm[p][c]) { done = false; break; } }
                if (done) break;
                k++;
            }
            if (k > maxno) { maxno = k; C[maxno+1].clear(); }
            N[p] = k;
            C[k].push_back(p);
        }
        R.clear();
        for (ll k = 1; k <= maxno; k++) {
            for (auto c : C[k]) { R.push_back(c); }
        }
    }

    void reNumberSort(vector<ll> &Va, vector<ll> &R, vector<ll> &N) {
        ll maxno = 1;
        C[1].clear();
        C[2].clear();
        ll Noth = (ll) Qmax.size() - (ll) Q.size();
        for (auto p : Va) {
            ll k = 1;
            while (true) {
                ll done = true;
                for (auto c : C[k]) { if (adjm[p][c]) { done = false; break; } }
                if (done) break;
                k++;
            }
            if (k > maxno) { maxno = k; C[maxno+1].clear(); }
            C[k].push_back(p);

            // Renumber stuff
            if ((k > Noth) && (k == maxno)) {
                reNumber(p,k,Noth);
                if (C[maxno].empty()) maxno--;
            }

        }
        // Now we really only need to keep candidates that exceed the threshold, so R could be smaller than Va
        R.clear();
        for (ll k = Noth+1; k <= maxno; k++) {
            for (auto c : C[k]) { 
                R.push_back(c);
                N[c] = k;
            }
        }
    }

    void reNumber(ll p, ll k, ll Noth) {
        for (ll k1 = 1; k1 < Noth; k1++) {
            ll cnt = 0; ll q = -1;
            for (auto c : C[k1]) { if (adjm[c][p]) { cnt++; q=c; } }
            if (cnt != 1) continue;
            for (ll k2 = k1+1; k2 <= Noth; k2++) {
                bool emp = true;
                for (auto c : C[k2]) { if (adjm[c][q]) { emp = false; break; } }
                if (emp) {
                    for (ll i = 0; i < (ll) C[k].size(); i++)  { if (C[k][i] == p)  { C[k].erase(C[k].begin()+i); break; } }
                    for (ll i = 0; i < (ll) C[k1].size(); i++) { if (C[k1][i] == q) { C[k1].erase(C[k1].begin()+i); break; } }
                    C[k1].push_back(p);
                    C[k2].push_back(q);
                    return;
                }
            }

        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void genGraph(ll s, double e, mt19937 &rng, vector<vector<ll>> &adj) {
    uniform_real_distribution<double> dist(0.0,1.0);
    adj.resize(s+1);
    for (ll i = 1; i < s; i++) {
        for (ll j = i+1; j <= s; j++) {
            if (dist(rng) < e) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
}

void testCorrectness(ll cnt=10) {
    vector<ll> sizes = {10,20,30,40};
    vector<double> edgeProbs = {0.5, 0.6, 0.7, 0.8, 0.9, 0.95, 0.98 };
    mt19937 rng(1234);
    for (ll i = 0; i < cnt; i++) {
        for (auto s : sizes) {
            for (auto e : edgeProbs) {
                vector<vector<ll>> adj;
                genGraph(s,e,rng,adj);

                MC mc;
                vector<ll> sol_mc;
                mc.search(1,s,adj,sol_mc);

                MCQ mcq;
                vector<ll> sol_mcq;
                mcq.search(1,s,adj,sol_mcq);

                MCR mcr;
                vector<ll> sol_mcr;
                mcr.search(1,s,adj,sol_mcr);

                MCS mcs;
                vector<ll> sol_mcs;
                mcs.search(1,s,adj,sol_mcs);

                if (sol_mc.size() == sol_mcq.size() && sol_mc.size() == sol_mcr.size() && sol_mc.size() == sol_mcs.size()) {
                    printf("--p---  (i=%lld s=%lld e=%.3f sol=%lld)\n", i, s, e, (ll) sol_mc.size());
                } else {
                    printf("FAILED  (i=%lld s=%lld e=%.3f sol_mc=%lld sol_mcq=%lld sol_mcr=%lld sol_mcs=%lld)\n", i, s, e, (ll) sol_mc.size(), (ll) sol_mcq.size(), (ll) sol_mcr.size(), (ll) sol_mcs.size());
                }
            }
        }
    }
}

void testPerformance(ll s, double e, ll cnt, ll timelim=10000, ll seed=1234) {
    mt19937 rng;
    rng.seed((unsigned int) seed);
    vector<ll> mcqArr;
    vector<ll> mcrArr;
    vector<ll> mcsArr;

    for (ll i = 0; i < cnt; i++) {
        vector<vector<ll>> adj;
        genGraph(s,e,rng,adj);
        vector<ll> sol;
        std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
        ll elapsed_time;

        MCQ mcq;
	    start = std::chrono::high_resolution_clock::now();
        mcq.search(1,s,adj,sol,timelim);
	    end = std::chrono::high_resolution_clock::now();
	    elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        mcqArr.push_back(min(timelim,elapsed_time));

        MCR mcr;
	    start = std::chrono::high_resolution_clock::now();
        mcr.search(1,s,adj,sol,timelim);
	    end = std::chrono::high_resolution_clock::now();
	    elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        mcrArr.push_back(min(timelim,elapsed_time));

        MCS mcs;
	    start = std::chrono::high_resolution_clock::now();
        mcs.search(1,s,adj,sol,timelim);
	    end = std::chrono::high_resolution_clock::now();
	    elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        mcsArr.push_back(min(timelim,elapsed_time));
    }
    printf("mcq,%lld,%.3f",s,e);
    for (auto x : mcqArr) { printf(",%lld",x); }
    printf("\n");

    printf("mcr,%lld,%.3f",s,e);
    for (auto x : mcrArr) { printf(",%lld",x); }
    printf("\n");

    printf("mcs,%lld,%.3f",s,e);
    for (auto x : mcsArr) { printf(",%lld",x); }
    printf("\n");

    fflush(stdout);
}

void regress(ll cnt=100, ll timelim=10000, ll seed=1234) {
    vector<ll> sizes = {50,100,150,200};
    vector<double> edgeProb = {0.50, 0.55, 0.60, 0.65, 0.70, 0.75, 0.80, 0.82, 0.84, 0.86, 0.88, 0.90, 0.92, 0.94, 0.96, 0.98};
    for (auto s : sizes) {
        for (auto e : edgeProb) {
            testPerformance(s,e,cnt,timelim,seed);
        }
    }
}


int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string mode = "correctness";
    if (argc >= 2) mode = argv[1];
    if (mode == "correctness")      { testCorrectness(); }
    else if (mode == "performance") {
        assert(argc == 6); 
        ll s = stoll(argv[2]);
        double e = stod(argv[3]);
        ll cnt = stoll(argv[4]);
        ll timelim = stoll(argv[5]);
        testPerformance(s,e,cnt,timelim);
    }
    else if (mode == "regress") {
        assert(argc == 4); 
        ll cnt = stoll(argv[2]);
        ll timelim = stoll(argv[3]);
        regress(cnt, timelim);
    }
    //else if (mode == "data") { 
    //    ll s = stoll(argv[2]);
    //    double e = stoee

    return 0;
}

