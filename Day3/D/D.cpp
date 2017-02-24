#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, M;
LL ans, ansout;
int a[110][110], b[110][110];
int A[110][110], B[110][110], C[110][110];

void pri(){
	ans = 0;
	for (int i = 0; i <= N; i++)
		for (int j = 1; j <= M; j++)
			if (a[i][j])
				ans += A[i][j];
	for (int i = 1; i <= N; i++)
		for (int j = 0; j <= M; j++)
			if (b[i][j])
				ans += B[i][j];
	ansout = max(ansout, ans);
	
/*	for (int j = 1; j<= M; j++){
		printf(" ");
		if (a[0][j]) printf("-");
		else printf(" ");
	}
	printf(" \n");
	for (int i = 1; i <= N; i++){
		for (int j = 0; j <= M; j++){
			if (b[i][j]) printf("|");
			else printf(" ");
			if (j < M) printf(" ");
			else printf("\n");
		}
		for (int j = 1; j<= M; j++){
			printf(" ");
			if (a[i][j]) printf("-");
			else printf(" ");
		}
		printf(" \n");
	}*/
}

void check(){
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	if (C[1][1] == 4)
		a[0][1] = b[1][0] = 1;
	else if (C[1][1] == 3) return;
	else a[0][1] = b[1][0] = 0;
	for (int j = 2; j <= M; j++)
		if (a[0][j - 1]){
			a[0][j] = 0;
			b[1][j - 1] = 1;
		}else a[0][j] = b[1][j - 1] = (C[1][j] > 2);
	if (a[0][M]) b[1][M] = 1;
	for (int i = 2; i <= N; i++){
		if (b[i - 1][0]){
			a[i - 1][1] = 1;
			b[i][0] = 0;
		}else{
			a[i - 1][1] = C[i - 1][1] - a[i - 2][1] - b[i - 1][0] - b[i - 1][1];
			if (a[i - 1][1] < 0 || a[i - 1][1] > 1) return;
			b[i][0] = a[i - 1][1];
		}
		for (int j = 2; j <= M; j++){
			if (b[i - 1][j - 1] && a[i - 1][j - 1]){
				b[i][j - 1] = 0;
				a[i - 1][j] = 0;
			}
			else if (b[i - 1][j - 1] && !a[i - 1][j - 1]){
				a[i - 1][j]= 1;
				b[i][j - 1] = 0;
			}else if (!b[i - 1][j - 1] && a[i - 1][j - 1]){
				a[i - 1][j]= 0;
				b[i][j - 1] = 1;
			}else{
				a[i - 1][j] = C[i - 1][j] - a[i - 2][j] - b[i - 1][j - 1] - b[i - 1][j];
				if (a[i - 1][j] < 0 || a[i - 1][j] > 1) return;
				b[i][j - 1] = a[i - 1][j];
			}
		}
		b[i][M] = a[i - 1][M] && !b[i - 1][M];
	}
	a[N][1] = b[N][0];
	for (int i = 2; i <= M; i++)
		if (b[N][i - 1] && !a[N][i - 1])
			a[N][i] = 1;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++){
			int res = a[i][j] + b[i][j] + a[i - 1][j] + b[i][j - 1];
			if (res != C[i][j])
				return;
		}
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= M; j++){
			int res = 0;
			if (j < M) res += a[i][j + 1];
			if (i < N) res += b[i + 1][j];
			if (j > 0) res += a[i][j];
			if (i > 0) res += b[i][j];
			if (res != 0 && res != 2) return;
			if (j > 0 && j < M){
				if (a[i][j] && a[i][j + 1]) return;
			}
			if (i > 0 && i < N){
				if (b[i][j] && b[i + 1][j]) return;
			}
		}
	pri();
}

int main(){
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
	while (scanf("%d%d", &N, &M) != EOF){
		for (int i = 1; i<= N; i++)
			for (int j = 1; j <= M; j++)
				scanf("%d", &C[i][j]);
		for (int i = 0; i <= N; i++)
			for (int j = 1; j <= M; j++)
				scanf("%d", &A[i][j]);
		for (int i = 1; i <= N; i++)
			for (int j = 0; j <= M; j++)
				scanf("%d", &B[i][j]);
		ansout = -1;
		check();
		cout << ansout << endl;
	}
}