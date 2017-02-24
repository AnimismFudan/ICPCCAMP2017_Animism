#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = 30;
const int MaxM = 500;
const int mod = (int)1e9 + 7;

int N, K, L, S, ans, mincnt, maxcnt;
char str[MaxN];
int fac[MaxN];
int l, m, x[MaxN];
int f[MaxN][MaxN][MaxM];

inline int DP()
{
        m = 0;
        if (K<0) return 0;
        for (int i=1; i<=l; i++)
                m += x[i];
        memset(f, 0, sizeof(f));
        f[0][0][0] = 1;
        for (int i=1; i<=l; i++)
                for (int j=0; j<=mincnt; j++)
                        for (int k=0; k<=m; k++)
                        {
                                if (x[i] > k || j<1 ) f[i][j][k] = f[i-1][j][k];
                                else f[i][j][k] = (f[i-1][j][k] + f[i-1][j-1][k-x[i]]) % mod;
                        }
        /*
                cout << l << ' ' << mincnt << ' ' << K << endl;
                for (int i=1; i<=l; i++)
                        cout << x[i] << ' ' ;
                cout << endl;
                cout << "res: " << f[l][mincnt][K] << endl << endl;;
        */
        return f[l][mincnt][K];
}

int main()
{
        //freopen("H.in", "r", stdin);
        
        scanf("%d%d", &N, &K);
        scanf("%s", str+1);        
        L = strlen(str+1);
        
        fac[0] = 1;
        for (int i=1; i<=N; i++)
                fac[i] = (ll) fac[i-1] * i % mod;
        
        K -= L;
        if (K < 0)
        {
                printf("%d\n", 0);
                return 0;
        }
        
        S = 0;
        mincnt = str[1] - 'a';
        maxcnt = N - mincnt - 1;
        for (int i=1; i<=L; i++)
        {
                if (str[i] < str[1]) S++, K -= N-i+1, mincnt --;
                if (str[i] > str[1]) maxcnt --;
        }
        
        //cout << mincnt << ' ' << maxcnt << endl;
        
        for (int i=1; i+L <= N+1; i++)
        {
                //cout << "pos: " << i << endl;
                l = 0;
                for (int j=1; j<i; j++)
                        x[++l] = N - j + 1;
                for (int j=i+L; j<=N; j++)
                        x[++l] = N - j + 1;
                
                ans = (ans + (ll)DP() * fac[mincnt] % mod * fac[maxcnt] % mod) % mod;
                
                K += S;
        }
        
        printf("%d\n", ans);
        
        return 0;
}