
#include <bits/stdc++.h>
#define maxn 101000
#define intl unsigned long long
using namespace std;

const intl Max = ~((intl) 0);

struct ST {
        intl v[100010 / 64 + 1];
} now, st[10000];

int n,m;
int A[101000], mark[101000],pri[101000],top;

int solve(int L, int R, int l, int r) {
        for (int i = r % 64; i >= 0; i--) {
                if (!(now.v[R] & (1LL << i))) return (R * 64 + i);
        }

        for (int k = R - 1; k >= L; k--) {
                if (now.v[k] == Max) continue;
                for (int i = 63; i >= 0; i--)
                        if (!(now.v[k] & (1LL << i))) return (k * 64 + i);
        }
        return -1;
}

int main() {
        for (int i = 2; i <= 100000; i++) {
                if (!mark[i]) pri[++top] = i;
                for (int j = 1; j <= top && i * pri[j] <= 100000; j++) {
                        mark[i * pri[j]] = 1;
                        if (!(i % pri[j])) break;
                }
        }

        for (int i = 1; i <= top; i++) mark[pri[i]] = i;
        scanf("%d %d",&n,&m);        
        for (int i = 0; i < n; i++) {
                scanf("%d",&A[i]);
                for (int j = 2; j * j <= A[i]; j++) {
                        if ((A[i] % j)) continue;
                        while (!(A[i] % j)) A[i] /= j;
                        st[mark[j]].v[i / 64] |= 1LL << (i % 64);
                }
                if (A[i] != 1)
                        st[mark[A[i]]].v[i / 64] |= 1LL << (i % 64);
        }

        for (; m; m--) {
                int l, r, x;
                scanf("%d %d %d",&l,&r,&x);
                l--; r--;
                int R = r / 64, L = l / 64;
                for (int i = R; i >= L; i--) now.v[i] = 0;
                for (int v = 2; v * v <= x; v++) {
                        if ((x % v)) continue;
                        while (!(x % v)) x /= v;
                        int u = mark[v];
                        for (int i = R; i >= L; i--)
                                now.v[i] |= st[u].v[i];
                }
                if (x != 1) {
                        int u = mark[x];
                        for (int i = R; i >= L; i--)
                                now.v[i] |= st[u].v[i];
                }
                int ans = solve(L, R, l, r);
                if (ans >= l) printf("%d\n",ans + 1);
                else printf("%d\n",-1);
        }
        return 0;
}