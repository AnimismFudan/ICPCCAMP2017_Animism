
#include <bits/stdc++.h>
using namespace std;

#define LL long long

int A, B, len;
LL hh;
int h[5000000];
char s[5000000][50];
map <int , int > H;

int cnt, a[10], b[10], t[10], x[10];

void Print(int d)
{
        for (int i=0; i<=6; i++)
        {
                int j = d&1; d>>=1;
                for (int k=0; k<7; k++)
                {
                        printf("%c", 'a' + x[k] + j * t[k] - 1);
                }
        }
        printf("\n");
}

void pri(){
        for (int i = 1; i <= len; i++)
                if (h[i] == hh){
                        for (int j = 0; j < 7; j++)
                                if (a[j] == 0) a[j] = s[i][j];
                                else b[j] = s[i][j];
                }
        for (int j=0; j<7; j++) t[j] = a[j] - b[j];
        for (int j=0; j<7; j++)
        {
                int k;
                for (k = 1; k<=26; k++)
                        if (k + t[j] >= 1 && k + t[j] <= 26) break;
                x[j] = k;
        }
        /*
        for (int j=0; j<7; j++)
                cout << t[j] << ' ';
        cout << endl;
        */
        for (int i=0; i<100; i++)
                Print(i);
}

int main(){
        
        scanf("%d%d", &A, &B);
        len = 0;
        while (len + 1 < 5000000){
                ++len;
                hh = 0;
                for (int i = 0; i < 7; i++){
                        s[len][i] = rand() % 26 + 1;
                        hh = (hh * A + s[len][i]) % B;
                }
                h[len] = hh;
                H[hh]++;
                if (H[hh] == 2){
                        pri();
                        return 0;
                }
        }
        int ans = 0;
        for (auto X : H)
                ans = max(ans, (X.second));
        printf("%d\n", ans);
        return 0;
}