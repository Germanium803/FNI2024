#include <stdio.h>

long long C(int n,int k){
    if(k>n) return 0;
    long long r=1;
    for(int i=1;i<=k;i++)
        r=r*(n-i+1)/i;
    return r;
}

int main(){
    int T;
    scanf("%d",&T);

    while(T--){
        long long N;
        scanf("%lld",&N);

        if(N>6) printf("0\n");
        else printf("%lld\n", C(5,N-1));
    }

    return 0;
}
