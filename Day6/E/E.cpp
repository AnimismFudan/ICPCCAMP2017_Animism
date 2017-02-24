
#include <bits/stdc++.h>
#define maxn 101000
#define midl ((L + R) >> 1)
#define midr (midl + 1)
#define lk (u << 1)
#define rk (lk + 1)
#define INF (1 << 30)
using namespace std;

map<int,int> st;
vector <int> vec[maxn];
int val[maxn];
int n,top;
int mark[maxn << 2];
int L[maxn], R[maxn];
int sou[maxn];

int dfs(int u) {
        L[u] = R[u] = ++top;
        sou[top] = u;
        for (auto i = vec[u].begin(); i != vec[u].end(); i++) {
                int v = *i;
                R[u] = dfs(v);
        }        
        return R[u];
}

void change(int u, int L, int R, int k) {
        if (L == R) { mark[u] = INF; return; }
        if (k < midr) change(lk, L, midl, k);
        else change(rk, midr, R, k);
        mark[u] = min(mark[lk], mark[rk]);
}

int query(int u, int L, int R, int l, int r) {
        if (L == l && R == r) return mark[u];
        if (r < midr) return query(lk, L, midl, l, r);
        if (l > midl) return query(rk, midr, R, l, r);
        return min(query(lk, L, midl, l, midl), query(rk, midr, R, midr, r));
}

void build(int u, int L, int R) {
        if (L == R) { mark[u] = val[sou[L]]; return; }
        build(lk, L, midl);
        build(rk, midr, R);
        mark[u] = min(mark[lk], mark[rk]);
}

void solve(int l, int r) {
        if (l == r) {
                printf("%d ", st[query(1, 1, n, l, r)]);
                change(1, 1, n, l);                
                return;
        }
        int k;
        while ((k = query(1, 1, n, l + 1, r)) != INF) {
                int u = st[k];
                solve(L[u], R[u]);
        }
        printf("%d ",st[query(1, 1, n, l, r)]);
        change(1, 1, n, l);
        return;
}

int main() {
        scanf("%d",&n);
        for (int i = 2; i <= n; i++) {
                int j;
                scanf("%d",&j);
                vec[j].push_back(i);
        }
        for (int i = 1; i <= n; i++) scanf("%d",&val[i]);
        for (int i = 1; i <= n; i++) st[val[i]] = i;
        dfs(1);
        build(1, 1, n);
        solve(1, n);
        return 0;
}