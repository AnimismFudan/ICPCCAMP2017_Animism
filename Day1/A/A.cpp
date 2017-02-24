#include <bits/stdc++.h>
#define intl long long
using namespace std;

intl ans;
intl f[2010][2010],g[2010][2010];
int n,m;
intl A[2010];

void add(intl &a, intl b) {
        a += b; a %= 1000000007LL;
}

int main() {
        while (scanf("%d",&n) != EOF) {
                for (int i = 1; i <= n; i++) scanf("%lld",&A[i]);
                for (int i = 1; i <= n; i++) f[2][i] = 1;
                for (int i = 1; i <= n; i++) g[2][i] = i - 1;
                for (int i = 3; i <= n; i++) {
                        for (int j = 1; j <= n; j++) f[i][j] = g[i][j] = 0;
                        // f -> f;
                        intl s = 0;
                        for (int j = n; j >= 1; j--) {
                                add(s, f[i - 1][j] * A[j]);
                                add(f[i][j], s);
                        }
                        // f -> g;
                        s = 0;
                        for (int j = n; j >= 1; j--) {
                                add(g[i][j], s * (j - 1));
                                add(s, f[i - 1][j] * A[j]);
                        }
                        s = 0;
                        for (int j = 1; j <= n; j++) {
                                add(g[i][j], s * A[j]);
                                add(g[i][j], f[i - 1][j] * (j - 1) % 1000000007LL * A[j]);
                                add(s, f[i - 1][j] * j);
                        }
                        // g -> g;
                        s = 0;
                        for (int j = 1; j <= n; j++) {
                                add(g[i][j], s * A[j]);
                                add(s, g[i - 1][j]);
                        }
                        // g -> f;
                        for (int j = 1; j <= n; j++)
                                add(f[i][j], g[i - 1][j] * A[j]);
                }
                ans = 0;
                for (int i = 1; i <= n; i++)
                        add(ans, f[n][i] * i + g[n][i]);
                printf("%lld\n",ans);
        }
        return 0;
}