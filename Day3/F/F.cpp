#include <bits/stdc++.h>
using namespace std;

int ans, res, N, step;
int A[400010], P[400010];
int seg[400010], D[400010], co[400010];

void sset(int x){
        if (A[x] > step) seg[x] = 1;
        else if (A[x] < step) seg[x] = -1;
        else seg[x] = 0;
}

void Mul(int x){
        if ((x << 1) <= N && seg[x << 1] > 0) seg[x] += seg[x << 1];
        if (((x << 1) + 1) <= N && seg[(x << 1) + 1] > 0) seg[x] += seg[(x << 1) + 1];
}

void build(int x){
        if ((x << 1) <= N) build(x << 1);
        if (((x << 1) + 1) <= N) build((x << 1) + 1);
        seg[x] = (A[x] > 1);
        Mul(x);
}

void deal(int x){
        res = seg[x];
        ans = max(ans, res);
        while (x > 1){
                int now = seg[x >> 1];
                if (seg[x] > 0) now -= seg[x];
                x >>= 1;
                res += now;
                ans = max(ans, res);
        }
}

void change(int x){
        sset(x);
        Mul(x);
        while (x > 1){
                x >>= 1;
                sset(x);
                Mul(x);
        }
}

int main(){
        
        while (scanf("%d", &N) != EOF){
                for (int i = 1; i <= N; i++){
                        scanf("%d", &A[i]);
                        P[A[i]] = i;
                }
                build(1);
                for (step = 1; step <= N; step++){
                        if (step > 1){
                                change(P[step - 1]);
                                change(P[step]);
                        }
                        ans = res = 0;
                        deal(P[step]);
                        D[step] = ans;
                }
                for (int i = 0; i < N; i++)
                        co[i] = 0;
                for (int i = 1; i <= N; i++)
                        co[D[i]] = i;
                for (int i = N - 1; i >= 0; i--)
                        co[i] = max(co[i], co[i + 1]);
                for (int i = 0; i < N; i++){
                        if (i > 0) printf(" ");
                        printf("%d", co[i]);
                }
                printf("\n");
        }
        
        return 0;
}