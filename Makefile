CC = gcc
CFLAGS = -std=c17 -pedantic -Wall -Wfatal-errors -Werror -Wextra -finline-functions -funroll-loops -ansi
CLIBS = 
OPT = -O3
ARCHIVE = MUNAITPASOV_NAVARRO

SRC_DIR = src
INC_DIR = include
OBJ_DIR = build
EXEMPLES = exemples
EXE = saage


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



dist: clean
	mkdir -p $(ARCHIVE)
	cp -R makefile rapport_MUNAITPASOV_NAVARRO.pdf graph.png $(SRC_DIR) $(INC_DIR) $(EXEMPLES) $(ARCHIVE)
	zip -r $(ARCHIVE).zip $(ARCHIVE)
	rm -rf $(ARCHIVE)

.PHONY: all clean mrproper uninstall

clean:
	rm -rf $(OBJ_DIR)

mrproper: clean
	rm -f $(EXE)

uninstall: mrproper
	rm -f $(ARCHIVE).zip
