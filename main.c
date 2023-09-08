#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ROWS 8
#define COLS 9
#define NUMBOMBS 16

// all these thresholds are inclusive
#define GREEN_THRESHOLD 0
#define GREEN_VALUE 1
#define BLUE_THRESHOLD 2
#define BLUE_VALUE 5
#define RED_THRESHOLD 8
#define RED_VALUE 20

int numBadNeighbors(int rows, int cols, int testIndex);
void print_board(char* arr, int rows, int cols);
int arrayHasElement(int* arr, int length, int value);
bool isBad(int index);

// needs to be global such that isBad can access
int* bomb_indices;

int main() {
    srand(time(NULL));

    char* gameboard = (char*) malloc(ROWS*COLS*sizeof(char));
    for(int i = 0; i < ROWS*COLS; i++) {
        gameboard[i] = ' ';
    }

    bomb_indices = (int*) malloc(NUMBOMBS*sizeof(int));

    // this forloop fills the bomb_indices array with NUMBOMBS distinct ints in [0, ROWS*COLS)
    for(int i = 0; i < NUMBOMBS; i++) {
        rerollBombIndex:
        bomb_indices[i] = rand() % (ROWS*COLS);

        for(int j = 0; j < i; j++) {
            if(bomb_indices[i] == bomb_indices[j]) {
                goto rerollBombIndex;
            }
        }
    }

    // each turn goes like this
    int playerCredit = 0;
    char buffer[100];
    print_board(gameboard, ROWS, COLS);
    fflush(stdout);
    while(true) {

        char userColChar;
        int userRow;
        int userCol;

        rescan_userInput:
        userRow = userCol = -1;
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%c %d", &userColChar, &userRow);

        fflush(stdin);

        // quicker atoi
        userCol = userColChar - 'a';

        // sanitize the input
        // check if input is in bounds and if that square has been checked already
        if(userRow < 0 || userRow >= ROWS || userCol < 0 || userCol >= COLS || gameboard[userRow*COLS + userCol] != ' ') goto rescan_userInput;


        int userIndex = userRow*COLS + userCol;

        int badNeighbors = numBadNeighbors(ROWS, COLS, userIndex);
        if(isBad(userIndex)) {
            printf("GAME OVER ):<\n");
            break;
        } else if(badNeighbors <= GREEN_THRESHOLD) {
            gameboard[userIndex] = 'G';
            playerCredit += GREEN_VALUE;
        } else if(badNeighbors <= BLUE_THRESHOLD) {
            gameboard[userIndex] = 'B';
            playerCredit += BLUE_VALUE;
        } else if(badNeighbors <= RED_THRESHOLD) {
            gameboard[userIndex] = 'R';
            playerCredit += RED_VALUE;
        }

        print_board(gameboard, ROWS, COLS);
        fflush(stdout);
    }

    return 0;
}

// check if the element "index" appears in "bomb_indices"
bool isBad(int index) {
    for(int i = 0; i < NUMBOMBS; i++) {
        if(bomb_indices[i] == index) return true;
    }

    return false;
}

int numBadNeighbors(int rows, int cols, int testIndex) {
    int result = 0;

    bool hasLeftNeighbor = (testIndex % cols != 0);
    bool hasRightNeighbor = ((testIndex+1) % cols != 0);

    bool hasUpperNeighbor = (testIndex / cols != 0);
    bool hasLowerNeighbor = (testIndex / cols != rows - 1);


    // check upper left neighbor
    if(hasUpperNeighbor && hasLeftNeighbor) {
        if(isBad(testIndex - 1 - cols)) {
            result++;
        }
    }

    // check upper neighbor
    if(hasUpperNeighbor) {
        if(isBad(testIndex - cols)) {
            result++;
        }
    }

    // check upper right neighbor
    if(hasUpperNeighbor && hasRightNeighbor) {
        if(isBad(testIndex + 1 - cols)) {
            result++;
        }
    }

    // check left neighbor
    if(hasLeftNeighbor) {
        if(isBad(testIndex - 1)) {
            result++;
        }
    }

    // check right neighbor
    if(hasRightNeighbor) {
        if(isBad(testIndex + 1)) {
            result++;
        }
    }

    // check lower left neighbor
    if(hasLowerNeighbor && hasLeftNeighbor) {
        if(isBad(testIndex + cols - 1)) {
            result++;
        }
    }

    // check lower neighbor
    if(hasLowerNeighbor) {
        if(isBad(testIndex + cols)) {
            result++;
        }
    }

    // check lower right neighbor
    if(hasLowerNeighbor && hasRightNeighbor) {
        if(isBad(testIndex + cols + 1)) {
            result++;
        }
    }



    return result;
}

void print_board(char* arr, int rows, int cols) {
    // first we print the letters adorning the top of the board
    
    // space for letter in left margin
    printf(" ");
    for(int i = 0; i < cols; i++) {
        printf(" %c", 'a'+i);
    }
    printf("\n");

    // first row of hyphens
    printf(" ");
    for(int i = 0; i < cols*2 + 1; i++) {
        printf("-");
    }
    printf("\n");

    // printing the rest of the board
    for(int i = 0; i < rows; i++) {
        printf("%d|", i);
        for(int j = 0; j < cols; j++) {
            printf("%c|", arr[i*cols + j]);
        }
        printf("\n");

        // printing the hyphens
        printf(" ");
        for(int j = 0; j < cols*2 + 1; j++) {
            printf("-");
        }
        printf("\n");
    }

}