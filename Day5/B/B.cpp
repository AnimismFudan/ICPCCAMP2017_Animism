#include <bits/stdc++.h>
using namespace std;

#define LL long long

int Test, N, M, ans;
int Nex[1000010][26];
char A[1000010], B[1010];
int f[1010][1010];

int main(){
        scanf("%d", &Test);
        while (Test--){
                scanf("%s%s", A + 1, B + 1);
                N = strlen(A + 1);
                M = strlen(B + 1);
                for (int i = 0; i < 26; i++)
                        Nex[N + 1][i] = N + 1;
                for (int i = N; i; i--){
                        for (int j = 0; j < 26; j++)
                                Nex[i][j] = Nex[i + 1][j];
                        Nex[i][A[i] - 'a'] = i;
                }
                for (int i = 0; i <= M; i++)
                        for (int j = 0; j <= M; j++)
                                f[i][j] = N + 1;
                f[0][0] = 0;
                ans = 0;
                for (int i = 0; i <= M; i++)
                        for (int j = 0; j <= i; j++)
                                if (f[i][j] <= N){
                                        ans = max(ans, j);
                                        f[i + 1][j] = min(f[i + 1][j], f[i][j]);
                                        int t = Nex[f[i][j] + 1][B[i + 1] - 'a'];
                                        if (t <= N)
                                                f[i + 1][j + 1] = min(f[i + 1][j + 1], t);
                                }
                printf("%d\n", ans);
        }
}