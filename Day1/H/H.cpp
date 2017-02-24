#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mod = (int)1e9 + 7;


struct nodetype
{
        ll A[3][3];
        void Set()
        {
                A[0][0] = 2; A[0][1] = 0; A[0][2] = 1;
                A[1][0] = 1; A[1][1] = 0; A[1][2] = 0;
                A[2][0] = 0; A[2][1] = 1; A[2][2] = 0;
        }
        void SetOne()
        {
                A[0][0] = 1; A[0][1] = 0; A[0][2] = 0;
                A[1][0] = 0; A[1][1] = 1; A[1][2] = 0;
                A[2][0] = 0; A[2][1] = 0; A[2][2] = 1;
        }
        void Print()
        {
                for (int i=0; i<3; i++)
                {
                        for (int j=0; j<3; j++)
                                printf("%lld ", A[i][j]);
                        printf("\n");
                }
        }
};

int N;
nodetype temp, res;

nodetype Mult(nodetype A, nodetype B)
{
        nodetype C;
        memset(C.A, 0, sizeof(C.A));
        for (int i=0; i<3; i++)
                for (int j=0; j<3; j++)
                        for (int k=0; k<3; k++)
                                C.A[i][j] = ( C.A[i][j] + A.A[i][k] * B.A[k][j] % mod ) % mod;
        return C;
}

nodetype QuickPow(nodetype A, int t)
{
        nodetype S; S.SetOne();
        while(t)
        {
                if (t&1) S = Mult(S,A);
                A = Mult(A,A); t>>=1;
        }
        return S;
}

void Solve()
{
        temp.Set();
        if (N==1)
        {
                printf("1\n");
                return;
        }
        if (N==2)
        {
                printf("2\n");
                return;
        }
        if (N==3)
        {
                printf("6\n");
                return;
        }
        res = QuickPow(temp, N-4);
        //res.Print();
        int ans = (res.A[0][0]*17 + res.A[0][1]*7 + res.A[0][2]*3) % mod;
        ans = (ans + mod - 1) % mod;
        printf("%d\n",ans);
}

int main()
{
        while(scanf("%d", &N)!=EOF)
                Solve(); 
        return 0;
}