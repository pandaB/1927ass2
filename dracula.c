// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Game.h"
#include "DracView.h"


int dracRandomMove(DracView gameState);

void decideDraculaMove(DracView gameState)
{
	// Seeding srand
	srand(time(NULL));
	// Getting random move
	int move = dracRandomMove(gameState);
	// Converting location ID to location string
	char* moveTo = idToAbbrev(move);


	registerBestPlay(moveTo, "SHIGGLES");
	




	
	/*
	
	Random Move Immediately: Everything
		remeber to not make illegal moves
		Not ocean
		
	Don't move within 1 of a hunter
	
	If below 10 life, move towards castle
	Rail links?
	\
	
	Weighted Moves:
	
	Away from hunters
	If below 10 life, move towards castle
	When to ocen
	Look for bottlenecks and make traps
	
	
	
	*/
}

int dracRandomMove(DracView gameState)
{
	int* numLocations = NULL;
	int* possibleLocs = whereCanIgo(gameState, numLocations, TRUE, FALSE);

	int randIndex = (rand()%(*numLocations-1));
	return possibleLocs[randIndex];
}


