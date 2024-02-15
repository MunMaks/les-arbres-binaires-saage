CC = gcc
CFLAGS = -std=c17 -pedantic -Wall -Wfatal-errors
LIBFLAGS = -lMLV -lncurses

SRC_DIR = src/
INC_DIR = include/


SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

EXE = algo



%.o: $(SRC_DIR)%.c
	$(CC) -c $< $(CFLAGS)

