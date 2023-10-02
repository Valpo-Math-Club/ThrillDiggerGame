// helper functions
#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>

// arduino is fkin weird man
#ifdef ARDUINO
    #include "CommonFunctions.ino"
    #include "Helpers.ino"
#endif


int  numBadNeighbors(int* bomb_indices, int rows, int cols, int testIndex);
bool arrayHasElement(int* arr, int length, int value);
void print_board(char* arr, int rows, int cols);
void print_arr(int* arr, int arr_size);

#endif