#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)1e5 + 7;
const int limit = 13;

int N, M;
double p[MaxN];
double s[MaxN<<2][limit+1], ts[MaxN<<2][limit+1];

void MakeSeg(int x, int le, int ri)
{
        for (int id = 1; id <= limit; id ++)
                ts[x][id] = 1.0;
        if (le == ri)
        {
                double ss = p[le];
                for (int id = 1; id <= limit; id ++, ss *= p[le])
                        s[x][id] = ss / id;
                return;
        }
        int mi = (le + ri) >> 1, lc = x<<1;
        MakeSeg(lc, le, mi);
        MakeSeg(lc+1, mi+1, ri);
        for (int id = 1; id <= limit; id ++)
                s[x][id] = s[lc][id] + s[lc+1][id];
}

void Download(int x)
{
        int lc = x<<1;
        for (int id = 1; id <= limit; id++)
                if (ts[x][id] != 1.0){
                        ts[lc][id] *= ts[x][id]; ts[lc+1][id] *= ts[x][id];
                        s[lc][id] *= ts[x][id]; s[lc+1][id] *= ts[x][id];
                        ts[x][id] = 1.0;
                }
}

void Update(int x, int le, int ri, int lee, int rii, double tmp)
{
        if (le <= lee && rii <= ri)
        {
                double ss = tmp;
                for (int id = 1; id <= limit; id++, ss *= tmp){
                        ts[x][id] *= ss;
                        s[x][id] *= ss;
                }
                return;
        }
        int lc = x<<1;
        int mid = (lee + rii) >> 1;
        Download(x);
        if (le <= mid) Update(lc, le, ri, lee, mid, tmp);
        if (ri > mid) Update(lc+1, le, ri, mid + 1, rii, tmp);
        for (int id = 1; id <= limit; id++)
                s[x][id] = s[lc][id] + s[lc+1][id];
}

inline double Calc(int x, int le, int ri, int lee, int rii)
{
        if (le <= lee && rii <= ri){
                double res = 0;
                for (int id = 1; id <= limit; id ++)
                        res += s[x][id];
                return res;
        }
        int lc = x<<1; double ans = 0.0;
        int mid = (lee + rii) >> 1;
        Download(x);
        if (le <= mid) ans += Calc(lc, le, ri, lee, mid);
        if (ri > mid) ans += Calc(lc+1, le, ri, mid + 1, rii);
        return ans;
}

void Proc()
{
        int i, typ, l, r; double k, ans;
        for (i=1; i<=N; i++)
                scanf("%lf", p+i);
        MakeSeg(1, 1, N);
        for (i=1; i<=M; i++)
        {
                scanf("%d", &typ);
                if (typ == 0)
                {
                        scanf("%d%d", &l, &r);
                        ans = Calc(1, l, r, 1, N);
                        printf("-%.16lf\n", ans);
                }
                else
                {
                        scanf("%d%d%lf", &l, &r, &k);
                        Update(1, l, r, 1, N, k);
                }
        }
}