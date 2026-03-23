#include <stdio.h>

int leap(int y){
    return (y%4==0 && y%100!=0) || (y%400==0);
}

int days_month(int m,int y){
    int d[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(m==2 && leap(y)) return 29;
    return d[m-1];
}

int main(){

    char *week[]={
        "Domingo","Lunes","Martes","Miércoles",
        "Jueves","Viernes","Sábado"
    };

    int T;
    scanf("%d",&T);

    while(T--){

        int D,M,A;
        scanf("%d %d %d",&D,&M,&A);

        if(M<1 || M>12 || D<1 || D>days_month(M,A)){
            printf("-1\n");
            continue;
        }

        long long days=0;

        for(int y=2000;y<A;y++)
            days+=365+leap(y);

        for(int m=1;m<M;m++)
            days+=days_month(m,A);

        days+=D-1;

        int day=(days+6)%7;

        printf("%s\n",week[day]);
    }

    return 0;
}
