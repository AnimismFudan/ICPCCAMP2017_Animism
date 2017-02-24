#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = (int)1e6 + 7;

int T, N, a[MaxN];
ll ans, s[MaxN], seg[MaxN];

int main()
{
        //freopen("I.in", "r", stdin);
        
        scanf("%d", &T);
        while (T--)
        {
                scanf("%d", &N); ans = -(1LL << 60);
                for (int i=1; i<=N; i++)
                {
                        scanf("%d", a+i);
                        s[i] = s[i-1] + a[i];
                }
                for (int i=1; i<=N; i++)
                {
                        ans = max(ans, s[i] - seg[i-1]);
                        if (i != 1) seg[i] = min(seg[i-2], s[i]);
                        else seg[i] = s[i];
                        //cout << i << ' ' << s[i] << ' ' <<seg[i-1] << ' ' << seg[i] << ' ' << endl;
                }
                printf("%lld\n", ans);
        }
        return 0;
}