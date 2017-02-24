#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int limit = 3;
int N, Q, pt, len, lca, ans;
int st[200010], ne[400010], go[400010];
int W[19][400010], fa[19][400010];
int dep[200010], in[200010], out[200010];
int Dia[400010][4];
int dp[200010][limit], dpx[200010][limit];
int dpl[200010][limit], dplx[200010][limit], dply[200010][limit];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

int get_lca(int x, int y){
	if (x == y) return x;
	if (in[x] > in[y])
		swap(x, y);
	if (out[x] > out[y])
		return x;
	int l = in[x], r = in[y];
	int delta = r - l + 1;
	int step = log(delta) / log(2);
	int t1 = W[step][l];
	int t2 = W[step][r - (1 << step) + 1];
	if (dep[t1] > dep[t2]) swap(t1, t2);
	return go[fa[0][t1]];
}

int get_dist(int x, int y){
	int ll = get_lca(x, y);
	return dep[x] + dep[y] - 2 * dep[ll];
}

void get_Twice(){
	for (int i = 1, s = 1; i <= 18; i++, s <<= 1)
		for (int j = 1; j <= len; j++){
			W[i][j] = W[i - 1][j];
			if (j + s <= len && dep[W[i - 1][j]] > dep[W[i - 1][j + s]])
				W[i][j] = W[i - 1][j + s];
			fa[i][j] = fa[i - 1][go[fa[i - 1][j]]];
		}
}

int get_middle(int x, int y, int k){
	bool flag = 0;
	if (get_dist(x, lca) < k){
		k = get_dist(x, y) - k + 1;
		swap(x, y);
		flag = 1;
	}
	for (int i = 17; i >= 0; i--)
		if (k > (1 << i)){
			k -= (1 << i);
			x = go[fa[i][x]];
		}
	return fa[0][x] ^ flag;
}

void renew(int x, int y){
	for (int i = 0; i < limit; i++){
		if (dp[y][0] + 1 > dp[x][i]){
			for (int j = limit - 1; j > i; j--){
				dp[x][j] = dp[x][j - 1];
				dpx[x][j] = dpx[x][j - 1];
			}
			dp[x][i] = dp[y][0] + 1;
			dpx[x][i] = dpx[y][0];
			break;
		}
	}
	int l = dpl[y][0];
	int lx = dplx[y][0];
	int ly = dply[y][0];
	if (l < dp[y][0] + dp[y][1]){
		l = dp[y][0] + dp[y][1];
		lx = dpx[y][0];
		ly = dpx[y][1];
		if (lx > ly) swap(lx, ly);
	}
	for (int i = 0; i < limit; i++){
		if (l > dpl[x][i]){
			for (int j = limit - 1; j > i; j--){
				dpl[x][j] = dpl[x][j - 1];
				dplx[x][j] = dplx[x][j - 1];
				dply[x][j] = dply[x][j - 1];
			}
			dpl[x][i] = l;
			dplx[x][i] = lx;
			dply[x][i] = ly;
			break;
		}
	}
}

void delet(int x, int y){
	for (int i = 0; i < limit; i++)
		if (dpx[x][i] == dpx[y][0]){
			for (int j = i; j + 1 < limit; j++){
				dp[x][j] = dp[x][j + 1];
				dpx[x][j] = dpx[x][j + 1];
			}
			dp[x][limit - 1] = 0;
			dpx[x][limit - 1] = x;
			break;
		}
	int l = dpl[y][0];
	int lx = dplx[y][0];
	int ly = dply[y][0];
	if (l < dp[y][0] + dp[y][1]){
		l = dp[y][0] + dp[y][1];
		lx = dpx[y][0];
		ly = dpx[y][1];
		if (lx > ly) swap(lx, ly);
	}
	for (int i = 0; i < limit; i++)
		if (dplx[x][i] == lx && dply[x][i] == ly){
			for (int j = i; j + 1 < limit; j++){
				dpl[x][j] = dpl[x][j + 1];
				dplx[x][j] = dplx[x][j + 1];
				dply[x][j] = dply[x][j + 1];
			}
			dpl[x][limit - 1] = 0;
			dplx[x][limit - 1] = x;
			dply[x][limit - 1] = x;
			break;
		}
}

void dfs(int x){
	W[0][++len] = x;
	in[x] = len;
	
	for (int i = st[x]; i; i = ne[i])
		if (i != fa[0][x]){
			int y = go[i];
			dep[y] = dep[x] + 1;
			fa[0][y] = i ^ 1;
			dfs(y);
			renew(x, y);
		}
	
	W[0][++len] = x;
	out[x] = len;
}

void change_root(int x, int y){
	delet(x, y);
	renew(y, x);
}

void DP_Rotate(int x){
	for (int i = st[x]; i; i = ne[i])
		if (i != fa[0][x]){
			int y = go[i];
			Dia[i][0] = dpx[y][0];
			Dia[i][1] = dpx[y][1];
			Dia[i][2] = dplx[y][0];
			Dia[i][3] = dply[y][0];
			change_root(x, y);
			
			DP_Rotate(y);
			
			Dia[i ^ 1][0] = dpx[x][0];
			Dia[i ^ 1][1] = dpx[x][1];
			Dia[i ^ 1][2] = dplx[x][0];
			Dia[i ^ 1][3] = dply[x][0];
			change_root(y, x);
		}
}

int main(){
	freopen("I.in", "r", stdin);
	freopen("I.out", "w", stdout);
	while (scanf("%d%d", &N, &Q) != EOF){
		for (int i = 1; i <= N; i++){
			st[i] = 0;
			dep[i] = 0;
			for (int j = 0; j < limit; j++){
				dp[i][j] = dpl[i][j] = 0;
				dpx[i][j] = dplx[i][j] = dply[i][j] = i;
			}
			for (int j = 0; j <= 18; j++)
				fa[j][i] = 0;
		}
		pt = 1;
		for (int i = 1; i < N; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			Add(x, y);
			Add(y, x);
		}
		for (int i = 1; i <= pt; i++)
			Dia[i][0] = Dia[i][1] = 0;
		len = 0;
		dep[1] = 1;
		dfs(1);
		DP_Rotate(1);
		get_Twice();
		for (int i = 1; i <= Q; i++){
			int x, y, k;
			scanf("%d%d%d", &x, &y, &k);
			lca = get_lca(x, y);
			int d = get_dist(x, y);
			if ((k & 1) && !(d & 1)){
				printf("1\n");
			}
			else if (!(k & 1) && (d & 1)){
				printf("0\n");
			}else if (!(k & 1) && !(d & 1)){
				if (k / 2 >= d){
					printf("-1\n");
					continue;
				}
				int m = get_middle(y, x, k / 2 + 1);
				ans = 0;
				ans = max(ans, get_dist(x, go[m]));
				for (int j = 0; j < 4; j++)
					ans = max(ans, get_dist(x, Dia[m][j]));
				if (ans >= k / 2) printf("0\n");
				else printf("-1\n");
			}else{
				if ((k + 1) / 2 >= d){
					printf("2\n");
					continue;
				}
				int m = get_middle(x, y, (k + 1) / 2 + 1);
				ans = 0;
				ans = max(ans, get_dist(y, go[m]));
				for (int j = 0; j < 4; j++)
					ans = max(ans, get_dist(y, Dia[m][j]));
				if (ans >= k / 2) printf("1\n");
				else printf("2\n");
			}
		}
	}
}