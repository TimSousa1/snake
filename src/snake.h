#ifndef T_SNAKE
#define T_SNAKE

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int cols;
    int lines;

    char **matrix;
} Board;

Board *create_board(int lines, int cols);
Board *alloc_board(int lines, int cols);
void print_board(Board*);
void fill_board(Board *board, char c);
void free_board(Board*);

#endif
