// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "DracView.h"

void decideDraculaMove(DracView gameState)
{
	int numLocations;
	LocationID* possibleLocations;

	possibleLocations = whereCanIgo(gameState, &numLocations, TRUE, FALSE);

	


	registerBestPlay("CD","Mwuhahahaha");
	




	
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
