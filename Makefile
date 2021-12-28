
INC = inc

SRC_CVV = $(wildcard src/CVV/*.c)

BIN = bin/cvv
SRC = src/main.c $(SRC_CVV) src/Disp_TER.c

$(BIN): $(SRC)
	gcc -g -I $(INC) $(SRC) -o $(BIN)