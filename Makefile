CC = gcc
CFLAGS = -Wall -Werror -g
BINS = testGameView testHunterView testDracView

all : $(BINS)

testGameView 		: testGameView.o GameView.o Graph.o Places.o Queue.o
testGameView.o 	: testGameView.c Globals.h Game.h 

testHunterView 	: testHunterView.o HunterView.o Graph.o Places.o Queue.o
testHunterView.o 	: testHunterView.c Map.c Places.h

testDracView 		: testDracView.o DracView.o Graph.o Places.o Queue.o
testDracView.o 	: testDracView.c Map.c Places.h

Queue.o 				: Queue.c Queue.h
Graph.o 				: Graph.c Graph.h
Places.o 			: Places.c Places.h
Map.o 				: Map.c Map.h Places.h
GameView.o 			: GameView.c GameView.h
HunterView.o 		: HunterView.c HunterView.h
DracView.o 			: DracView.c DracView.h

clean :
	rm -f $(BINS) *.o core

