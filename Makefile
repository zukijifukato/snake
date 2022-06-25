CC=g++

CFLAGS=-g -Wall

all: clean game run

game: Core.cpp main.cpp Text.cpp
	$(CC) -c Core.cpp -lSDL2 -lSDL2_ttf -I/usr/lib
	$(CC) -c main.cpp -I/usr/lib
	$(CC) -c Text.cpp -I/usr/lib
	$(CC) Text.o Core.o main.o -o game -lSDL2 -lSDL2_ttf -I/usr/lib
	
run: game
	./game

clean:
	rm -rf *.o
	rm -rf game