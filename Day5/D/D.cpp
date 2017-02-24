
#include <bits/stdc++.h>
#define INF (1 << 30)
using namespace std;

// 0 -> now black; 1 -> now white;
// black king -> white king -> white root;

struct str { int x1, y1, x2, y2, x3, y3; };

vector <str> A, B;

int f[2][8][8][8][8][8][8];
char s[10][10];
int T;

bool judge(int x1, int y1, int x2, int y2, int x3, int y3) {
        if (x1 == x2 && y1 == y2) { f[1][x1][y1][x2][y2][x3][y3] = f[0][x1][y1][x2][y2][x3][y3] = INF; return false; }
        if (x2 == x3 && y2 == y3) { f[1][x1][y1][x2][y2][x3][y3] = f[0][x1][y1][x2][y2][x3][y3] = INF; return false; }
        if (x1 == x3 && y1 == y3) {
                if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) return true;
                return false;
        }
        if (x1 == x3 && y1 == y3) { f[1][x1][y1][x2][y2][x3][y3] = f[0][x1][y1][x2][y2][x3][y3] = INF; return false; }
        if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) return true;
        if (x1 == x3) {
                if (x1 == x2 && (y1 - y2) * (y2 - y3) >= 0) return false;
                return true;
        }
        else if (y1 == y3) {
                if (y1 == y2 && (x1 - x2) * (x2 - x3) >= 0) return false;
                return true;
        }
        //if (x1 == x3 || y1 == y3) return true;
        return false;
}

void updateblack(int x1, int y1, int x2, int y2, int x3, int y3) {
        if (x1 < 0 || x1 >= 8 || y1 < 0 || y1 >= 8) return;
        if (x1 == x2 && y1 == y2) return;
        if (x1 == x3 && y1 == y3) return;
        if (x2 == x3 && y2 == y3) return;
        int m = 0;
        if (x1 < 7)
                m = max(m, f[1][x1 + 1][y1][x2][y2][x3][y3]);
        
        if (x1 > 0)
                m = max(m, f[1][x1 - 1][y1][x2][y2][x3][y3]);

        if (y1 < 7)
                m = max(m, f[1][x1][y1 + 1][x2][y2][x3][y3]);

        if (y1 > 0)
                m = max(m, f[1][x1][y1 - 1][x2][y2][x3][y3]);

        if (x1 < 7 && y1 < 7)
                m = max(m, f[1][x1 + 1][y1 + 1][x2][y2][x3][y3]);

        if (x1 < 7 && y1 > 0)
                m = max(m, f[1][x1 + 1][y1 - 1][x2][y2][x3][y3]);

        if (x1 > 0 && y1 > 0)
                m = max(m, f[1][x1 - 1][y1 - 1][x2][y2][x3][y3]);

        if (x1 > 0 && y1 < 7)
                m = max(m, f[1][x1 - 1][y1 + 1][x2][y2][x3][y3]);

        if (m == 0) {
                if (!judge(x1,y1,x2,y2,x3,y3)) return;
        }

        if (m <= 50) {
                f[0][x1][y1][x2][y2][x3][y3] = m;
                B.push_back((str) { x1, y1, x2, y2, x3, y3 });
        }
        return;
}

void updatewhite(int x1, int y1, int x2, int y2, int x3, int y3, int val) {
        if (x2 < 0 || x2 >= 8) return;
        if (x3 < 0 || x3 >= 8) return;
        if (y2 < 0 || y2 >= 8) return;
        if (y3 < 0 || y3 >= 8) return;
        if (x1 == x2 && y1 == y2) return;
        if (x1 == x3 && y1 == y3) return;
        if (x2 == x3 && y2 == y3) return;
        if (f[1][x1][y1][x2][y2][x3][y3] <= val + 1) return;
        f[1][x1][y1][x2][y2][x3][y3] = val + 1;
        A.push_back((str) { x1, y1, x2, y2, x3, y3 });
}

void prepare() {
        memset(f,1,sizeof(f));
        for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                        for (int a = 0; a < 8; a++)
                                for (int b = 0; b < 8; b++)
                                        for (int x = 0; x < 8; x++)
                                                for (int y = 0; y < 8; y++)        {
                                                        if (judge(i, j, a, b, x, y)) {
                                                                f[1][i][j][a][b][x][y] = 0;
                                                                A.push_back((str) { i, j, a, b, x, y });
                                                        }
                                                }

        for (int step = 0; step <= 50; step++) {
                for (auto i = A.begin(); i != A.end(); i++) {
                        updateblack(i -> x1 + 1, i -> y1, i -> x2, i -> y2, i -> x3, i -> y3);
                        updateblack(i -> x1 - 1, i -> y1, i -> x2, i -> y2, i -> x3, i -> y3);
                        updateblack(i -> x1, i -> y1 + 1, i -> x2, i -> y2, i -> x3, i -> y3);
                        updateblack(i -> x1, i -> y1 - 1, i -> x2, i -> y2, i -> x3, i -> y3);                        
                        updateblack(i -> x1 - 1, i -> y1 - 1, i -> x2, i -> y2, i -> x3, i -> y3);                        
                        updateblack(i -> x1 + 1, i -> y1 - 1, i -> x2, i -> y2, i -> x3, i -> y3);                        
                        updateblack(i -> x1 - 1, i -> y1 + 1, i -> x2, i -> y2, i -> x3, i -> y3);                        
                        updateblack(i -> x1 + 1, i -> y1 + 1, i -> x2, i -> y2, i -> x3, i -> y3);                                                
                }

                A.clear();
                for (auto i = B.begin(); i != B.end(); i++) {
                        int x1 = i -> x1, y1 = i -> y1, x2 = i -> x2, y2 = i -> y2, x3 = i -> x3, y3 = i -> y3;
                        int val = f[0][i -> x1][i -> y1][i -> x2][i -> y2][i -> x3][i -> y3];
                        updatewhite(x1, y1, x2 + 1, y2, x3, y3, val);
                        updatewhite(x1, y1, x2 - 1, y2, x3, y3, val);        
                        updatewhite(x1, y1, x2, y2 + 1, x3, y3, val);        
                        updatewhite(x1, y1, x2, y2 - 1, x3, y3, val);
                        updatewhite(x1, y1, x2 + 1, y2 + 1, x3, y3, val);
                        updatewhite(x1, y1, x2 + 1, y2 - 1, x3, y3, val);
                        updatewhite(x1, y1, x2 - 1, y2 + 1, x3, y3, val);
                        updatewhite(x1, y1, x2 - 1, y2 - 1, x3, y3, val);
                        for (int x = 1; x + x3 < 8; x++) {
                                if (x + x3 == x1 && y3 == y1) break;
                                if (x + x3 == x2 && y3 == y2) break;
                                updatewhite(x1, y1, x2, y2, x + x3, y3, val);
                        }

                        for (int x = -1; x + x3 >= 0; x--) {
                                if (x + x3 == x1 && y3 == y1) break;
                                if (x + x3 == x2 && y3 == y2) break;
                                updatewhite(x1, y1, x2, y2, x + x3, y3, val);
                        }

                        for (int y = 1; y + y3 < 8; y++) {
                                if (x3 == x1 && y + y3 == y1) break;
                                if (x3 == x2 && y + y3 == y2) break;
                                updatewhite(x1, y1, x2, y2, x3, y3 + y, val);
                        }
                        
                        for (int y = -1; y + y3 >= 0; y--) {
                                if (x3 == x1 && y + y3 == y1) break;
                                if (x3 == x2 && y + y3 == y2) break;
                                updatewhite(x1, y1, x2, y2, x3, y3 + y, val);
                        }
                }

                B.clear();
        }
}

int main() {
        prepare();
        /*for (int x1 = 0; x1 < 8; x1++)
                for (int y1 = 0; y1 < 8; y1++)
                        for (int x2 = 0; x2 < 8; x2++)
                                for (int y2 = 0; y2 < 8; y2++)
                                        for (int x3 = 0; x3 < 8; x3++)
                                                for (int y3 = 0; y3 < 8; y3++)
                                                printf("%d\n",f[1][x1][y1][x2][y2][x3][y3]);
        
        return 0;
        */
        for (scanf("%d",&T); T; T--) {
                for (int i = 0; i < 8; i++)
                        scanf("%s",s[i]);
                int x1, y1, x2, y2, x3, y3;
                for (int i = 0; i < 8; i++)
                        for (int j = 0; j < 8; j++) {
                                if (s[i][j] == 'B') x1 = i, y1 = j;
                                if (s[i][j] == 'W') x2 = i, y2 = j;
                                if (s[i][j] == 'R') x3 = i, y3 = j;
                        }
                //printf("%d\n",f[0][x1][y1][x2][y2][x3][y3] <= 3 ? f[0][x1][y1][x2][y2][x3][y3] : -1);
                printf("%d\n",f[1][x1][y1][x2][y2][x3][y3]);
        }
        return 0;
}