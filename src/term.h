#ifndef T_TERM
#define T_TERM

#include <termios.h>
#include <unistd.h>

int enableRAW(struct termios *original);
int disableRAW(struct termios *original);

#endif
