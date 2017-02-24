#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <bitset>
#include <algorithm>
using namespace std;

#define ll long long

const int MaxN = (int)1e3 + 7;

char str[MaxN];
bitset<MaxN> bst[MaxN];
int n;
ll ans, siz[MaxN], tri[MaxN], cnt[10];
int wei[10] = {0, 2, 12, 6, 12, 24, 24, 36, 48, 12};

int main()
{
        //freopen("B.in", "r", stdin);

        while (scanf("%d", &n) != EOF)
        {
                for (int i=1; i<10; i++)
                        cnt[i] = 0;
                for (int i=1; i<=n; i++)
                        tri[i] = 0, bst[i] = 0;

                for (int i=1; i<=n; i++)
                {
                        scanf("%s", str+1);
                        for (int j=1; j<=n; j++)
                        {
                                bst[i][j] = str[j] - '0';
                        }
                        siz[i] = bst[i].count();

                        cnt[1] += siz[i];
                        cnt[2] += siz[i] * (siz[i] - 1) / 2;
                        cnt[4] += siz[i] * (siz[i] - 1) * (siz[i] - 2) / 6;
                }
                cnt[1] /= 2;
                for (int i=1; i<=n; i++)
                        for (int j=1; j<=n; j++)
                        {
                                if (i==j) continue;
                                ll k = (bst[i] & bst[j]).count();
                                cnt[8] += k * (k-1);
                                cnt[9] += k * (k-1) / 2 * (siz[i] - 2);
                                if (bst[i][j] == 1)
                                {
                                        //cout << i << ' ' << j << ' ' << k << endl;
                                        cnt[3] += (siz[i] - 1) * (siz[j] - 1);
                                        tri[i] += k;
                                        cnt[5] += k; cnt[7] += k * (k-1) / 2;
                                        //cout << k*(k-1)/2 << endl;
                                }
                        }

                for (int i=1; i<=n; i++)
                {
                        tri[i] /= 2;
                        //cout << tri[i] << ' ';
                        cnt[6] += tri[i] * (tri[i] - 1);
                }
                //cout << endl;

                //cout << cnt[5] << endl;

                cnt[7] /= 2;
                cnt[6] /= 2; cnt[6] -= cnt[7] * 2;
                cnt[8] /= 8; //cnt[9] /= 8; 
                cnt[9] -= 2 * cnt[7];
                cnt[5] /= 6; cnt[3] = cnt[3] / 2 - cnt[5] * 3;
/*
                for (int i=1; i<10; i++)
                        printf("%lld ", cnt[i]);
                printf("\n");
*/
                ans = 0;
                for (int i=1; i<10; i++)
                {
                        //cout << cnt[i] << ' ';
                        ans += cnt[i] * wei[i];
                }
                //cout << endl;
                printf("%lld\n", ans);

                for (int i=1; i<=n; i++)
                        bst[i] = 0;
        }
        return 0;
}