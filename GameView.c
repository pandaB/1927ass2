// GameView.c ... GameView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Map.h"

#define PLAYERS 4
#define HEALTH 0

struct gameView {

	Graph *map;

	int turnNum;
	
	int playerStats[PLAYERS]  //TODO rename to health and do below
	
	Queue trails[5];

	int score;
};
	 

// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[])
{
	GameView g = malloc(sizeof(struct gameView));
	
	Graph map = newGraph(NUM_MAP_LOCATIONS);
	
	//make score
	g->score = GAME_START_SCORE;
	
	//initialises player and dracular health
	g->playerStats[0][HEALTH] = GAME_START_HUNTER_LIFE_POINTS;
	g->playerStats[1][HEALTH] = GAME_START_HUNTER_LIFE_POINTS;
	g->playerStats[2][HEALTH] = GAME_START_HUNTER_LIFE_POINTS;
	g->playerStats[3][HEALTH] = GAME_START_HUNTER_LIFE_POINTS;
	g->playerStats[4][HEALTH] = GAME_START_BLOOD_POINTS;
	

	int t_index;
	for (t_index = 0; t_index < 5, t_index++) {
		g->trails[t_index]
	}
	
	//go forward through past plays and make actions
	int curr = 0;
	while (pastPlays[curr] != NULL) {
		//determine which player
		PlayerID p;
		switch (i) {
			case 'G':
				p = PLAYER_LORD_GODALMING;
				break;
			case 'S':
				p = PLAYER_DR_SEWARD;	
				break;
			case 'H':
				p = PLAYER_VAN_HELSING;
				break;
			case 'M':
				p = PLAYER_MINA_HARKER;
				break;
			case 'D':
				p = PLAYER_DRACULA;
				break;
			default:
				exit 0;
		}
		
		//get location id from string from lab
		Location loc = placeToID(strcat(pastPlays[curr+1], pastPlays[curr+2]);  //TODO get pl
		
		//make trail
		//TODO include queues and change items and write queue length
		QueueJoin(g->trails[p],loc);
		if (QueueLen(g->trails[p]) > 6) {
			QueueLeave(g->trails[p]);
		}
		
		//make actions
		if (p==PLAYER_DRACULA) {
			for (int index = 3; index<7; index++) {
				makeActionDracula(g, p, pastPlays[curr+i], index)	//makes the action on the dracular	
			}
		} else {
			for (int index = 3; index<7; index++) {
				makeActionHunter(g, p, pastPlays[curr+i])				//makes the action on the player	
			}
		}
		
		if (p=='D') {
			g->score--;
		}
		
		curr += 8;
	}
	
	
		
	return g;
}

static void makeActionHunter(Gameview g, PlayerID p, char a) {

	int lifeLoss = 0;

	switch (a) {
		case '.':
			break;
		case 'T':
			lifeLoss = LIFE_LOSS_TRAP_ENCOUNTER;
			break;
		case 'V':

			break;
		case 'D':
			lifeLoss = LIFE_LOSS_DRACULA_ENCOUNTER;
			g->playerStats[PLAYER_DRACULA][HEALTH] -= LIFE_LOSS_HUNTER_ENCOUNTER;
	}

	g->playerStats[p][HEALTH] -= lifeLoss;
	
	if (g->playerStats[p][HEALTH] <= 0) {
		g->playerStats[p][HEALTH] = GAME_START_HUNTER_LIFE_POINTS;
		g->score -= 6;
	}
}
	
	
static void makeActionDracula(Gameview g, PlayerID p, char a, int index) {

	switch (a) {
		case '.':		//nothing happens
			break;
		case 'T':		//trap is made by game
			break;
		case 'M':		//trap is destroyed by game
			break;
		case 'V':		//immature vampire matures
			if (i == 5){
				g->score -= 13;
			}
			break;
	}
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
//first location is most recent
void getHistory(GameView currentView, PlayerID player,
	                        LocationID trail[TRAIL_SIZE])
{
	//takes queue from struct and implements it
	int location, reverse, buffer;
	for (location = 0; location < 6; ;location++){
		trail[location] = QueueLeave(g->trails[player]);
	}
	//reverses list to ensure the first element is the one visited most recently
	for (reverse = 0; reverse < 3; reverse++){
		buffer = trail[reverse];
		trail[reverse] = trail[6-reverse];
		trail[6-reverse] = buffer;
	}
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
