#include <bits/stdc++.h>
#define S(a) ((a) * (a))
#define eps (1e-8)
using namespace std;

double X[1010],Y[1010];
int n,T;
double step;
int cnt;
double x, y;

void solve(double step) {
        double A = 0, B = 0, C = 0, D = 0, now = 0;
        double xa = x - step, xb = x + step;
        double yc = y - step, yd = y + step;
        for (int i = 1; i <= n; i++) {
                A += sqrt(S(xa - X[i]) + S(y - Y[i]));
                B += sqrt(S(xb - X[i]) + S(y - Y[i]));
                C += sqrt(S(x - X[i]) + S(yc - Y[i]));
                D += sqrt(S(x - X[i]) + S(yd - Y[i]));                
                now += sqrt(S(x - X[i]) + S(y - Y[i]));
        }
        double ansx = x, ansy = y;
        if (now > A) now = A, ansx = xa, ansy = y;
        if (now > B) now = B, ansx = xb, ansy = y;
        if (now > C) now = C, ansx = x, ansy = yc;
        if (now > D) now = D, ansx = x, ansy = yd;
        x = ansx; y = ansy;
}

int main() {
        for (scanf("%d",&T); T; T--) {
                scanf("%d",&n);
                x = y = 0;
                for (int i = 1; i <= n; i++) scanf("%lf %lf",&X[i],&Y[i]),x += X[i],y += Y[i];
                x /= (double) n; y /= (double) n;
                step = 1000000;
                cnt = 10;
                while (step > eps) {
                        if (!cnt) cnt = 10, step /= 2.0;
                        solve(step);
                        cnt--;
                }
                printf("%.12lf %.12lf\n",x,y);
        }        
        return 0;
}