#include <bits/stdc++.h>
#define intl long long
#define maxn 1001000
using namespace std;

intl A[maxn],B[maxn],C[maxn];
int n,m;
intl ans,cnt;

int main() {
        while (scanf("%d",&n) != EOF) {
                for (int i = 0; i < n; i++) scanf("%lld",&A[i]);
                for (int i = 0; i < n; i++) scanf("%lld",&B[i]);
                for (int i = 0; i <= 2 * n; i++) scanf("%lld",&C[i]);
                C[2 * n + 1] = 0LL;
                ans = 1LL << 60;
                cnt = 1LL << 60;
                for (int i = 0; i < n; i++) {
                        cnt += C[i * 2] + C[i * 2 + 1];
                        cnt = min(cnt, C[i * 2 + 1] + B[i]);
                        ans = min(ans, cnt + A[i]);
                }
                cnt = 1LL << 60;
                for (int i = 1; i < n; i++) {
                        cnt += C[i * 2] + C[(i - 1) * 2 + 1];
                        cnt = min(cnt, A[i - 1] + C[i * 2]);
                        ans = min(ans, B[i] + cnt);
                }
                cnt = 0;
                for (int i = 0; i < n; i++) {
                        cnt += C[i * 2] + C[i * 2 + 1];
                        ans = min(ans, A[i] + cnt);
                }
                cnt = 0;
                for (int i = n - 1; i >= 0; i--) {
                        cnt += C[i * 2 + 1] + C[(i + 1) * 2];
                        ans = min(ans, B[i] + cnt);
                }
                cnt = 0;
                for (int i = 0; i <= 2 * n; i++) cnt += C[i];
                ans = min(ans, cnt);
                printf("%lld\n",ans);
        }
        return 0;
}