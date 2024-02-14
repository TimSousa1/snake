#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>

#include "term.h"
#include "snake.h"

#define LINES 15
#define COLS 30

#define SPEED .5


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
    enableRAW(&original, SPEED * 10);       // SPEED should be set on a different func

    // frametime info
    struct timespec initFRAME;
    struct timespec midFRAME;
    struct timespec endFRAME;

    struct timespec ft;         // time that should be spent
    struct timespec pt;         // time spent processing
    struct timespec dt;         // total time spent on frame
    struct timespec remaining;  // time to wait for next frame

    ft.tv_sec = 0;
    ft.tv_nsec = 0.5 * 1e9;

    // game
    char key;
    Board *board = create_board(LINES, COLS);

    Player player;
    Body start;

    start.posx = board->cols / 2;
    start.posy = board->lines / 2;

    player.size = 1;
    player.direction = RIGHT;
    player.head = &start;
    player.head->next = NULL;
    player.tail = player.head;

    while (1){
        clock_gettime(CLOCK_MONOTONIC, &initFRAME);
        clear_screen();
        move_player(&player);
        update_board(board, &player);
        print_board(board);

        printf("\n[%c](%i)\npress 'q' to exit\n", key, player.direction);

        read(STDIN_FILENO, &key, sizeof(key));
        tcflush(STDIN_FILENO, TCIFLUSH);              // flushing what wasn't read
        // printf("got %c from stdin in RAW mode\n", key);

        if (key == 'q') break;

        switch (key) {
            case 'w':
                player.direction = UP;
                break;
            case 'a':
                player.direction = LEFT;
                break;
            case 's':
                player.direction = DOWN;
                break;
            case 'd':
                player.direction = RIGHT;
                break;

            default:
                break;
        }

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
