#include <bits/stdc++.h>
using namespace std;

const int pp = (1e9) + 7;

int N, M, ans;
int f[200010];
int pow2[200010];
int T[200010], W[200010], A[200010];

int lowbit(int x){
        return x & -x;
}

void Init(int x, int data){
        for (;x <= M + 2; x += lowbit(x))
                f[x] = (f[x] + data) % pp;
}

int calc(int x){
        int res = 0;
        for (;x ; x -= lowbit(x))
                res = (res + f[x]) % pp;
        return res;
}

int main() {
        pow2[0] = 1;
        for (int i = 1; i <= 200002; i++)
                pow2[i] = pow2[i - 1] * 2 % pp;
        while (scanf("%d%d", &N, &M) != EOF){
                for (int i = 1; i <= M; i++)
                        W[i] = M + 2;
                for (int i = 0; i <= M + 2; i++){
                        T[i] = 0;
                        f[i] = 0;
                }
                for (int i = 1; i <= N; i++){
                        int k;
                        scanf("%d", &k);
                        for (int j = 1; j <= k; j++){
                                int x;
                                scanf("%d", &x);
                                W[x] = min(W[x], j);
                        }
                }
                for (int i = 1; i <= M; i++)
                        T[W[i]]++;
                for (int i = 1; i <= M; i++)
                        scanf("%d", &A[i]);
                for (int i = 1; i <= M; i++)
                        Init(i, pow2[T[i]] - 1);
                Init(M + 1, 1);
                ans = calc(M + 1) % pp;
                for (int X = 1; X <= M; X++){
                        int x = A[X];
                        Init(W[x], -pow2[T[W[x]]] + 1);
                        T[W[x]]--;
                        Init(W[x], pow2[T[W[x]]] - 1);
                        ans = (ans + calc(W[x] - 1)) % pp;
                }
                ans = (ans + pp) % pp;
                printf("%d\n", ans);
        }
        
        return 0;
}