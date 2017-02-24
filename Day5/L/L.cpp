#include <bits/stdc++.h>
using namespace std;

#define LL long long

int Test, N;
int A[100010];
LL ans;

int main(){
        scanf("%d", &Test);
        while (Test--){
                scanf("%d", &N);
                for (int i = 1; i <= N; i++)
                        scanf("%d", &A[i]);
                sort(A + 1, A + N + 1);
                ans = 0;
                for (int i = N; i; i--)
                        ans += max(0, A[i] - (N - i));
                cout << ans << endl;
        }
}