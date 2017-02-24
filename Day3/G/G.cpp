#include <bits/stdc++.h>
using namespace std;

int n;
unsigned int ans;
int A[110];

int main() {
        scanf("%d",&n);
        for (int i = 1; i <= n; i++)
                scanf("%d",&A[i]);
        while (A[1]) {
                if (A[1] == 1) {
                        int k = 1;
                        for (; A[k] == k; k++);
                        ans += ((unsigned int)1 << (k - 1)) - 1;
                        A[1] = A[k];
                        for (int i = 2; i <= k; i++)
                                A[i] = i - 1;
                } else {
                        int k = A[1];
                        for (int i = 1; i <= k; i++)
                                A[i] = A[i + 1];
                        A[k + 1] = k;
                        ans++;
                }                
        }
        printf("%u\n",ans);
        return 0;
}