SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .c .o

CC := gcc

CFLAGS = -ggdb

OUTNAME := snake
SRC := $(shell find . -name '*.c')
OBJ := $(SRC:%.c=%.o)
DEPS := $(shell find . -name '*.h')

all: $(OBJ) compile

compile : $(OBJ)
	$(CC) -o $(OUTNAME) $^ $(CFLAGS)

.PHONY : clean
clean:
	rm $(OBJ) $(OUTNAME)
