#include <bits/stdc++.h>
using namespace std;

int N, W, ans;

class rec{
	public:
	int t, l, a, b, v;
}P[2010];
int f[2010][2010];

bool cmpa(const rec &A, const rec &B){
	if (A.a != B.a) return A.a < B.a;
	if (A.b != B.b) return A.b < B.b;
	if (A.t < B.t) return A.t < B.t;
	return 0;
}

int main(){
	freopen("F.in", "r", stdin);
	freopen("F_2.out", "w", stdout);
	while (scanf("%d%d", &N, &W) != EOF){
		for (int i = 1; i <= N; i++)
			scanf("%d%d%d%d%d", &P[i].t, &P[i].l, &P[i].a, &P[i].b, &P[i].v);
		P[N + 1].t = P[N + 1].l = P[N + 1].a = P[N + 1].b = P[N + 1].v = 0;
		P[N + 2] = P[N + 1];
		P[N + 2].t = 1;
		N += 2;
		sort(P + 1, P + N + 1, cmpa);
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
				for (int k = 1; k < i; k++){
					if (P[i].a < P[j].a) continue;
					if (P[k].t != 0) continue;
					if (f[k][j] < 0) continue;
					bool flag = 0;
					if (P[k].b <= P[j].a) flag = 1;
					if (P[k].b <= P[i].a && P[k].b > P[j].a && P[k].l + P[j].l <= W) flag = 1;
					if (P[k].b <= P[i].a && P[k].a >= P[j].b) flag = 1;
					if (!flag) continue;
					f[i][j] = max(f[i][j], f[k][j] + P[i].v);
				}
				for (int k = 1; k < j; k++){
					if (P[j].a < P[i].a) continue;
					if (P[k].t != 1) continue;
					if (f[i][k] < 0) continue;
					bool flag = 0;
					if (P[k].b <= P[i].a) flag = 1;
					if (P[k].b <= P[j].a && P[k].b > P[i].a && P[k].l + P[i].l <= W) flag = 1;
					if (P[k].b <= P[j].a && P[k].a >= P[i].b) flag = 1;
					if (!flag) continue;
					f[i][j] = max(f[i][j], f[i][k] + P[j].v);
				}
				ans = max(ans, f[i][j]);
			}
		}
		printf("%d\n", ans);
	}
}

