#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = (int)1e5 + 7;
const int mod = 999973;

struct nodetype
{
        int d, w[3];
        void Print()
        {
                cout << d << " : " << w[0] << ' ' << w[1] << ' ' << w[2] << endl;
        }
};

int N, M, ans, deg[MaxN], w[MaxN];
bool flg[MaxN];
vector<int> iv[MaxN], dt[MaxN], big;
nodetype lin[MaxN][4];
int tot, fir[mod], nxt[MaxN];
ll dat[MaxN]; int res[MaxN];

inline void Upload(int a, nodetype tmp)
{
        int i;
        for (i=2; i>=0; i--)
        {
                if (lin[a][i].d >= tmp.d) break;
                lin[a][i+1] = lin[a][i];
        }
        lin[a][i+1] = tmp;
}

inline void Update(int a, int b, int c)
{
        if (a > b) swap(a, b);
        if (a > c) swap(a, c);
        if (b > c) swap(b, c);
        int d = w[a] + w[b] + w[c];
        //cout << a << ' ' << b << ' ' << c << ' ' << d << endl;
        nodetype tmp;
        tmp.w[0] = a; tmp.w[1] = b; tmp.w[2] = c;
        tmp.d = d;
        //tmp.Print();
        Upload(a, tmp); Upload(b, tmp); Upload(c, tmp);
}

inline int CheckLink(int a, int b)
{
        if (a>b) swap(a, b);
        ll tmp = (ll)1e6 * a + b;
        for (int i=fir[tmp % mod]; i; i = nxt[i])
                if (dat[i] == tmp) return res[i];
        return 0;
}

void Init()
{
         int i,j,k,a,b,c;
        scanf("%d%d", &N, &M);
        for (i=1; i<=M; i++)
                for (j=0; j<4; j++)
                        lin[i][j].d = -(1<<30);
        for (i=1; i<=M; i++)
        {
                scanf("%d%d%d", &a, &b, w+i);
                deg[a]++; deg[b]++;
                iv[a].push_back(b); dt[a].push_back(i);
                iv[b].push_back(a); dt[b].push_back(i);
        
                if (a>b) swap(a, b);
                ll tmp = (ll)1e6 * a + b;
                c = tmp % mod;
                tot++; nxt[tot] = fir[c]; fir[c] = tot;
                dat[tot] = tmp; res[tot] = i;
        }
        int siz = (int) sqrt(N);
        for (i=1; i<=N; i++)
                if (deg[i] > siz)
                {
                        big.push_back(i);
                        flg[i] = true;
                }
                else
                {
                        for (a=0; a<iv[i].size(); a++)
                                for (b=a+1; b<iv[i].size(); b++)
                                {
                                        //cout << i << ' ' << iv[i][a] << ' ' << iv[i][b] << endl;
                                        c = CheckLink(iv[i][a], iv[i][b]);
                                        if (c!=0) Update(dt[i][a], dt[i][b], c);
                                }
                }
        //cout << endl;
        int l = big.size();
        //cout << "big: " ;
        //for (i=0; i<l; i++) cout << big[i] << ' ' ; cout << endl << endl;
        
        for (i=0; i<l; i++)
                for (j=i+1; j<l; j++)
                        for (k=j+1; k<l; k++)
                        {
                                a = CheckLink(big[i], big[j]);
                                if (a==0) continue;
                                b = CheckLink(big[i], big[k]);
                                if (b==0) continue;
                                c = CheckLink(big[j], big[k]);
                                if (c==0) continue;
                                Update(a, b, c);
                        }
}

inline bool Link(nodetype a, nodetype b)
{
        int i,j;
        for (i=j=0; i<3 && j<3; )
        {
                if (a.w[i] == b.w[j]) return true;
                if (a.w[i] < b.w[j]) i++;
                else j++;
        }
        return false;
}

inline bool Comp(int a, int b)
{
        for (int i=0; i<3; i++)
                if (lin[a][i].d < lin[b][i].d) return false;
                else if (lin[a][i].d > lin[b][i].d) return true;
        return true;
}

void Proc()
{
        int i, j, l1, l2, firline;
/*
        for (i=1; i<=M; i++)
        {
                for (j=0; j<3; j++)
                        cout << lin[i][j].d << ' ' ;
                cout << endl;
        }
*/
        for (i=1; i<=N; i++)
        {
                //cout << i << endl;
                if (dt[i].size() == 0) continue;
                firline = dt[i][0];
                for (j=1; j<dt[i].size(); j++)
                {
                        if (Comp(dt[i][j], firline)) firline = dt[i][j];
                }
                //cout << firline << endl;
                l1 = l2 = 0;
                for (j=0; j<dt[i].size(); j++)
                {
                        if (!Link(lin[dt[i][j]][0], lin[firline][0]))
                        {
                                //lin[dt[i][j]][0].Print(); lin[firline][0].Print(); cout << endl;
                                ans = max(ans, lin[firline][0].d + lin[dt[i][j]][0].d);
                        }
                        if (dt[i][j] == lin[firline][0].w[0] || dt[i][j] == lin[firline][0].w[1] || dt[i][j] == lin[firline][0].w[2])
                        {
                                if (l1 == 0) l1 = dt[i][j];
                                else l2 = dt[i][j];
                        }
                }
                //cout << "==" << l1 << ' ' << l2 << endl;
                if (!Link(lin[l1][1], lin[l2][1])) ans = max(ans, lin[l1][1].d + lin[l2][1].d);
                if (!Link(lin[l1][1], lin[l2][2])) ans = max(ans, lin[l1][1].d + lin[l2][2].d);
                if (!Link(lin[l1][2], lin[l2][1])) ans = max(ans, lin[l1][2].d + lin[l2][1].d);
                //cout << endl;
        }
        if (ans == 0) printf("-1\n");
        else printf("%d\n", ans);
}

int main()
{
        
        Init();
        Proc();
        return 0;
}