#include <bits/stdc++.h>
using namespace std;

#define LL long long

int Test, N, S, M, pt;
int ans, delta, dd;
int fa[200010], dep[200010], vis[200010];
int st[200010], ne[400010], go[400010];

class rec{
        public:
        int x, d;
}L[200010];

void Add(int x, int y){
        ne[++pt] = st[x];
        st[x] = pt;
        go[pt] = y;
}

bool cmpd(const rec &A, const rec &B){
        return A.d > B.d;
}

void dfs(int x){
        for (int i = st[x]; i; i = ne[i])
                if (go[i] != fa[x]){
                        dep[go[i]] = dep[x] + 1;
                        fa[go[i]] = x;
                        dfs(go[i]);
                }
}

void Push(int x){
        if (vis[x]) return;
        if (fa[x]) Push(fa[x]);
        vis[x] = 1;
        delta += 2;
}

int get_dist(int x, int y){
        vis[x] = 1;
        vis[y] = 1;
        int dd = 0;
        while (x != y){
                if (dep[x] > dep[y])
                        swap(x, y);
                x = fa[x];
                vis[x] = 1;
                dd++;
        }
        return dd;
}

int main(){
        scanf("%d", &Test);
        while (Test--){
                scanf("%d%d%d", &N, &S, &M);
                pt = 1;
                for (int i = 1; i <= N; i++){
                        st[i] = 0;
                        vis[i] = 0;
                }
                for (int i = 1; i < N; i++){
                        int x, y;
                        scanf("%d%d", &x, &y);
                        Add(x, y);
                        Add(y, x);
                }
                for (int i = 1; i <= N; i++){
                        fa[i] = 0;
                        dep[i] = 0;
                }
                dfs(M);
                for (int i = 1; i <= N; i++){
                        L[i].x = i;
                        L[i].d = dep[i];
                }
                sort(L + 1, L + N + 1, cmpd);
                for (int i = 1; i <= N; i++){
                        fa[i] = 0;
                        dep[i] = 0;
                }
                dfs(S);
                for (int i = 1; i <= N; i++)
                        dep[L[i].x] = L[i].d;
                dd = get_dist(S, M);
                ans = dd + L[1].d;
                delta = 0;
                for (int i = 1; i <= N;){
                        int j = i;
                        for (; j <= N && L[j].d == L[i].d; j++);
                        for (int k = i; k < j; k++)
                                Push(L[k].x);
                        ans = min(ans, dd + L[j].d + delta);
                        i = j;
                }
                printf("%d\n", ans);
        }
}