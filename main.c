#include <bits/time.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>

#include "term.h"

double read_time(struct timespec *a){
    double s;
    s = a->tv_sec;
    s += a->tv_nsec / 1e9;

    return s;
}

struct timespec timeDiff(struct timespec *a, struct timespec *b){
    struct timespec diff;

    diff.tv_sec = a->tv_sec - b->tv_sec;
    diff.tv_nsec = a->tv_nsec - b->tv_nsec;

    return diff;
}

int main(void){
    struct termios original;
    enableRAW(&original);

    struct timespec initFRAME;
    struct timespec midFRAME;
    struct timespec endFRAME;

    char c;

    struct timespec ft;         // time that should be spent
    struct timespec pt;         // time spent processing
    struct timespec dt;         // total time spent on frame
    struct timespec remaining;  // time to wait for next frame

    ft.tv_sec = 0;
    ft.tv_nsec = 0.1 * 1e9;

    while (1){
        clock_gettime(CLOCK_MONOTONIC, &initFRAME);

        read(STDIN_FILENO, &c, sizeof(c));
        tcflush(STDIN_FILENO, TCIFLUSH);              // flushing what wasn't read
        printf("got %c from stdin in RAW mode\n", c);
        if (c == 'q') break;

        clock_gettime(CLOCK_MONOTONIC, &midFRAME);
        pt = timeDiff(&midFRAME, &initFRAME);
        remaining = timeDiff(&ft, &pt);
        nanosleep(&remaining, NULL);
        clock_gettime(CLOCK_MONOTONIC,&endFRAME);
        dt = timeDiff(&endFRAME, &initFRAME);
        printf("time taken on frame: %lf\n", read_time(&dt));
    }

    disableRAW(&original);
    return 0;
}
