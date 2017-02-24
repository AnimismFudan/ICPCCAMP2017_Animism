#include <bits/stdc++.h>
using namespace std;

const int limit = 13;
int N, M, now, col, ans;
int pow3[20];
bool B[51][51];
int f[51][1600000];

void dfs(int step, int s){
	if (step > limit){
		int t = s - col * pow3[limit];
		f[now][s / 3] += f[now - 1][t];
		f[now][s / 3] &= 3;
		return;
	}
	if (now - step <= 0 || !B[now - step][now]){
		dfs(step + 1, s * 3);
		dfs(step + 1, s * 3 + 1);
		dfs(step + 1, s * 3 + 2);
	}else{
		if (col != 1) dfs(step + 1, s * 3);
		if (col != 0) dfs(step + 1, s * 3 + 1);
		dfs(step + 1, s * 3 + 2);
	}
}

int main(){
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
	pow3[0] = 1;
	for (int i = 1; i <= limit; i++)
		pow3[i] = pow3[i - 1] * 3;
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		if (x > y) swap(x, y);
		B[x][y] = 1;
	}
	for (int i = 0; i < 3; i++)
		f[1][i * pow3[limit - 1]] = 1;
	for (now = 2; now <= N; now++)
		for (col = 0; col < 3; col++)
			dfs(1, col);
	ans = 0;
	for (int i = 0; i < pow3[limit]; i++)
		ans = (ans + f[N][i]) & 3;
	ans = ans - 1;
	ans = ans & 3;
	printf("%d", ans >> 1);
}