#include <bits/stdc++.h>
#define intl long long
using namespace std;

intl ans;
intl mark[101000], A[101000];
int n;

void solve(intl a, intl b, intl c, intl d, intl e, intl f) {
        bool flag = false;
        if (a + b > d && c + e > f) flag = true;
        if (a + b > e && c + d > f) flag = true;
        if (a + b > f && c + d > e) flag = true;
        if (a + c > d && b + e > f) flag = true;
        if (a + c > e && b + d > f) flag = true;
        if (a + c > f && b + d > e) flag = true;
        if (a + d > e && b + c > f) flag = true;
        if (a + d > f && b + c > e) flag = true;
        if (a + e > f && b + c > d) flag = true;
        if (flag) ans = max(ans, a + b + c + d + e + f);
}

int main() {
        scanf("%d",&n);
        for (int i = 1; i <= n; i++) scanf("%lld",&A[i]);
        sort(A + 1, A + n + 1);
        ans = 0;
        mark[1] = mark[2] = mark[0] = -1;
        for (int i = 3; i <= n; i++) {
                if (A[i - 1] + A[i - 2] > A[i]) {
                        if (mark[i - 3] != -1) ans = max(ans, mark[i - 3] + A[i] + A[i - 2] + A[i - 1]);
                        mark[i] = A[i - 1] + A[i - 2] + A[i];
                }
                else mark[i] = mark[i - 1];
        }
        for (int i = 6; i <= n; i++)
                solve(A[i - 5], A[i - 4], A[i - 3], A[i - 2], A[i - 1], A[i]);
        printf("%lld\n",ans); 
        return 0;
}