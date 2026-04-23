#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10   // розмір поля (10x10)
#define MINES 10  // кількість мін

char field[SIZE][SIZE];      // поле, яке бачить гравець
char realField[SIZE][SIZE];  // справжнє поле з мінами

int firstMove = 1; // перевірка першого ходу

// перевірка чи координати в межах поля
int inBounds(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

// підрахунок мін навколо клітини
int count(int x, int y) {
    int c = 0;

    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            int nx = x + i;
            int ny = y + j;

            if(inBounds(nx, ny) && realField[nx][ny] == '*') {
                c++;
            }
        }
    }

    return c;
}

// генерація мін після першого кліку
void generate(int safeX, int safeY) {

    // очищаємо поле
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            realField[i][j] = '.';
        }
    }

    int placed = 0;

    // ставимо міни
    while(placed < MINES) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        // не ставимо міну біля першого кліку
        if(abs(x - safeX) <= 1 && abs(y - safeY) <= 1)
            continue;

        if(realField[x][y] != '*') {
            realField[x][y] = '*';
            placed++;
        }
    }
}

// вивід поля для гравця
void printField() {
    printf("\n  ");
    for(int i=0;i<SIZE;i++) printf("%d ", i);
    printf("\n");

    for(int i=0;i<SIZE;i++) {
        printf("%d ", i);
        for(int j=0;j<SIZE;j++) {
            printf("%c ", field[i][j]);
        }
        printf("\n");
    }
}

// адмін режим — показує всі міни
void showReal() {
    printf("\nADMIN:\n");
    for(int i=0;i<SIZE;i++) {
        for(int j=0;j<SIZE;j++) {
            printf("%c ", realField[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL)); // випадковість

    // заповнюємо поле #
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            field[i][j] = '#';
        }
    }

    char cmd;
    int x, y;

    while(1) {
        printField();
        printf("\ncommand (o x y | f x y | a): ");

        scanf(" %c", &cmd);

        // адмін команда
        if(cmd == 'a') {
            showReal();
            continue;
        }

        scanf("%d %d", &x, &y);

        if(!inBounds(x,y)) {
            printf("wrong coords\n");
            continue;
        }

        // відкриття клітини
        if(cmd == 'o') {

            // якщо перший хід — генеруємо поле
            if(firstMove) {
                generate(x,y);
                firstMove = 0;
            }

            // якщо міна — програш
            if(realField[x][y] == '*') {
                printf("\nBOOM\n");

                // показуємо всі міни
                for(int i=0;i<SIZE;i++){
                    for(int j=0;j<SIZE;j++){
                        if(realField[i][j] == '*')
                            field[i][j] = '*';
                    }
                }

                printField();
                break;
            }

            // показуємо цифру
            int c = count(x,y);
            field[x][y] = c + '0';
        }

        // прапорець
        else if(cmd == 'f') {
            if(field[x][y] == '#')
                field[x][y] = 'F';
            else if(field[x][y] == 'F')
                field[x][y] = '#';
        }
    }

    return 0;
}