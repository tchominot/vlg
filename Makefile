CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -pedantic -I/usr/include/igraph -ligraph

SRC_FILES=vlg.c \
          graph-data.c \
          graph-loader.c \
          pick-point.c \
          preprocess.c \
          strategy.c \
          sweep-core.c \
          sweeps.c \
          vecutils.c
OBJ_FILES=$(SRC_FILES:.c=.o)

SRC_DIR=src
OBJ_DIR=obj

SRC=$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ=$(addprefix $(OBJ_DIR)/, $(OBJ_FILES))
EXE=vlg

all: debug

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

opti: CFLAGS += -O3 -DNDEBUG
opti: $(EXE)

debug: CFLAGS += -Og -g
debug: $(EXE)

clean:
	$(RM) $(OBJ) $(EXE)

.PHONY: all clean debug
