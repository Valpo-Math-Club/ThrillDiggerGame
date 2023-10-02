#include "Helpers.h"

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

