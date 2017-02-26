#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

#define pir pair <int, int>
#define ll long long

const int MaxN = (int)5e5 + 7;
const int mod1 = 99999973;
const int mod2 = (int)1e9 + 7;

int T, N, M, tot;
string str[MaxN];
vector<pir> pre[MaxN], suf[MaxN];
vector<int> iv[2][MaxN];
map<pir, int> premp, sufmp;
char ctmp[MaxN];

void Init()
{
        scanf("%d", &N); M = 0;
        //cerr << N << endl;
        premp.clear(); sufmp.clear();
        for (int i=1; i<=N; i++)
        {
        		scanf("%s", ctmp);
        		str[i] = string(ctmp);
                //cin >> str[i];
                M += str[i].size();
        }
        //cerr << str[1] << endl;
        for (int i=1; i<=M; i++)
        {
                pre[i].clear(); suf[i].clear();
                iv[0][i].clear(); iv[1][i].clear();
        }

        tot = 0;
        for (int i=1; i<=N; i++)
        {
                int l, tmp1, tmp2;
                l = str[i].size(); tmp1 = tmp2 = 0;
                for (int j=0; j<l; j++)
                {
                        tmp1 = ((ll)tmp1 * 27 + (str[i][j] - 'a' + 1)) % mod1;
                        tmp2 = ((ll)tmp2 * 27 + (str[i][j] - 'a' + 1)) % mod2;
                        pir tmp = make_pair(tmp1, tmp2);
                        pre[i].push_back(tmp);
                        if (premp.find(tmp) == premp.end())
                            premp[tmp] = ++tot;

                        //cout << str[i].substr(0, j+1) << ' ' << tmp1 << ' ' << tmp2 << ' ' << premp[tmp] << endl;
                }
        }
        tot = 0;
        for (int i=1; i<=N; i++)
        {
                int l, tmp1, tmp2;
                l = str[i].size(); tmp1 = tmp2 = 0;
                for (int j=l-1; j>=0; j--)
                {
                        tmp1 = ((ll)tmp1 * 27 + (str[i][j] - 'a' + 1)) % mod1;
                        tmp2 = ((ll)tmp2 * 27 + (str[i][j] - 'a' + 1)) % mod2;
                        pir tmp = make_pair(tmp1, tmp2);
                        suf[i].push_back(tmp);
                        if (sufmp.find(tmp) == sufmp.end())
                            sufmp[tmp] = ++tot;

                        //cout << str[i].substr(j, str[i].size()) << ' ' << tmp1 << ' ' << tmp2 << ' ' << sufmp[tmp] << endl;
                }

                for (int j=0; j+1<l; j++)
                {
                        int a = premp[pre[i][j]], b = sufmp[suf[i][l - j - 2]];
                        iv[0][a].push_back(b);
                        iv[1][b].push_back(a);
                    //    iv[0][premp[pre[i][j]]].push_back(sufmp[suf[i][l - j - 2]]);
                    //    iv[1][sufmp[suf[i][l - j - 2]]].push_back(premp[pre[i][j]]);
                }
        }
/*
        for (int i=1; i<=N; i++)
                for (int j=0; j+1 <str[i].size(); j++)
                        cout << premp[pre[i][j]] << ' ' << sufmp[suf[i][str[i].size() - j - 2]] << endl;
*/
        for (int i=1; i<=M; i++)
        {
                if (iv[0][i].size() != 0)
                {
                        sort(iv[0][i].begin(), iv[0][i].end());
                        iv[0][i].erase(unique(iv[0][i].begin(), iv[0][i].end()), iv[0][i].end());
                }
                if (iv[1][i].size() != 0)
                {
                        sort(iv[1][i].begin(), iv[1][i].end());
                        iv[1][i].erase(unique(iv[1][i].begin(), iv[1][i].end()), iv[1][i].end());
                }
        }
}

void Print(int a, int b, int c, int d) // ac ; bd
{
        //cout << a << ' ' << b << ' ' << c << ' ' << d << endl;

        string sa, sb, sc, sd;
        sa = sb = sc = sd = "";
        for (int i=1; i<=N; i++)
                for (int j=0; j<str[i].size(); j++)
                {
                        if (premp[pre[i][j]] == a) sa = str[i].substr(0, j+1);
                        if (premp[pre[i][j]] == b) sb = str[i].substr(0, j+1);
                        if (sufmp[suf[i][str[i].size() - j - 1]] == c) sc = str[i].substr(j, str[i].size());
                        if (sufmp[suf[i][str[i].size() - j - 1]] == d) sd = str[i].substr(j, str[i].size());
                }
        printf("YES\n");
        cout << sa << sc << ' ' << sb << sd << endl;
        cout << sa << sd << ' ' << sb << sc << endl;
}

int vis[MaxN];
queue<int> mq;

bool BFS(int x)
{
        for (int i=1; i<=M; i++) vis[i] = 0;
        while(!mq.empty()) mq.pop();
        for (int i=0; i<iv[0][x].size(); i++)
        {
                //cerr << iv[0][x][i] << ' ' ;
                mq.push(iv[0][x][i]);
        }
        while (!mq.empty())
        {
                int u = mq.front();
                for (int i=0; i<iv[1][u].size(); i++)
                {
                        if (vis[iv[1][u][i]] != 0 && x != iv[1][u][i])
                        {
                                Print(x, iv[1][u][i], vis[iv[1][u][i]], u);
                                return true;
                        }
                        vis[iv[1][u][i]] = u;
                }
                mq.pop();
        }
        return false;
}

vector<int> sml[MaxN], yyh[MaxN];
int flg[MaxN];

bool DealSmall(int x)
{
        for (int i=0; i<iv[0][x].size(); i++)
                for (int j=i+1; j<iv[0][x].size(); j++)
                {
                	if (iv[0][x][i] < iv[0][x][j])
                	{
                		sml[iv[0][x][i]].push_back(iv[0][x][j]);
                		yyh[iv[0][x][i]].push_back(x);
                	}
                	else
                	{
	                	sml[iv[0][x][j]].push_back(iv[0][x][i]);
    	            	yyh[iv[0][x][j]].push_back(x);
    	            }
                }
        return false;
}

void Proc()
{
        int siz = min(300, (int)sqrt(M));
        //mp.clear();
        //cerr << M << endl;
        for (int i=1; i<=M; i++)
        {
        	flg[i] = 0;
        	sml[i].clear();
        	yyh[i].clear();
        }
        for (int i=1; i<=M; i++)
                if (iv[0][i].size() > siz)
                {
                        if(BFS(i)) return;
                }
                else
                {
                        if (DealSmall(i)) return;
                }

        //for (int i=1; i<=M; i++)
        //	cerr << sml[i].size() << endl;
        for (int i=1; i<=M; i++)
        {
        	for (int j=0; j<sml[i].size(); j++)
        	{
        		//cerr << i << ' ' << j << ' ' << sml[i].size() << ' ' <<sml[i][j] << endl;
        		if (flg[sml[i][j]] != 0)
        		{
        			Print(flg[sml[i][j]], yyh[i][j], i, sml[i][j]);
        			return;
        		}
        		flg[sml[i][j]] = yyh[i][j];
        	}
        	for (int j=0; j<sml[i].size(); j++)
        		flg[sml[i][j]] = 0;
        	//cerr << i << ' ' << M << endl;
    	}

        printf("NO\n");
}

int main()
{
        freopen("J.in", "r", stdin);

        scanf("%d", &T);
        while (T--)
        {
                Init();
                Proc();
        }

        return 0;
}
