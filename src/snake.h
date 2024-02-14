#ifndef T_SNAKE
#define T_SNAKE

#include <stdio.h>
#include <stdlib.h>

enum MOVE {
    UP, DOWN, LEFT, RIGHT
};

typedef struct _body {
    int posx;
    int posy;
    struct _body *next;
} Body;

typedef struct {
    int direction;

    int size;

    Body *head;
    Body *tail;
} Player;

typedef struct {
    int cols;
    int lines;

    char **matrix;
} Board;

Board *create_board(int lines, int cols);
void fill_board(Board *board, char c);
void update_board(Board *board, Player *player);

void print_board(Board*);
Board *alloc_board(int lines, int cols);
void free_board(Board*);

void move_player(Player*);

#endif
