BIN=cubical
CFLAGS= -Wall -Wextra -g

all:
	g++ $(CFLAGS) main.cpp -o $(BIN)

run:
	./$(BIN)
