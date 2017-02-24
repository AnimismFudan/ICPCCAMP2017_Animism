#include <bits/stdc++.h>
#define maxn 301000
#define intl long long
using namespace std;

struct NODE {
        int nex[26], f, ml, p;
        void init() {
                memset(nex,0,sizeof(nex));
                f = ml = 0;
        }
} node[maxn * 2];

struct str { int v, nex; } edge[maxn * 2];

intl ans;
int e,n,tot,head,tail;
int fst[maxn * 2];
int sum[26][maxn];
char s[maxn];

void add(int ch, int len) {
        int p = tail, np = ++tot; node[tot].init();
        node[np].ml = len;
        for (; p && !node[p].nex[ch]; p = node[p].f) node[p].nex[ch] = np;
        tail = np;
        if (!p) node[np].f = head;
        else {
                if (node[node[p].nex[ch]].ml == node[p].ml + 1)
                        node[np].f = node[p].nex[ch];
                else {
                        int q = node[p].nex[ch], just = ++tot;
                        node[tot].init();
                        node[just] = node[q];
                        node[just].ml = node[p].ml + 1;
                        node[q].f = node[np].f = just;
                        for (; p && node[p].nex[ch] == q; p = node[p].f)
                                node[p].nex[ch] = just;
                }
        }
}

void make_edge(int a, int b) {
        edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
}

void prepare() {
        for (int i = 1; i <= n; i++) {
                for (int k = 0; k < 26; k++) sum[k][i] = sum[k][i - 1];
                sum[s[i] - 'a'][i]++;
        }
}

int query(int L, int R, int k) {
        if (L > R) return 0;
        return (sum[k][R] - sum[k][L - 1]);
}

void solve() {
        for (int u = 1; u <= tot; u++) {
                for (int k = 0; k < 26; k++) {
                        if (!node[u].nex[k]) continue;
                        ans += (intl) query(node[u].p - node[u].ml + 1, node[u].p - node[node[u].f].ml - 1, k);
                }
                for (int i = fst[u]; i; i = edge[i].nex) {
                        int v = edge[i].v;
                        int k = s[node[v].p - node[u].ml] - 'a';
                        if (node[u].nex[k]) ans++;
                }
        }
}

int main() {
        scanf("%s",s + 1);
        n = strlen(s + 1);
        head = tail = ++tot;
        for (int i = 1; i <= n; i++) {
                add(s[i] - 'a', i);
        }
        int u = head;
        for (int i = 1; i <= n; i++) {
                u = node[u].nex[s[i] - 'a'];
                node[u].p = i;
                for (int v = node[u].f; v && !node[v].p; v = node[v].f)
                        node[v].p = i;                
        }

        for (int i = 2; i <= tot; i++)                 
                make_edge(node[i].f, i);

        prepare();
        solve();
        printf("%lld\n",ans);
        return 0;
}