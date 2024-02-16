CC = gcc
CFLAGS = -std=c17 -pedantic -Wall -Wfatal-errors
LIBS = -lMLV -lncurses -lm

SRC_DIR = src/
INC_DIR = include/
OBJ_DIR = build/


SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

EXE = algo



all: $(BIN_DIR)/$(EXE)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/saage.h

$(OBJ_DIR)/saage.o: $(SRC_DIR)/saage.c $(INC_DIR)/saage.h $(INC_DIR)/greffe.h

$(OBJ_DIR)/greffe.o: $(SRC_DIR)/greffe.c $(INC_DIR)/greffe.h $(INC_DIR)/arbres_binaires.h

$(OBJ_DIR)/arbres_binaires.o: $(SRC_DIR)/arbres_binaires.c $(INC_DIR)/arbres_binaires.h




%.o: $(SRC_DIR)%.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -rf $(OBJ_DIR)/

mrproper: clean
	rm -rf $(BIN_DIR)/

uninstall: mrproper
	rm $(EXE)

.PHONY: all clean mrproper install uninstall
