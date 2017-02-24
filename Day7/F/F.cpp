#include <bits/stdc++.h>
#define intl long long
using namespace std;

intl S,A[110],B[110],C[110],m;
int n,p[110];

bool cmp(int a, int b) {
        return (A[a] * m % S > A[b] * m % S || (A[a] * m % S == A[b] * m % S && a < b));
}

bool judge(intl m) {
        sort(p + 1, p + n + 1, cmp);
        for (int i = 1; i <= n; i++) C[i] = A[i] * m / S;
        for (int i = 1; i <= n; i++) m -= C[i];
        for (int i = 1; i <= n && m; i++) {
                C[p[i]]++; m--;
        }
        for (int i = 1; i <= n; i++)
                if (C[i] < B[i]) return false;
        return true;
}

int main() {
        scanf("%d",&n);
        for (int i = 1; i <= n; i++) scanf("%lld %lld",&A[i],&B[i]), S += A[i];
        for (int i = 1; i <= n; i++) {
                double b = B[i] - 1;                
                m = max(m, (intl) (b / (double) A[i] * (double) S));
        }
        for (int i = 1; i <= n; i++) p[i] = i;        
        sort(p + 1, p + n + 1, cmp);
        while (!judge(m)) m++;
        printf("%lld\n",m);
        return 0;
}