#include <bits/stdc++.h>
#define maxn 201000
#define lk (u << 1)
#define rk (u << 1 | 1)
#define midl ((L + R) >> 1)
#define midr (midl + 1)
using namespace std;

struct str { int v,nex; } edge[maxn << 1];

int w[maxn],W[maxn];
int fst[maxn],size[maxn],fa[maxn],son[maxn],anc[maxn],mark[maxn],sou[maxn],dep[maxn];
int MARK[maxn << 2], val[maxn << 2], sum[maxn << 2];
int n,m,top,e;

void make_edge(int a, int b) {
        edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
        edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a;
}

void dfs(int u) {
        dep[u] = dep[fa[u]] + 1;
        size[u] = 1;
        w[u] = W[u] - W[fa[u]];
        for (int i = fst[u]; i; i = edge[i].nex) {
                int v = edge[i].v;
                if (fa[u] == v) continue;
                fa[v] = u;
                dfs(v);
                size[u] += size[v];
                if (size[v] > size[son[u]]) son[u] = v;
        }
        return;
}

void build(int u, int L, int R) {
        if (L == R) {
                val[u] = w[sou[L]];
                sum[u] = 0;
                MARK[u] = 0;
                return;
        }
        build(lk, L, midl);
        build(rk, midr, R);
        sum[u] = sum[lk] + sum[rk];
        val[u] = val[lk] + val[rk];
        MARK[u] = 0;
        return;
}

void init() {
        for (int i = 1; i <= n; i++) fa[i] = fst[i] = size[i] = dep[i] = son[i] = mark[i] = 0;
        e = 0;
}

void down(int u, int L, int R) {
        if (!MARK[u]) return;
        sum[u] += val[u] * MARK[u];
        if (L < R) { MARK[lk] += MARK[u]; MARK[rk] += MARK[u]; }
        MARK[u] = 0;
        return;
}

int query(int u, int L, int R, int l, int r) {
        down(u, L, R);
        if (L == l && R == r) return sum[u];
        if (r < midr) { down(rk, midr, R); return query(lk, L, midl, l, r); }
        else if (l > midl) { down(lk, L, midl); return query(rk, midr, R, l, r); }
        else return query(lk, L, midl, l, midl) + query(rk, midr, R, midr, r);
}

void change(int u, int L, int R, int l, int r) {
        down(u, L, R);
        if (L == l && R == r) { MARK[u]++; down(u, L, R); return; }
        if (r < midr) { down(rk, midr, R); change(lk, L, midl, l, r); }
        else if (l > midl) { down(lk, L, midl); change(rk, midr, R, l, r); }
        else { change(lk, L, midl, l, midl); change(rk, midr, R, midr, r); }
        sum[u] = sum[lk] + sum[rk];
        return;
}

int solve(int u) {
        int ans = 0;
        for (; u; u = fa[anc[u]])
                ans += query(1, 1, n, mark[anc[u]], mark[u]);
        return ans;
}

void Change(int u) {
        for (; u; u = fa[anc[u]])
                change(1, 1, n, mark[anc[u]], mark[u]);
}

int main() {
        while (scanf("%d",&n) != EOF) {
                init();
                for (int i = 1; i <= n; i++)
                        scanf("%d",&W[i]);
                for (int i = 2; i <= n; i++) {
                        int j;
                        scanf("%d",&j);
                        make_edge(i, j);
                }
                dfs(1);
                top = 0;
                for (int i = 1; i <= n; i++) {
                        if (mark[i]) continue;
                        int v;
                        for (v = i; fa[v] && son[fa[v]] == v; v = fa[v]);
                        for (int u = v; u; u = son[u]) {
                                anc[u] = v;
                                mark[u] = ++top;
                                sou[top] = u;
                        }
                }
                build(1, 1, n);
                for (int i = 1; i <= n; i++) {
                        int ans = solve(i);
                        if (i != 1)
                                printf("%d\n",ans);
                        Change(i);
                }
        }        
        
        return 0;
}