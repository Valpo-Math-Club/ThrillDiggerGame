#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
//personal headers
#include "./../lib/thrill_digger.h"

#define DEBUG_STATEMENTS false
// constants
const int  THRESHOLDS[NUM_RUPEE_TYPES] = {0, 2, 4, 6, 8};
const int  VALUES[NUM_RUPEE_TYPES] = {1, 5, 20, 100, 300};
const char BOARD_CHARS[NUM_RUPEE_TYPES] = {'G', 'B', 'R', 'S', 'Y'};
// functions
int  numBadNeighbors(int* bomb_indices, int rows, int cols, int testIndex);
void print_arr(int* arr, int arr_size);
void print_board(char* arr, int rows, int cols);
bool arrayHasElement(int* arr, int length, int value);

int main(void) {
	int playerCredit = 0;

	char buffer[100];
	int bomb_indices[NUM_BOMBS];
	char* gameboard = calloc(BOARD_SIZE, sizeof(char));

	srand(time(NULL));

	for(int i = 0; i < BOARD_SIZE; i++) gameboard[i] = ' ';

	// this forloop fills the bomb_indices array with NUM_BOMBS distinct ints in [0, ROWS*COLS)
	for(int i = 0; i < NUM_BOMBS; i++) {
		bomb_indices[i] = rand() % (BOARD_SIZE);
		if(DEBUG_STATEMENTS) print_arr(bomb_indices, NUM_BOMBS);

		for(int j = 0; j < i; j++) {
			if(bomb_indices[i] == bomb_indices[j]) {
				i--;
			}
		}

		if(DEBUG_STATEMENTS) sleep(1);
	}

	print_board(gameboard, ROWS, COLS);
	fflush(stdout);

	while(true) {
		int userRow, userCol;
		char userColChar;
		bool outside_row_range, outside_col_range, non_empty_space;

		do {
			userRow = userCol = -1;
			fgets(buffer, sizeof(buffer), stdin);
			sscanf(buffer, "%c %d", &userColChar, &userRow);

			fflush(stdin);
			
			userCol = userColChar - 'a'; // quicker atoi

			outside_row_range = (userRow < 0 || userRow >= ROWS);
			outside_col_range = (userCol < 0 || userCol >= COLS);
			non_empty_space   = gameboard[userRow*COLS + userCol] != ' ';
		} while(outside_row_range || outside_col_range || non_empty_space);

		int userIndex = (userRow * COLS) + userCol;
		int badNeighbors = numBadNeighbors(bomb_indices, ROWS, COLS, userIndex);

		if(arrayHasElement(bomb_indices, NUM_BOMBS, userIndex)) {
			printf("GAME OVER ):<\n");
			return 0;
		}
		else{
			for(int i = GREEN_RUPEE; i < NUM_RUPEE_TYPES; i++){
				if(badNeighbors <= THRESHOLDS[i]){
					gameboard[userIndex] = BOARD_CHARS[i];
					playerCredit += VALUES[i];
					break;
				}
			}

			printf("Credit: %d\n", playerCredit);
			print_board(gameboard, ROWS, COLS);
			fflush(stdout);
		}
	}
}

bool arrayHasElement(int* arr, int length, int value){
	for(int i = 0; i < length; i++)
		if(arr[i] == value) return true;
	
	return false;
}

int numBadNeighbors(int* bomb_indices, int rows, int cols, int testIndex) {
	int result = 0;

	bool hasLeftNeighbors  = ((testIndex % cols) != 0);
	bool hasRightNeighbors = (((testIndex + 1) % cols ) != 0);
	bool hasUpperNeighbors = ((testIndex / cols) != 0);
	bool hasLowerNeighbors = ((testIndex / cols) != (rows - 1));
	// there's definitely a better way to do this, but this is more concise
	// to-do: refactor later
	if(hasUpperNeighbors) {
		if(hasLeftNeighbors){
			if(arrayHasElement(bomb_indices, NUM_BOMBS, testIndex - 1 - cols))
				result++;
		}
		if(hasRightNeighbors){
			if(arrayHasElement(bomb_indices, NUM_BOMBS, testIndex + 1 - cols))
				result++;
		}
		if(arrayHasElement(bomb_indices, NUM_BOMBS, testIndex - cols))
			result++;
	}
	if(hasLowerNeighbors){
		if(hasLeftNeighbors){
			if(arrayHasElement(bomb_indices, NUM_BOMBS, testIndex + cols - 1))
				result++;
		}
		if(hasRightNeighbors){
			if(arrayHasElement(bomb_indices, NUM_BOMBS, testIndex + cols + 1))
				result++;
		}
		if(arrayHasElement(bomb_indices, NUM_BOMBS, testIndex + cols))
			result++;
	}
	if(hasLeftNeighbors){
		if(arrayHasElement(bomb_indices, NUM_BOMBS, testIndex - 1))
			result++;
	}
	if(hasRightNeighbors){
		if(arrayHasElement(bomb_indices, NUM_BOMBS, testIndex + 1))
			result++;
	}

	return result;
}

void print_arr(int* arr, int arr_size){
	printf("[ ");
	for(int i = 0; i < arr_size; i++){
		printf("%d ", arr[i]);
	}
	printf("]\n");
}

void print_board(char* arr, int rows, int cols) {
	// first we print the letters adorning the top of the board

	// space for letter in left margin
	printf(" ");
	for(int i = 0; i < cols; i++) {
		printf(" %c", 'a' + i);
	}
	printf("\n");

	// first row of hyphens
	printf(" ");
	for(int i = 0; i < (cols * 2) + 1; i++) {
		printf("-");
	}
	printf("\n");

	// printing the rest of the board
	for(int i = 0; i < rows; i++) {
		printf("%d|", i);
		for(int j = 0; j < cols; j++) {
			printf("%c|", arr[(i * cols) + j]);
		}
		printf("\n");

		// printing the hyphens
		printf(" ");
		for(int j = 0; j < (cols * 2) + 1; j++) {
			printf("-");
		}
		printf("\n");
	}

}

