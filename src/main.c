#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>

#include "term.h"
#include "snake.h"

#define LINES 15
#define COLS 30

#define SPEED .2
#define INIT_SIZE 3


double read_time(struct timespec *a){
    double s;
    s = a->tv_sec;
    s += a->tv_nsec / 1e9;

    return s;
}

struct timespec time_diff(struct timespec *a, struct timespec *b){
    struct timespec diff;

    diff.tv_sec = a->tv_sec - b->tv_sec;
    diff.tv_nsec = a->tv_nsec - b->tv_nsec;

    return diff;
}

int main(void){
    // getting terminal ready
    struct termios original;
    enableRAW(&original, SPEED * 10);       // SPEED should be set on a different func (speeding game up if needed)

    // frametime info
    struct timespec initFRAME;
    struct timespec midFRAME;
    struct timespec endFRAME;

    struct timespec ft;         // time that should be spent
    struct timespec pt;         // time spent processing
    struct timespec dt;         // total time spent on frame
    struct timespec remaining;  // time to wait for next frame

    ft.tv_sec = 0;
    ft.tv_nsec = SPEED * 1e9;

    // game
    char key;
    Board *board = create_board(LINES, COLS);

    Player player;
    Body start;

    start.posx = board->cols / 2;
    start.posy = board->lines / 2;

    player.size = 1;
    player.hasGrown = 0;
    player.direction = RIGHT;
    player.head = &start;
    player.head->next = NULL;
    player.tail = player.head;

    for (int i = 1; i < INIT_SIZE; i++) grow_snake(&player);

    while (1){
        clock_gettime(CLOCK_MONOTONIC, &initFRAME);
        clear_screen();
        move_player(&player);

        update_board(board, &player);
        print_board(board);

        print_player(&player);

        printf("\n[%c](%i)\npress 'q' to exit\n", key, player.direction);

        read(STDIN_FILENO, &key, sizeof(key));
        tcflush(STDIN_FILENO, TCIFLUSH);              // flushing what wasn't read
        // printf("got %c from stdin in RAW mode\n", key);

        if (key == 'q') break;

        set_player_direction(&player, key);

        clock_gettime(CLOCK_MONOTONIC, &midFRAME);
        pt = time_diff(&midFRAME, &initFRAME);
        remaining = time_diff(&ft, &pt);

        nanosleep(&remaining, NULL);
        clock_gettime(CLOCK_MONOTONIC,&endFRAME);

        dt = time_diff(&endFRAME, &initFRAME);
        // printf("time taken on frame: %lf\n", read_time(&dt));
    }

    disableRAW(&original);
    return 0;
}
