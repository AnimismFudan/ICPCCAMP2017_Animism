#include <bits/stdc++.h>
using namespace std;

#define LL long long

const LL pp = (1e9) + 7;

int N, V, K, pt;
int s[5010];
int st[5010], ne[5010], go[5010], fa[5010];
LL f[5010][5010];
LL H[5010], Hrev[5010];

void Add(int x, int y){
        ne[++pt] = st[x];
        st[x] = pt;
        go[pt] = y;
}

LL C(int x, int y){
        return H[x] * Hrev[y] % pp * Hrev[x - y] % pp;
}

LL quick(int x, int y){
        LL s = 1, t = x;
        for (; y; y >>= 1){
                if (y & 1) s = s * t % pp;
                t = t * t % pp;
        }
        return s;
}

int dfs(int x){
        LL res = 1;
        LL now = 0;
        s[x] = 0;
        for (int i = st[x]; i; i = ne[i]){
                int y = go[i];
                now = dfs(y);
                s[x] += s[y];
                res = res * C(s[x], s[y]) % pp * now % pp;
        }
        s[x]++;
        return res;
}

void work(){
        int x = V;
        LL res = dfs(x);
        f[x][1] = res;
        while (x > 1){
                int p = x;
                x = fa[x];
                s[x] = 0;
                LL ans = 1;
                for (int i = st[x]; i; i = ne[i])
                        if (go[i] != p){
                                int y = go[i];
                                res = dfs(y);
                                s[x] += s[y];
                                ans = ans * C(s[x], s[y]) % pp * res % pp;
                        }
                s[x] += s[p];
                for (int j = 1; j <= s[p]; j++)
                        for (int k = j; k <= j + s[x] - s[p]; k++)
                                f[x][k] = (f[x][k] + f[p][j] * C(k - 1, j - 1) % pp * C(s[x] - k, s[p] - j) % pp) % pp;
                for (int k = s[x]; k >= 0; k--)
                        f[x][k + 1] = f[x][k] * ans % pp;
                s[x]++;
        }
}

int main() {
        H[0] = Hrev[0] = 1;
        for (int i = 1; i <= 5000; i++){
                H[i] = H[i - 1] * i % pp;
                Hrev[i] = quick(H[i], pp - 2);
        }
        scanf("%d", &N);
        for (int i = 2; i <= N; i++){
                scanf("%d", &fa[i]);
                Add(fa[i], i);
        }
        scanf("%d%d", &V, &K);
        work();
        cout << f[1][K] << endl;
        return 0;
}