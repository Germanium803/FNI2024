#include <stdio.h>
#include <stdlib.h>

int main() {
    int T;
    scanf("%d", &T);

    while(T--) {
        int N, K;
        scanf("%d %d", &N, &K);

        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {

                int val = (abs(i - j) + 1) * K;

                printf("%d", val);

                if(j < N) printf(" ");
            }
            printf(".\n");
        }
    }

    return 0;
}
