#include <cs50.h>
#include <stdio.h>

int main(void){
    int arr[] = {1, 2, 3};

    int i = sizeof(arr);
    int j = sizeof(arr[0]);
    printf("%i\n", i);
    printf("%i\n", j);
}