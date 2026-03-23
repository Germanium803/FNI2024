#include <stdio.h>

int main() {
    int P;
    scanf("%d", &P);

    while(P--) {
        long long N;
        scanf("%lld", &N);

        long long prev, curr;
        int ok = 1;

        if(N > 0)
            scanf("%lld", &prev);

        for(long long i = 1; i < N; i++) {
            scanf("%lld", &curr);

            if(curr < prev)
                ok = 0;

            prev = curr;
        }

        if(ok) printf("SI\n");
        else printf("NO\n");
    }

    return 0;
}
