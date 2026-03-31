// #include <stdio.h>
// #include <stdlib.h>
// int main()
// {
//     float arr[] = { 12.5, 3.7, 25.1, 8.9, 25.1, 10.2, 5.4};
//     float maxel = 0,t= 0;
//     for (int i = 0; i < 8
//         ; i++){
//         t = arr[i];
//         // printf("%f",t);
//         if (t > maxel){
//             maxel = t;
//         }
//     }
//     printf("%f",maxel);
//     return 0;
// }
// int check_type(char c,char *nums){
//     for (int j = 0; j < 10;j++){
//         if (c == nums[j]){
//             return 0;
//         }
//     }
//     return 1;
// }
// int main()
// {   char nums[] = "1234567890";
//     char s[] = "Hello123 World456! This is test789.";
//     char s2[100];
//     int ind = 0;
//     for (int i = 0; i < sizeof(s)-1; i++){
//         if(check_type(s[i],nums)){
//             s2[ind] = s[i];
//             ind ++;
//         }
//     }
//     printf("%s",s2);
//     return 0;
// }
// int main(int argc, char const *argv[])
// {
//     int arr1[] = {1, 5, 3, 4, 2, 6, 1};
//     int maxel = -1, minel = 10000, t = 0;
//     for (int i = 0; i < sizeof(arr1)/sizeof(int);i++){
//         t = arr1[i];
//         if (t > maxel){
//             maxel = t;
//         }
//         if (t < minel){
//             minel = t;
//         }
//     }
//     printf("%d %d", maxel,minel);
//     return 0;
// }

int main(int argc, char const *argv[])
{
    int arr2[] = {5, 5, 3, 3, 3, 7, 2, 2, 2, 2, 8, 8, 4, 4, 4, 4, 4, 9, 1, 1};
    int t_count = 1, min_c = 1000;
    printf("%d\n", sizeof(arr2)/sizeof(int));
    for (int i =0; i < sizeof(arr2)/sizeof(int)-1;i++){
        if (arr2[i] == arr2[i+1]){
            t_count +=1;
        }
        else{
            if (t_count <  min_c){
                min_c = t_count;
                
            }
             t_count = 1;
        }  
    }
    printf("%d",min_c);
    return 0;
}
