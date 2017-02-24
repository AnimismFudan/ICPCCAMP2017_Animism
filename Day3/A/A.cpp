#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N;
LL M, K, ss;
LL A[200010], B[200010], C[200010];
unordered_set <LL> Hash;

LL exgcd(LL a,LL b,LL &x,LL &y){
	if (b==0){x=1;y=0;return a;}
	LL r=exgcd(b,a%b,x,y);
	LL t=x;
	x=y;
	y=t-a/b*y;
	return r;
}

bool check2(){
	for (int i = 1; i <= N; i++){
		C[i] = (A[i] + K) % M;
		if (Hash.find(C[i]) == Hash.end())
			return 0;
	}
	sort(C + 1, C + N + 1);
	for (int i = 1; i <= N; i++)
		if (B[i] != C[i]) return 0;
	return 1;
}

bool check(){
	LL GCD, Delta, T;
	GCD = exgcd(N, M, K, T);
	Delta = M / GCD;
	K = (K % Delta) * ((ss / GCD) % Delta) % Delta;
	if (K < 0) K += Delta;
	while (K < M){
		if (check2()) return 1;
		K += Delta;
	}
	return 0;
}

int main(){
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
	while (scanf("%d", &N) != EOF){
		Hash.clear();
		for (int i = 1; i <= N; i++)
			scanf("%lld", &A[i]);
		M = 0;
		for (int i = 1; i <= N; i++){
			scanf("%lld", &B[i]);
			Hash.insert(B[i]);
			M = max(M, B[i]);
		}
		sort(B + 1, B + N + 1);
		ss = 0;
		for (int i = 1; i <= N; i++){
			ss -= A[i];
			ss += B[i];
		}
		for (; !check(); )
			M++;
		printf("%lld %lld\n", M, K);
	}
}