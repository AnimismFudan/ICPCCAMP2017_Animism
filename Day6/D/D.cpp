#include <bits/stdc++.h>
#define maxn 201000
using namespace std;

struct str { int v, nex; } edge[maxn << 1];
int top,now,e,p[maxn],n,mark[maxn];
int A[maxn],st[maxn];
int fst[maxn];

void make_edge(int a , int b) {
        edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
        edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a;
}

void dfs(int u) {
        st[++top] = u;
        mark[u] = 1;
        for (int i = fst[u]; i; i = edge[i].nex) {
                int v = edge[i].v;
                if (mark[v]) continue;
                p[u] = v;
                dfs(v);
        }
}

int main() {
        scanf("%d",&n);
        for (int i = 1; i < n; i++) scanf("%d",&A[i]);
        now = 0;
        for (int i = 1; i < n; i++) {
                if (A[i] > now) {
                        if ((A[i] > now + 2) || ((A[i] - now) & 1)) { printf("No\n"); return 0; }
                        while (A[i] > now) {
                                st[++now] = i;
                        }
                } else if (A[i] < now) {
                        if ((A[i] < now - 2) || ((now - A[i]) & 1)) { printf("No\n"); return 0; }
                        while (A[i] < now) {
                                make_edge(st[now--], i);
                        }
                }
        }
        if (now > 2 || now == 1) { printf("No\n"); return 0; }
        while (now > 0) { make_edge(st[now--], n); }
        for (int i = 1; i <= n; i++) {
                top = 0;
                if (!mark[i]) dfs(i);
                for (int i = 1; i <= top; i++) p[st[i]] = st[i + 1];
                p[st[top]] = st[1];
        }
        printf("Yes\n");
        for (int i = 1; i <= n; i++) 
                printf("%d ",p[i]);
        return 0;
}