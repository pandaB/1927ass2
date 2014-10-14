// HunterView.c ... HunterView ADT implementation

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "HunterView.h"


// #include "Map.h" ... if you decide to use the Map ADT
	
struct hunterView {
	GameView view;
	PlayerMessage *stored_messages;
};


// Creates a new HunterView to summarise the current state of the game
HunterView newHunterView(char *pastPlays, PlayerMessage messages[])
{
	HunterView hunterView = malloc(sizeof(struct hunterView));
	assert(hunterView!=NULL);
	hunterView->view = newGameView(pastPlays, messages);
	
	int turn = giveMeTurnNum(hunterView);
	hunterView->stored_messages = malloc(sizeof(PlayerMessage)*turn);
	   
	int i;
	for (i=0;i<turn;i++) {
		strncpy(hunterView->stored_messages[i], messages[i], MESSAGE_SIZE);
	}
	
	return hunterView;
}
	
	
// Frees all memory previously allocated for the HunterView toBeDeleted
void disposeHunterView(HunterView toBeDeleted)
{
	disposeGameView(toBeDeleted->view);
	free (toBeDeleted->stored_messages);
	free(toBeDeleted);
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round giveMeTheRound(HunterView currentView)
{
	return getRound(currentView->view);
}

// Get the id of current player
PlayerID whoAmI(HunterView currentView)
{
	return getCurrentPlayer(currentView->view);
}

// Get the current score
int giveMeTheScore(HunterView currentView)
{
	return getScore(currentView->view);
}

// Get the current health points for a given player
int howHealthyIs(HunterView currentView, PlayerID player)
{
	assert (player<NUM_PLAYERS);
	return getHealth(currentView->view, player);
}

// Get the current location id of a given player
LocationID whereIs(HunterView currentView, PlayerID player)
{
	assert (player<NUM_PLAYERS);
	LocationID playerLoc = getLocation(currentView->view, player);
	
	return playerLoc;
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(HunterView currentView, PlayerID player,
					   LocationID trail[TRAIL_SIZE])
{
	assert (player<NUM_PLAYERS);
	getHistory(currentView->view, player, trail);
}

//// Functions that query the map to find information about connectivity

// What are my possible next moves (locations)
LocationID *whereCanIgo(HunterView currentView, int *numLocations, int road, int rail, int sea)
{
	LocationID *edges;
	PlayerID currHunter = whoAmI(currentView);
	edges = connectedLocations(currentView->view, numLocations, getLocation(currentView->view, currHunter), currHunter, getRound(currentView->view), road, rail, sea);
	return edges;
}

// What are the specified player's next possible moves
LocationID *whereCanTheyGo(HunterView currentView, int *numLocations,
					  PlayerID player, int road, int rail, int sea)
{
	LocationID *edges;
  
	edges = connectedLocations(currentView->view, numLocations, getLocation(currentView->view, player), player, getRound(currentView->view), road, rail, sea);
	return edges;
}

void getMessages(HunterView h, PlayerMessage *messages)
{
	int i;
	int round = giveMeTurnNum(h);
	for (i=0;i<round;i++) {
		printf("message[%d]: %s\n",i,h->stored_messages[i]);
		strncpy(messages[i], h->stored_messages[i], MESSAGE_SIZE);
	}
}


int giveMeTurnNum(HunterView h)
{
	return giveMeTurnNumber(h->view);
}







