#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int count_of_numbers(int num,int count_numb){
    if (num == 0){
        return count_numb;
    }
    num = num/10; // 123 -> 12
    
    return count_of_numbers(num,count_numb+1);
}
int main(){
    int num = 0;
    scanf_s("%d",&num);
    // printf_s("%d",num/10);
    printf("%d", count_of_numbers(num,0));
    return 0;
}




