#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MaxN = (int)1e6 + 7;
const int MaxM = 6;

int N, M, mod, fa[MaxN];

struct nodetype
{
	int mat[MaxM][MaxM];
	void Read()
	{
		int i, j;
		for (i=1; i<=M; i++)
			for (j=1; j<=M; j++)
				scanf("%d", &mat[i][j]);
	}
	void Print()
	{
		int i, j;
		for (i=1; i<=M; i++)
		{
			for (j=1; j<=M; j++)
				printf("%d ", mat[i][j]);
			printf("\n");
		}
	}
	void SetE()
	{
		int i;
		memset(mat, 0, sizeof(mat));
		for (i=1; i<=M; i++)
			mat[i][i] = 1;
	}
} A, B, f[MaxN];

nodetype Mult(nodetype A, nodetype B)
{
	int i,j,k; nodetype C;
	memset(C.mat, 0, sizeof(C.mat));
	for (i=1; i<=M; i++)
		for (j=1; j<=M; j++){
			ll res = 0;
			for (k=1; k<=M; k++)
				res += (ll)A.mat[i][k] * B.mat[k][j];
			 C.mat[i][j] = res % mod;
		}
	return C;
}

int FindF(int x)
{
	if (fa[x] == x) return x;
	int i = fa[x];
	fa[x] = FindF(i);
	f[x] = Mult(f[x], f[i]);
	return fa[x];
}

void Proc()
{
	int i, j;
	for (i=0; i<=N; i++)
		fa[i] = i;

	A.Read(); B.Read(); f[0] = A;

	for (i=1; i<=N; i++)
	{
		scanf("%d", &j);
		fa[i - 1] = i;
		f[i].SetE();
		FindF(j);
		f[i] = Mult(f[j], B);
	}

	f[N].Print();
}

int main()
{
		freopen("G.in", "r", stdin);
		freopen("G.out", "w", stdout);

	while (scanf("%d%d%d", &N, &M, &mod) != EOF)
		Proc();
	return 0;
}