#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define ll long long

const int MaxN = 20;
const int MaxM = 360360 * 20 + 7;

int N, L, w[MaxN];
ll A, M, T, S, ans;
bool f[MaxM];

int main()
{
   // freopen("D.in", "r", stdin);

    while (scanf("%d", &N) != EOF)
    {
        L = 1; A = T = M = 0;
        for (int i=1; i<=N; i++)
        {
            scanf("%d", w+i);
            A = A + (ll)w[i] * i;
            L = i / __gcd(i,L) * L;
        }

        //cout << "T: " ;
        for (int i=1; i<=N; i++)
        {
            if (w[i] == 0) continue;
            int j = min(w[i], w[i] % (L/i) + L/i);
            T += (w[i] - j) / (L / i);
            w[i] = j;
            M = M + (ll)w[i] * i;
            //cout << T << ' ';
        }

        //cout << endl;
        //cout << M << ' ' << L << ' '<< T << endl;

        for (int j=0; j<=M; j++)
            f[j] = false;
        f[0] = true; S = 0;
        for (int i=1; i<=N; i++)
        {
            for (int j=1; w[i]; j<<=1)
            {
                int k = min(w[i], j);
                //S += k*i;
                for (int t = M; t >=k * i; t--)
                    f[t] |= f[t - k*i];
                w[i] -= k;
            }
        }
/*
        for (int j=0; j<=M; j++)
            cout << f[j];
        cout << endl;
*/
        ans = 0;
        for (int i=0; i<L; i++)
        {
            bool flg = false;
            for (int j=0; j*L + i <= M; j++)
                if (f[j*L + i])
                    ans++, flg = true;
            if (flg) ans += T;
        }
        printf("%lld\n", ans);

        //cout << endl;

    }
    return 0;
}