#include <bits/stdc++.h>
using namespace std;

struct EDGE { int a, b; };

vector <EDGE> vec[110];

int n,m;
int top;

int main() {
        scanf("%d %d",&n,&m);
        top = 1;
        vec[1].push_back((EDGE) { 1, 2 });        
        for (int i = 3; i <= n; i++) {
                if ((i & 1)) {
                        for (int j = 1; j <= top; j++) {
                                vec[j].push_back((EDGE) { i - j, i });
                        }                        
                } else {
                        for (int j = 1; j <= top; j++)
                                vec[j].push_back((EDGE) { j, i });
                        if (top < m) {
                                top++;
                                for (int j = 1; j < i / 2; j++)
                                        vec[top].push_back((EDGE) { j, i - 1 });
                                for (int j = i / 2; j <= i - 1; j++)
                                        vec[top].push_back((EDGE) { j, i });
                        }
                }
        }
        if (top < m) { printf("-1"); return 0; }
        for (int i = 1; i <= m; i++) {
                for (auto j = vec[i].begin(); j != vec[i].end(); j++)
                        printf("%d %d\n",j -> a, j -> b);
                putchar('\n');
        }
        return 0;
}