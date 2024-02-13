SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .c .o

CC := gcc

OUTNAME := snake
SRC := $(shell find . -name '*.c')
OBJ := $(SRC:%.c=%.o)
DEPS := $(shell find . -name '*.h')

all: $(OBJ) compile

compile : $(OBJ)
	$(CC) -o $(OUTNAME) $^

.PHONY : clean
clean:
	rm $(OBJ) $(OUTNAME)
