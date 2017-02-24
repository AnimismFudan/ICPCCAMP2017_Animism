#include <bits/stdc++.h>
using namespace std;

int N, K, D, step, ans;
bool B[110][110];

int main(){
        scanf("%d%d", &N, &K);
        if (K == 1){
                printf("-1\n");
                return 0;
        }
        D = 2;
        for (int i = 1; i <= N; i++){
                B[i][i % N + 1] = 1;
                B[i % N + 1][i] = 1;
        }
        step = 2;
        while (D + 1 < K){
                for (int i = 1; i <= N; i++){
                        B[i][(i + step - 1) % N + 1] = 1;
                        B[(i + step - 1) % N + 1][i] = 1;
                }
                D += 2;
                step++;
        }
        if (D < K){
                bool flag = 0;
                if (N & 1){
                        N--;
                        flag = 1;
                }
                for (int i = 1; i <= N; i++){
                        B[i][(i + N / 2 - 1) % N + 1] = 1;
                        B[(i + N / 2 - 1) % N + 1][i] = 1;
                }
                D++;
                if (flag){
                        N++;
                        for (int i = 1; i <= N; i++)
                                if (!B[N][i]){
                                        B[N][i] = 1;
                                        B[i][N] = 1;
                                        break;
                                }
                }
        }
        ans = 0;
        for (int i = 1; i <= N; i++)
                for (int j = i + 1; j <= N; j++)
                        ans += B[i][j];
        printf("%d\n", ans);
        for (int i = 1; i <= N; i++)
                for (int j = i + 1; j <= N; j++)
                        if (B[i][j])
                                printf("%d %d\n", i, j);
        for (int i = 1; i <= N; i++){
                printf("%d", i);
                if (i < N) printf(" ");
                else printf("\n");
        }
}