// helper functions
#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>

// common functions (implementation's the same in arduino and c console)
int  numBadNeighbors(int* bomb_indices, int rows, int cols, int testIndex);
bool arrayHasElement(int* arr, int length, int value);


void print_board(char* arr, int rows, int cols);
void print_arr(int* arr, int arr_size);

// arduino requires that we #include these in the header
#ifdef ARDUINO
    #include "Helpers.ino"
#endif

#endif