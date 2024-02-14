#include "snake.h"
#include <stdio.h>
#include <stdlib.h>

#define EMPTY ' '
#define SNAKE '#'

void grow_snake(Player *player){
    Body *new = malloc (sizeof(*new));

    new->posx = player->tail->posx;
    new->posy = player->tail->posy;

    new->next = player->tail;

    player->tail = new;
    player->hasGrown = 1;
}

void set_player_direction(Player *player, char key){
    int dir = player->direction;

    switch (key) {
        case 'w':
            if (dir == DOWN) break;
            dir = UP;
            break;
        case 'a':
            if (dir == RIGHT) break;
            dir = LEFT;
            break;
        case 'r':
            if (dir == UP) break;
            dir = DOWN;
            break;
        case 's':
            if (dir == LEFT) break;
            dir = RIGHT;
            break;

        case 'g':
            grow_snake(player);

        default:
            break;
    }

    player->direction = dir;
}

void move_player(Player *player){
    Body *itStart = player->tail;

    if (player->hasGrown) {
        itStart = player->tail->next;
        player->hasGrown = 0;
    }

    for (Body *iteration = itStart; iteration; iteration = iteration->next){
        if (iteration == player->head){
            switch (player->direction) {
                case UP:
                    iteration->posy--;
                    break;
                case DOWN:
                    iteration->posy++;
                    break;
                case LEFT:
                    iteration->posx--;
                    break;
                case RIGHT:
                    iteration->posx++;
                    break;
                default:
                    break;
            }
            break;
        }
        iteration->posx = iteration->next->posx;
        iteration->posy = iteration->next->posy;
    }
}

void print_player(Player *player){

    printf("dir: %i | hasGrown: %i\n", player->direction, player->hasGrown);

    for (Body *iteration = player->tail; iteration; iteration = iteration->next){
        printf("(%i,%i)--", iteration->posx, iteration->posy);
    }

    putchar('\n');
}

void update_board(Board *board, Player *player){
    fill_board(board, EMPTY);

    for (Body *iteration = player->tail; iteration; iteration = iteration->next){
        iteration->posx += board->cols * (iteration->posx <= 0);
        iteration->posy += board->lines * (iteration->posy <= 0);

        iteration->posx %= board->cols;
        iteration->posy %= board->lines;

        board->matrix[iteration->posy][iteration->posx] = SNAKE;
    }
}

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
    for (int i = 0; i < board->cols; i++) putchar('_');
    printf("\n");
    for (int i = 0; i < board->lines; i++){
        printf("|%s|\n", board->matrix[i]);
    }
    for (int i = 0; i < board->cols; i++) putchar('_');
    printf("\n");
}
