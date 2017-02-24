#include <bits/stdc++.h>
#define eps (1e-10)
using namespace std;

double s,t,mid;
double h,a,b,c,x,y,z,ans;
int T; 

int main() {
        for (scanf("%d",&T); T; T--) {
                scanf("%lf %lf %lf %lf %lf %lf %lf",&h,&a,&b,&c,&x,&y,&z);
                double L = 0, R = h;
                while (L + eps < R) {
                        mid = (L + R) / 2.0;
                        double sa = mid / sqrt(mid * mid + a * a);
                        sa = sa / x * y;
                        if (sa > 1.0 - eps) { R = mid; continue; }
                        double sb = sa / sqrt(1.0 - sa * sa);
                        t = b * sb;
                        sa = sa / y * z;
                        if (sa > 1.0 - eps) { R = mid; continue; }
                        double sc = sa / sqrt(1.0 - sa * sa);
                        s = c * sc;
                        if (mid + t + s > h) R = mid;
                        else L = mid;
                }

                ans = sqrt(mid * mid + a * a) / x + sqrt(t * t + b * b) / y + sqrt(s * s + c * c) / z;
                printf("%.12lf\n",ans);
        }
        return 0;
}