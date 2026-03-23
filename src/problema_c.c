#include <stdio.h>

int main() {
    int T;
    scanf("%d",&T);

    while(T--){
        int N;
        scanf("%d",&N);

        int k = 1;

        while(N > k){
            N -= k;
            k++;
        }

        printf("%d\n", N);
    }

    return 0;
}
