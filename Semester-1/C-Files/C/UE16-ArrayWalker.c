#include <stdio.h>

void printArray(char array[10][10], char player, int x, int y){
    array[x][y] = player;
    for (int i = 0; i < 10 ; ++i) {
        for (int j = 0; j < 10; ++j) {
            printf("%c", array[i][j]);
        }
        printf("\n");
    }
}

int main(){
    char array[10][10];
    char input = ' ';
    int x = 0, y = 0;
    for (int i = 0; i < 10 ; ++i) {
        for (int j = 0; j < 10; ++j) {
            array[i][j] = '.';
        }
    }
    char player = 'A';
    printArray(array, player, x, y);
    while(1){
        printf("walk to: \n");
        scanf(" %c", &input);
        if(input == 'x') break;
        switch (input) {
            case 'n':
                if(x > 0 && array[x - 1][y] == '.'){
                    --x;
                }
                else {
                    printf("not possible\n");
                    continue;
                }
                break;

            case 'e':
                if(y < 9 && array[x][y + 1] == '.'){
                    ++y;
                }
                else {
                    printf("not possible\n");
                    continue;
                }
                break;


            case 's':
                if(x < 9 && array[x + 1][y] == '.'){
                    ++x;
                }
                else {
                    printf("not possible\n");
                    continue;
                }
                break;

            case 'w':
                if(y > 0 && array[x][y - 1] == '.'){
                    --y;
                }
                else {
                    printf("not possible\n");
                    continue;  // Skip the rest of the loop and ask for input again
                }
                break;

            default:
                printf("not possible\n");
                continue;
        }

        // Update the player letter
        if (player == 'Z') {
            player = 'A';
        } else {
            ++player;
        }

        // Print the array with the updated player position and letter
        printArray(array, player, x, y);
    }

    return 0;
}