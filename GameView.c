// GameView.c ... GameView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Map.h"

#define PLAYERS 4

struct gameView {

	MapRep *map;

	int turnNum;
	/*
	[player ID][stat id]
	stat ids:
	0 - location
	1 - health
	*/
	int playerStats[PLAYERS][2];

};
	 

// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[])
{
	GameView g = malloc(sizeof(struct gameView));
	
	g->turnNumber = 0;
	int c = 0;
	for (c;c<PLAYERS;c++) {
		
	}
	
	return g;
}
	 
	 
// Frees all memory previously allocated for the GameView toBeDeleted
void disposeGameView(GameView toBeDeleted)
{
	//COMPLETE THIS IMPLEMENTATION
	free( toBeDeleted );
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round getRound(GameView currentView)
{
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	return 0;
}

// Get the id of current player - ie whose turn is it?
PlayerID getCurrentPlayer(GameView currentView)
{
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	return 0;
}

// Get the current score
int getScore(GameView currentView)
{
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	return 0;
}

// Get the current health points for a given player
int getHealth(GameView currentView, PlayerID player)
{
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	return 0;
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player)
{
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	return 0;
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void getHistory(GameView currentView, PlayerID player,
	                        LocationID trail[TRAIL_SIZE])
{
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
}

//// Functions that query the map to find information about connectivity

// Returns an array of LocationIDs for all directly connected locations

LocationID *connectedLocations(GameView currentView, int *numLocations,
	                           LocationID from, PlayerID player, Round round,
	                           int road, int rail, int sea)
{
	//REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	return NULL;
}
