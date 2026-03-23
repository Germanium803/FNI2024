#include <stdio.h>
#include <string.h>

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        char s[30];
        scanf("%s", s);
        int n = strlen(s);
        int f0 = 0, f1 = 1;

        for (int i = 0; i < n; i++) {
            int shift;

            if (i == 0) shift = 0;
            else if (i == 1) shift = 1;
            else {
                int f = (f0 + f1);
                f0 = f1;
                f1 = f;
                shift = f % 10;
            }

            printf("%c", s[i] + shift);
        }
        printf("\n");
        f0 = 0;
        f1 = 1;
    }

    return 0;
}
