
#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int fx[4] = {0, 0, 1, -1};
const int fy[4] = {1, -1, 0, 0};

const int maxl = 5000000;

int W, H, Q;
LL ans;

int A[10010][12];

class poi{
	public:
	int x, y;
	LL d;
} p;

bool operator < (const poi &A, const poi &B){
	return A.d < B.d;
}

bool operator > (const poi &A, const poi &B){
	return A.d > B.d;
}

priority_queue <poi, vector<poi>, greater<poi> > Heap;

class querec{
	public:
	int sx, tx, sy, ty, n, t;
	LL ans;
} que[100010];

bool vis[10010][11];

LL dist[10010][11];

bool cmpt(const querec &A, const querec &B){
	return A.t < B.t;
}

bool cmpn(const querec &A, const querec &B){
	return A.n < B.n;
}

void dijkstra(int sx, int sy, int ll, int rr){
	for (int i = ll; i <= rr; i++)
		for (int j = 1; j <= W; j++){
			dist[i][j] = 2e18;
			vis[i][j] = 0;
		}
	dist[sx][sy] = A[sx][sy];
	p.x = sx;
	p.y = sy;
	p.d = A[sx][sy];
	Heap.push(p);
	for (; !Heap.empty(); ){
		p = Heap.top();
		Heap.pop();
		int x = p.x;
		int y = p.y;
		if (vis[x][y]) continue;
		vis[x][y] = 1;
		for (int i = 0; i < 4; i++){
			int xx = x + fx[i];
			int yy = y + fy[i];
			if (xx < ll || xx > rr || yy < 1 || yy > W) continue;
			if (dist[xx][yy] > dist[x][y] + A[xx][yy]){
				dist[xx][yy] = dist[x][y] + A[xx][yy];
				p.x = xx;
				p.y = yy;
				p.d = dist[xx][yy];
				Heap.push(p);
			}
		}
	}
}

void work(int ql, int qr, int hl, int hr){
	if (ql > qr) return;
	if (hl > hr) return;
	int mid = (hl + hr) >> 1;
	for (int j = 1; j <= W; j++){
		dijkstra(mid, j, hl, hr);
		for (int i = ql; i <= qr; i++)
			que[i].ans = min(que[i].ans, dist[que[i].sx][que[i].sy] + dist[que[i].tx][que[i].ty] - A[mid][j]);
	}
	if (hl >= hr) return;
	for (int i = ql; i <= qr; i++)
		if (que[i].sx <= mid && que[i].tx <= mid)
			que[i].t = 0;
		else if (que[i].sx > mid && que[i].tx > mid)
			que[i].t = 1;
		else que[i].t = 2;
	sort(que + ql, que + qr + 1, cmpt);
	int ll = ql, rr = ql - 1;
	while (rr < qr && que[rr + 1].t == 0) rr++;
	work(ll, rr, hl, mid);
	ll = rr + 1;
	while (rr < qr && que[rr + 1].t == 1) rr++;
	work(ll, rr, mid + 1, hr);
}

int main(){
	freopen("I.in", "r", stdin);
	freopen("I.out", "w", stdout);
	scanf("%d%d%d", &W, &H, &Q);
	for (int i = 1; i <= H; i++)
		for (int j = 1; j <= W; j++)
			scanf("%d", &A[i][j]);
	for (int i = 1; i <= Q; i++){
		scanf("%d%d%d%d", &que[i].sy, &que[i].sx, &que[i].ty, &que[i].tx);
		que[i].n = i;
		que[i].ans = 2e18;
	}
	work(1, Q, 1, H);
	sort(que + 1, que + Q + 1, cmpn);
	for (int i = 1; i <= Q; i++)
		printf("%I64d\n", que[i].ans);
	return 0;
}