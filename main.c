#include <stdio.h>

 char field[10][10];
    int i, j;

int main(){
    printf("Minesweeper version 0.0.2");
    // заповнення масиву
    for(i = 0; i < 10; i++) {
        for(j = 0; j < 10; j++) {
            field[i][j] = '#';
        }
    }

    // вивід масиву
    for(i = 0; i < 10; i++) {
        for(j = 0; j < 10; j++) {
            printf("%c ", field[i][j]);
        }
        printf("\n");
    }
    return 0;
}