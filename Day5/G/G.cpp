#include <bits/stdc++.h>
using namespace std;

#define LL long long

const LL P = 998244353;
const LL G = 3;

int N, M;
LL W[2][400010], js[400010];
LL A[400010], B[400010], C[400010], p[400010], ans[400010];
int rev[400010];
int t, n, m, T;

LL Pow (LL a, LL b){
        LL c = 1; 
        for (; b; b >>= 1, a = a * a % P)
                if (b & 1) c = c * a % P;
        return c;
}

void FFT(LL *a, int f) {
        for (int i = 0; i < M; i++)
                if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int i = 1; i < M; i <<= 1)
                for (int j = 0, t = M / (i << 1); j < M; j += i << 1)
                        for (int k = 0, l = 0; k < i; k++, l += t) {
                                LL x, y;
                                x = W[f][l] * a[j + k + i] % P;
                                y = a[j + k];
                                a[j + k] = (y + x) % P;
                                a[j + k + i] = (y - x + P) % P;
                        }
        if (f)
                for (int i = 0, x = Pow(M, P - 2); i < M; i++)
                        a[i] = a[i] * x % P;
}

void work() {
        for (int i = 0; i < M; i++) {
                int x = i, y = 0;
                for (int k = 1; k < M; x >>= 1, k <<= 1) (y <<= 1) |= x & 1;
                rev[i] = y;
        }
        W[0][0] = W[1][0] = 1;
        LL x = Pow(G, (P - 1) / M), y = Pow(x, P - 2);
        for (int i = 1; i < M; i++){
                W[0][i] = x * W[0][i - 1] % P;
                W[1][i] = y * W[1][i - 1] % P;
        }
}

void DoDoDo(){
        N = n;
        for (M = 1; M <= N; M <<= 1);
        M <<= 1;
        work();
        FFT(A, 0);
        FFT(B, 0);
        for (int i = 0; i < M; i++) C[i] = A[i] * B[i] % P;
        FFT(C, 1);
        for (int i = 0; i < M; i++) C[i] = (C[i] + P) % P;
}

void fpm(int t) {
        for (int i = 0; i <= M; i++) A[i] = B[i] = C[i] = ans[i] = js[i] = 0;
        A[1] = 2; A[0] = m - 1;
        ans[0] = 1;
        for (; t; t >>= 1) {
                if (t & 1) {
                        for (int i = 0; i <= M; i++) js[i] = A[i], B[i] = ans[i];                                
                        //memcpy(js,A,sizeof(js));
                        //memcpy(B,ans,sizeof(ans));
                        DoDoDo();
                        for (int i = 0; i <= M; i++) ans[i] = C[i], A[i] = js[i];
                        //memcpy(ans,C,sizeof(ans));
                        //memcpy(A,js,sizeof(js));
                        for (int i = 0; i < n; i++) {
                                ans[i] = (ans[i] + ans[i + n]) % m;
                                ans[i + n] = 0;
                        }
                        for (int i = n + n; i <= M; i++) ans[i] = 0;
                }
                for (int i = 0; i <= M; i++) B[i] = A[i];
                //memcpy(B,A,sizeof(A));                
                DoDoDo();
                for (int i = 0; i <= M; i++) A[i] = C[i];
                //memcpy(A,C,sizeof(A));
                for (int i = 0; i < n; i++) {
                        A[i] = (A[i] + A[i + n]) % m;
                        A[i + n] = 0;
                }
                for (int i = n + n; i <= M; i++) A[i] = 0;
        }
}

void Main() {
        for (scanf("%d",&T); T; T--) {
                DoDoDo();
                scanf("%d %d %d",&n,&m,&t);
                //memset(W,0,sizeof(W));
                for (int i = 0; i < n; i++) scanf("%lld",&p[i]), p[i + n] = 0;
                fpm(t);
                reverse(p,p + n);                
                for (int i = 0; i <= M; i++) A[i] = ans[i], B[i] = p[i];
                //memcpy(A,ans,sizeof(ans));                
                //memcpy(B,p,sizeof(p));
                DoDoDo();
                for (int i = n - 1; i >= 0; i--) {
                        LL k = (C[i] + C[i + n]) % m;
                        printf("%lld ",k ? k : m);
                }
                putchar('\n');
        }
}

int main(){
        Main();
        return 0;
}