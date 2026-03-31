#include <stdio.h>
#include <stdlib.h>
void mass_output(int *mass,int len,int count){
    if (count == 1){
        printf("{ ");
    }
    if (count == len){
        printf("%d ",mass[count-1]);
        printf("}");
        return;
    }
    printf("%d, ",mass[count-1]);
    return mass_output(mass,len,count+1);

}


int main(){
    int len = 0,count = 1;
    int* numbers;
    printf("Длинна массива: ");
    scanf_s("%d",&len);
    numbers = (int*)malloc(sizeof(int)*len);
    printf_s("Введите массив: \n");
    for (int i = 0;i < len;i++){
        scanf_s("%d",&numbers[i]);
    }
    mass_output(numbers, len, count);

    return 0;
}
