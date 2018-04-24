CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -pedantic -I/usr/include/igraph -ligraph

SRC_FILES=vlg.c

OBJ_FILES=$(SRC_FILES:.c=.o)

SRC=$(addprefix src/, $(SRC_FILES))
OBJ=$(addprefix obj/, $(OBJ_FILES))

all: vlg-opti

vlg: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ):
	mkdir -p obj
	$(CC) $(CFLAGS) $(SRC) -c -o $(OBJ)

vlg-opti: CFLAGS += -O3
vlg-opti: vlg

vlg-debug: CFLAGS += -g -Og
vlg-debug: vlg

clean:
	$(RM) $(OBJ) vlg

.PHONY: all clean vlg-debug
