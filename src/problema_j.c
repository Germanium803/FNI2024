#include <stdio.h>

int main(){
    int t;
    scanf("%d",&t);

    while(t--){
        int n,k;
        scanf("%d %d",&n,&k);

        int a[60];

        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);

        int bag=0;
        int helped=0;

        for(int i=0;i<n;i++){

            if(a[i] >= k){
                bag += a[i];
            }
            else if(a[i] == 0 && bag > 0){
                bag--;
                helped++;
            }
        }

        printf("%d\n",helped);
    }

    return 0;
}
