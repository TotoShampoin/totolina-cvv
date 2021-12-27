
INC = inc

BIN = bin/cvv
SRC = src/main.c src/CVV/CVV_DATA.c src/CVV/CVV_FILE.c src/CVV/CVV_GAME.c src/Disp_TER.c

$(BIN): $(SRC)
	gcc -i $(INC) $(SRC) -o $(BIN)