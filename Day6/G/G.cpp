#include <bits/stdc++.h>
using namespace std;

int N, M, len;

class rec{
        public:
        int a[4];
}ans[4000010];

char A[2010][2010];

void work(int x, int y){
	int xx = x + 1;
	while (1){
		while (A[xx][y + 1] != 'X')
			xx++;
		if (A[xx][y + 1] == 'X' && A[xx][y + 2] == 'X' && 
			A[xx + 1][y + 1] == 'X' && A[xx + 1][y + 2] == '.' &&
			A[xx + 1][y] == 'X' && A[xx + 2][y] == 'X'){
				work(xx, y + 1);
				continue;
			}
		break;
	}
	int yy = y + 1;
	while (1){
		while (A[x + 1][yy] != 'X')
			yy++;
		if (A[x + 1][yy] == 'X' && A[x + 1][yy + 1] == 'X' && 
			A[x + 2][yy] == 'X' && A[x + 2][yy + 1] == '.' &&
			A[x][yy + 1] == 'X' && A[x][yy + 2] == 'X'){
				work(x + 1, yy);
				continue;
			}
		break;
	}
	++len;
	ans[len].a[0] = x;
	ans[len].a[1] = y;
	ans[len].a[2] = xx;
	ans[len].a[3] = yy;
	for (int i = x; i <= xx; i++)
		A[i][y] = A[i][yy] = '.';
	for (int i = y; i <= yy; i++)
		A[x][i] = A[xx][i] = '.';
}

int main(){
	freopen("G.in", "r", stdin);
	freopen("G.out", "w", stdout);
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++){
		scanf("%s", A[i]);
		A[i][M] = '.';
	}
	for (int i = 0; i <= M; i++)
		A[N][i] = '.';
	int x = 0, y = 0;
	while (1){ 
		while (x < N){
			while (y < M && A[x][y] == '.')
				y++;
			if (y == M) x++, y = 0;
			else break;
		}
		if (x >= N) break;
		work(x, y);
	}
	printf("%d\n", len);
	for (int i = 1; i <= len; i++){
			for (int j = 0; j < 4; j++){
					if (j) printf(" ");
					printf("%d", ans[i].a[j] + 1);
			}
			printf("\n");
	}
}