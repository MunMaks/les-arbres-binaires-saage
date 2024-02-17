CC = gcc
CFLAGS = -std=c17 -pedantic -Wall -Wfatal-errors
CLIBS = -lncurses
OPT = -O3

SRC_DIR = src
INC_DIR = include
OBJ_DIR = build
EXE = algo


SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))


INC = -I $(INC_DIR)


all: $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(OPT) $(CLIBS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OPT) $(INC) -c -o $@ $<


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# $(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/saage.h

# $(OBJ_DIR)/saage.o: $(SRC_DIR)/saage.c $(INC_DIR)/saage.h $(INC_DIR)/greffe.h

# $(OBJ_DIR)/greffe.o: $(SRC_DIR)/greffe.c $(INC_DIR)/greffe.h $(INC_DIR)/arbres_binaires.h

# $(OBJ_DIR)/arbres_binaires.o: $(SRC_DIR)/arbres_binaires.c $(INC_DIR)/arbres_binaires.h




# %.o: $(SRC_DIR)%.c
# 	$(CC) $(CFLAGS) -c -o $@ $<

# clean:
# 	rm -rf $(OBJ_DIR)/

# mrproper: clean

# uninstall: mrproper
# 	rm $(EXE)

# .PHONY: all clean mrproper install uninstall

.PHONY: all clean mrproper uninstall

all: $(EXE)

clean:
	rm -rf $(OBJ_DIR)

mrproper: clean
	rm -f $(EXE)

uninstall: mrproper
