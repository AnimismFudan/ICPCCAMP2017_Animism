#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int pp = (1e9) + 7;
int N, M, pt, Unt, Cnt, ans;
int R[200010], fa[200010], update[200010];
bool vis[200010];
int st[200010], ne[400010], go[400010];

LL ran(){
	LL t = 0;
	for (int i = 0; i < 4; i++)
		t = (t << 16) ^ (rand() % 65536);
	return t;
}

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

int C2(int x){
	return x * (x - 1) / 2;
}

int quick(int x, int y){
	if (y < 0) return 0;
	int s = 1, t = x;
	for (; y; y >>= 1){
		if (y & 1) s = (LL)s * t % pp;
		t = (LL)t * t % pp;
	}
	return s;
}

void dfs(int x){
	vis[x] = 1;
	for (int i = st[x]; i; i = ne[i])
		if (fa[x] != i){
			if (!vis[go[i]]){
				fa[go[i]] = i ^ 1;
				dfs(go[i]);
			}else if (!R[i >> 1]){
				Unt++;
				R[i >> 1] = ran();
			}
		}
}

LL pushR(int x){
	vis[x] = 1;
	LL s = 0;
	for (int i = st[x]; i; i = ne[i])
		if ((i ^ 1) == fa[go[i]]){
			LL t = pushR(go[i]);
			R[i >> 1] = t;
			s ^= t;
		}
	s ^= update[x];
	return s;
}

int main(){
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
	while (scanf("%d%d", &N, &M) != EOF){
		memset(R, 0, sizeof(R));
		memset(st, 0, sizeof(st));
		memset(fa, 0, sizeof(fa));
		memset(vis, 0, sizeof(vis));
		memset(update, 0, sizeof(update));
		
		Unt = Cnt = 0;
		pt = 1;
		for (int i = 1; i <= M; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			Add(x, y);
			Add(y, x);
		}
		for (int i = 1; i <= N; i++)
			if (!vis[i])
				dfs(i);
		for (int i = 1; i <= M; i++)
			if (R[i] != 0){
				int x = go[i << 1];
				int y = go[(i << 1) + 1];
				update[x] ^= R[i];
				update[y] ^= R[i];
			}
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= N; i++)
			if (!vis[i])
				pushR(i);
		for (int i = 1; i <= M; i++)
			if (R[i]) Cnt++;
		ans = 0;
		ans = (ans + (LL)quick(2, Unt - 2) * C2(Cnt) % pp) % pp;
		sort(R + 1, R + M + 1);
		for (int i = 1; i <= M;){
			int j = i;
			for (; j <= M && R[i] == R[j]; j++);
			if (R[i]){
				ans = (ans - (LL)quick(2, Unt - 2) * C2(j - i) % pp) % pp;
				ans = (ans + (LL)quick(2, Unt - 1) * C2(j - i) % pp) % pp;
			}
			i = j;
		}
		ans = ans * 2 % pp;
		ans = (ans + (LL)quick(2, Unt - 1) * Cnt) % pp;
		printf("%d\n", ans);
	}
}