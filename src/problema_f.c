#include <stdio.h>

int main(){
    int T;
    scanf("%d",&T);

    while(T--){
        int N;
        scanf("%d",&N);

        long long e[35];
        long long total=0;

        for(int i=0;i<N;i++){
            scanf("%lld",&e[i]);
            total+=e[i];
        }

        long long mid1=(total+1)/2;
        long long mid2=(total%2==0)?mid1+1:mid1;

        long long sum=0;

        for(int i=0;i<N;i++){
            if(mid1>sum && mid1<=sum+e[i])
                printf("T: %d E: %lld\n",i+1,mid1-sum);

            if(mid2!=mid1 && mid2>sum && mid2<=sum+e[i])
                printf("T: %d E: %lld\n",i+1,mid2-sum);

            sum+=e[i];
        }
    }

    return 0;
}
