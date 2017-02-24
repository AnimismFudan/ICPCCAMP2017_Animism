#include bitsstdc++.h
#define intl long long
#define maxn 1010000
#define INF (1LL  60)
using namespace std;

intl f[maxn][2][2];
int n,m;
intl A[maxn];
intl B[maxn];
intl ans;

int main() {
        while (scanf(%d,&n) != EOF) {
                for (int i = 0; i  n; i++) scanf(%lld,&A[i]);
                for (int i = 0; i  n; i++) scanf(%lld,&B[i]);
                f[0][0][0] = B[0];
                f[0][1][1] = A[0];
                f[0][0][1] = INF;
                f[0][1][0] = INF;
                for (int i = 1; i  n; i++) {
                        for (int a = 0; a  2; a++)
                                for (int b = 0; b  2; b++)
                                        f[i][a][b] = INF;
                        for (int a = 0; a  2; a++)
                                for (int b = 0; b  2; b++)
                                        for (int c = 0; c  2; c++) {
                                                f[i][a][c] = min(f[i][a][c], f[i - 1][a][b] + B[i]  (intl)(!(b && c)) + A[i]  (intl) c);
                                        }
                }
                ans = INF;
                ans = min(ans, min(f[n - 1][0][0], f[n - 1][0][1]));
                ans = min(ans, min(f[n - 1][1][1], f[n - 1][1][0] + B[0]));
                printf(%lldn,ans);
        }
        return 0;
}