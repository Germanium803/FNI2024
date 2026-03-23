#include <stdio.h>
#include <stdlib.h>

void sort3(long long *a, long long *b, long long *c){
    long long t;
    
    if(*a > *b){ t=*a; *a=*b; *b=t; }
    if(*b > *c){ t=*b; *b=*c; *c=t; }
    if(*a > *b){ t=*a; *a=*b; *b=t; }
}

int main(){
    int T;
    scanf("%d",&T);

    while(T--){
        long long a,b,c;
        scanf("%lld %lld %lld",&a,&b,&c);

        sort3(&a,&b,&c);

        long long med = b;

        long long dist = llabs(a-med) + llabs(b-med) + llabs(c-med);

        printf("%lld\n",dist);
    }

    return 0;
}
