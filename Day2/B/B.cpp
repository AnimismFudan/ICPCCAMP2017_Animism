#include <bits/stdc++.h>
using namespace std;

const int MaxN = (int)2e5 + 7;

int N, M, col[MaxN];
vector<int> iv[MaxN];

bool DFS(int u)
{
        int i, v;
        for (i=0; i<iv[u].size(); i++)
        {
                v = iv[u][i];
                if (col[u] == col[v]) return true;
                if (!col[v])
                {
                        col[v] = 3 - col[u];
                        if(DFS(v)) return true;
                }
        }
        return false;
}

void Proc()
{
        int i,a,b;
        for (i=1; i<=N; i++)
                col[i] = 0, iv[i].clear();
        
        for (i=1; i<=M; i++)
        {
                scanf("%d%d", &a, &b);
                iv[a].push_back(b);
                iv[b].push_back(a);
        }
        
        col[1] = 1;
        if (DFS(1)) printf("0\n");
        else printf("1\n");
        
        //for (i=1; i<=N; i++) cout << col[i] << ' '; cout << endl;
}
                

int main()
{
        while (scanf("%d%d", &N, &M) != EOF)
                Proc();
        return 0;
}