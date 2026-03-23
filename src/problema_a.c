#include <stdio.h>

long long gcd(long long a, long long b){
    while(b != 0){
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main(){
    int T;
    scanf("%d", &T);

    while(T--){
        long long A, B, C;
        scanf("%lld %lld %lld", &A, &B, &C);

        long long S = A + B + C;

        long long min = A;
        if(B < min) min = B;
        if(C < min) min = C;

        long long total = S - min;

        long long precios[3] = {A, B, C};

        for(int i = 0; i < 3; i++){
            long long num = total * precios[i];
            long long den = S;

            long long g = gcd(num, den);
            num /= g;
            den /= g;

            printf("%lld/%lld", num, den);
            if(i < 2) printf(" ");
        }

        printf("\n");
    }

    return 0;
}
