
INC = inc

SRC_CVV = $(wildcard src/CVV/*.c)

BIN = bin/cvv
SRC = src/main.c $(SRC_CVV) src/Disp_TER.c src/Disp_MLV.c src/Control_MLV.c src/Control_TER.c src/msleep.c

$(BIN): $(SRC)
	gcc -Wall -g -I $(INC) $(SRC) -o $(BIN) -lMLV