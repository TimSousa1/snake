#include "snake.h"
#include <stdio.h>
#include <stdlib.h>

#define EMPTY '$'

Board *create_board(int lines, int cols){
    Board *board = alloc_board(lines, cols);
    if (!board) return NULL;

    fill_board(board, EMPTY);
    return board;
}

Board *alloc_board(int lines, int cols){
    Board *board;

    char **matrix = calloc(lines, sizeof(char*));
    if (!matrix) return NULL;

    for (int i = 0; i < lines; i++){
        matrix[i] = calloc(cols +1, 1);

        if (!matrix[i]) {
            for (int j = 0; j < i; j++){
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }

    }

    board = malloc(sizeof(*board));
    board->cols = cols;
    board->lines = lines;
    board->matrix = matrix;

    return board;
}

void fill_board(Board *board, char c){
    for (int i = 0; i < board->lines; i++){
        for (int j = 0; j < board->cols; j++){
            board->matrix[i][j] = c;
        }
        board->matrix[i][board->cols +1] = 0;
    }
}

void free_board(Board *board){
    for (int i = 0; i < board->lines; i++){
        free(board->matrix[i]);
    }
    free(board->matrix);
    free(board);
}

void print_board(Board *board){
    for (int i = 0; i < board->lines; i++){
        printf("%s\n", board->matrix[i]);
    }
}