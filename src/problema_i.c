#include <stdio.h>
#include <stdlib.h>

int main(){
    int t;
    scanf("%d",&t);

    while(t--){
        int n;
        scanf("%d",&n);

        int a[55];

        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);

        int ok=1;

        for(int i=1;i<n;i++){
            int diff = abs(a[i]-a[i-1]);

            if(diff!=5 && diff!=7){
                ok=0;
                break;
            }
        }

        if(ok) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}
