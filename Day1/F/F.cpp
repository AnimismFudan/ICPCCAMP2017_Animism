#include <bits/stdc++.h>
#define maxn 72
#define maxm 10100
#define maxt 2010000
#define intl long long
using namespace std;

const intl Mo = 1000000007LL;

int ti[maxm],loc[maxm];
int n,T,m,du[maxn];
intl Ans,ans[maxt],val[maxn],VAL[maxn];

char s[maxn][maxn];

struct matrix {
        intl v[maxn][maxn];

        void operator *= (matrix b) {
                matrix a;
                memcpy(a.v,v,sizeof(v));
                memset(v,0,sizeof(v));
                for (int i = 1; i <= n; i++)
                        for (int j = 1; j <= n; j++)
                                for (int k = 1; k <= n; k++)
                                        (v[i][j] += a.v[i][k] * b.v[k][j]) %= Mo;
        }
        
} trans[maxn];

intl fpm(intl a, intl b) {
        intl ans = 1LL;
        if (!a) return 0LL;
        for (; b; b >>= 1) {
                if (b & 1LL) (ans *= a) %= Mo;
                (a *= a) %= Mo;
        }
        return ans;
}

void solve() {
        int u = 1;
        for (int t = 1; t <= T; t += n) {
                int R = min(t + n - 1, T);
                
                for (int i = 1; i <= n; i++) {
                        for (int k = 1; k <= n; k++)
                                (ans[t + i - 1] += trans[i].v[k][n] * val[k]) %= Mo;
                }

                memset(VAL,0,sizeof(VAL));
                
                for (int a = 1; a <= n; a++)
                        for (int b = 1; b <= n; b++)
                                (VAL[b] += val[a] * trans[n].v[a][b]) %= Mo;
                
                for (; u <= m && ti[u] <= R; u++) {
                        for (int i = 0; i + ti[u] <= R; i++) {
                                int k = loc[u];
                                (ans[ti[u] + i] += trans[i].v[k][n]) %= Mo;
                        }

                        int a = loc[u];
                        for (int b = 1; b <= n; b++)
                                (VAL[b] += trans[R - ti[u]].v[a][b]) %= Mo;
                }

                for (int i = 1; i <= n; i++) val[i] = VAL[i];
        }

        Ans = 0;
        for (int i = 1; i <= T; i++)
                Ans ^= ans[i];
        printf("%lld\n",Ans);
}

int main() {
        scanf("%d %d %d",&n,&m,&T);
        for (int i = 1; i <= n; i++)
                scanf("%s",s[i] + 1);

        for (int i = 1; i <= m; i++)
                scanf("%d %d",&ti[i],&loc[i]);
        for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++)
                        if (s[i][j] == '1') du[i]++;
        }

        for (int i = 1; i <= n; i++) {
                intl js = fpm(du[i], Mo - 2LL);
                for (int j = 1; j <= n; j++)
                        if (s[i][j] == '1')
                                trans[1].v[i][j] = js;
        }

        for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                        trans[0].v[i][j] = (i == j);
        
        for (int i = 2; i <= n; i++) {
                trans[i] = trans[i - 1];
                trans[i] *= trans[1];
        }

        solve();
        return 0;
}