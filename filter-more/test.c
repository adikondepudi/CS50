#include <cs50.h>
#include <stdio.h>

int main(void){
    int arr[3][3];
    int increment = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            arr[i][j] = increment;
            increment++;
        }
    }
    for(int a = 0; a < 3; a++){
        for(int b = 0; b < 3; b++){
            printf("%i ", arr[a][b]);
        }
        printf("\n");
    }
}