#include <bits/stdc++.h>
using namespace std;

#define LL long long

int Test, N;

int main(){
        scanf("%d", &Test);
        while (Test--){
                scanf("%d", &N);
                if (N > 4){
                        printf("impossible\n");
                        continue;
                }
                if (N == 1){
                        printf("1 1 1 2\n");
                        continue;
                }
                if (N == 2){
                        printf("1 1 1 2\n");
                        printf("1 3 1 4\n");
                        printf("1 5 1 6\n");
                        continue;
                }
                if (N == 3){
                        printf("1 1 2 1\n");
                        printf("1 2 1 3\n");
                        printf("3 1 3 2\n");
                        printf("2 2 2 3\n");
                        printf("1 4 2 4\n");
                        printf("3 3 3 4\n");
                        continue;
                }
                if (N == 4){
                        printf("3 2 4 2\n");
                        printf("3 3 3 4\n");
                        printf("4 3 5 3\n");
                        printf("2 2 2 1\n");
                        printf("2 3 2 4\n");
                        printf("4 4 5 4\n");
                        printf("1 4 1 3\n");
                        printf("5 1 5 2\n");
                        printf("4 1 3 1\n");
                        printf("1 1 1 2\n");
                        continue;
                }
        }
}