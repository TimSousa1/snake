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

    int hasGrown;
    int isDead;

    int size;   // might now matter

    Body *head;
    Body *tail;
} Player;

typedef struct {
    int cols;
    int lines;

    int apple[2];

    char **matrix;
} Board;

Board *create_board(int lines, int cols);
void fill_board(Board *board, char c);
void update_board(Board *board, Player *player);

void print_board(Board*);
Board *alloc_board(int lines, int cols);
void free_board(Board*);

void move_player(Player*);
void set_player_direction(Player *player, char key);
void grow_snake(Player *player);
void print_player(Player *player);

void create_apple(Board *board, Player *player);

#endif
