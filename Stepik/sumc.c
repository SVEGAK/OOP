#include <stdio.h>
#include <stdlib.h>
int sumc(int num, int sum){
    if (num == 0){
        return sum;
    }
    sum = sum + num%10;
    num = num/10; // 123 -> 12
    return sumc(num,sum);
}
int main(){
    int num,sum = 0;
    scanf("%d",&num);
    printf("%d",sumc(num,sum));
    return 0;
}