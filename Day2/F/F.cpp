#include <bits/stdc++.h>
using namespace std;

int N, W, ans, len;

class rec{
	public:
	int t, l, a, b, v;
}P[2010];
int D1[2010], D2[2010];
int D[4][2010][4010];
int ls[4010];
int f[2010][2010];

int lowbit(int x){
	return x & -x;
}

void Init(int t, int x, int y, int data){
	for (; y <= len; y += lowbit(y))
		D[t][x][y] = max(D[t][x][y], data);
}

int calc(int t, int x, int y){
	int res = -2e9;
	for (; y; y -= lowbit(y))
		res = max(res, D[t][x][y]);
	return res;
}

bool cmpa(const rec &A, const rec &B){
	if (A.a != B.a) return A.a < B.a;
	if (A.b != B.b) return A.b < B.b;
	if (A.t < B.t) return A.t < B.t;
	return 0;
}

int main(){
	freopen("F.in", "r", stdin);
	freopen("F.out", "w", stdout);
	while (scanf("%d%d", &N, &W) != EOF){
		ls[len = 1] = 0;
		for (int i = 1; i <= N; i++){
			scanf("%d%d%d%d%d", &P[i].t, &P[i].l, &P[i].a, &P[i].b, &P[i].v);
			ls[++len] = P[i].a;
			ls[++len] = P[i].b;
		}
		P[N + 1].t = P[N + 1].l = P[N + 1].a = P[N + 1].b = P[N + 1].v = 0;
		P[N + 2] = P[N + 1];
		P[N + 2].t = 1;
		N += 2;
		sort(P + 1, P + N + 1, cmpa);
		sort(ls + 1, ls + len + 1);
		len = unique(ls + 1, ls + len + 1) - ls - 1;
		for (int i = 1; i <= N; i++){
			P[i].a = lower_bound(ls + 1, ls + len + 1, P[i].a) - ls;
			P[i].b = lower_bound(ls + 1, ls + len + 1, P[i].b) - ls;
		}
		for (int i = 1; i <= N; i++){
			D1[i] = D2[i] = -2e9;
			for (int k = 0; k < 4; k++)
				for (int j = 0; j <= len; j++)
					D[k][i][j] = -2e9;
		}
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				f[i][j] = -2e9;
		f[1][2] = 0;
		ans = 0;
		for (int i = 1; i <= N; i++){
			if (P[i].t != 0) continue;
			for (int j = 1; j <= N; j++){
				if (P[j].t != 1) continue;
				if (P[i].l + P[j].l > W && max(P[i].a, P[j].a) <= min(P[i].b, P[j].b))
					continue;
				if (P[i].a >= P[j].a){
					f[i][j] = max(f[i][j], D1[j] + P[i].v);
					f[i][j] = max(f[i][j], calc(0, j, P[i].a) + P[i].v);
					f[i][j] = max(f[i][j], calc(2, j, P[i].a) + P[i].v);
				}
				if (P[j].a >= P[i].a){
					f[i][j] = max(f[i][j], D2[i] + P[j].v);
					f[i][j] = max(f[i][j], calc(1 ,i, P[j].a) + P[j].v);
					f[i][j] = max(f[i][j], calc(3 ,i, P[j].a) + P[j].v);
				}
				ans = max(ans, f[i][j]);
				if (P[i].b <= P[j].a) D1[j] = max(D1[j], f[i][j]);
				if (P[j].b <= P[i].a) D2[i] = max(D2[i], f[i][j]);
				if (P[i].l <= W - P[j].l) Init(0, j, P[i].b, f[i][j]);
				if (P[i].l <= W - P[j].l) Init(1, i, P[j].b, f[i][j]);
				if (P[i].a >= P[j].b) Init(2, j, P[i].b, f[i][j]);
				if (P[j].a >= P[i].b) Init(3, i, P[j].b, f[i][j]);
//				if (P[k].b <= P[i].a && P[k].a > P[j].b) flag = 1;
//				if (P[k].b <= P[j].a && P[k].a > P[i].b) D6[i] = max(D6[i], f[i][j]);
			}
		}
		printf("%d\n", ans);
	}
}

