#include <bits/stdc++.h>
#define maxn 1010000
#define intl unsigned long long
using namespace std;

intl has[maxn];
int du[maxn],fa[maxn],size[maxn];
map<intl,int> st;
int cnt,n,ans;
int L,R;
int que[maxn];

void add(intl a) {
        if (!st[a]) cnt++;
        st[a]++;
}

void del(intl a) {
        st[a]--;
        if (!st[a]) cnt--;
}

int main() {
        while (scanf("%d",&n) != EOF) {
                st.clear();
                for (int i = 1; i <= n; i++)
                        fa[i] = has[i] = du[i] = size[i] = 0;
                for (int i = 2; i <= n; i++) {
                        scanf("%d",&fa[i]); du[fa[i]]++;
                }

                cnt = 0;
                ans = 0;
                L = 0; R = 0;
                
                for (int i = 1; i <= n; i++) {
                        has[i] = 1;
                        size[i] = 1;
                        if (!du[i]) { que[++R] = i;  }
                        add(has[i]);
                }
                
                while (L < R) {
                        int u = que[++L];                
                        if (cnt == 1) ans++;
                        if (u == 1) continue;
                        
                        size[fa[u]] += size[u];
                        del(has[u]);
                        if (fa[u]){
                                del(has[fa[u]]);
                                   has[fa[u]] += has[u] * has[u];
                                add(has[fa[u]]);
                                if (!(--du[fa[u]])) {
                                        que[++R] = fa[u];
                                }
                        }
                }
                printf("%d\n",ans - 1);
        }
        return 0;
}