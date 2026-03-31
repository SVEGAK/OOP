#include <stdio.h>

int main() {
    int N;
    float S;
    float f=0,d=0;
    scanf("%d",&N);
    for (int i = 0; i < N; i ++ ){
        f = (1.0/(i+1));
        d = (1.0/(N-i));
        printf("1/%d*1/%d",i+1,N-i);
        S += (f*d);
        if (i < N-1){
            printf("+");}
    }
    printf("=%.2f",S);
    return 0;
}