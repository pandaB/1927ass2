// GameView.c ... GameView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Graph.h"

#define HEALTH 0

//====static functions====


struct gameView {

	Graph map;
	int turnNum;
	int health[NUM_PLAYERS];
	int trails[NUM_PLAYERS][TRAIL_SIZE];
	int score;
};


static void makeActionHunter(GameView g, PlayerID p, char a);
static void makeActionDracula(GameView g, PlayerID p, char a, int index);
static void addTrail(GameView g, PlayerID p, LocationID loc);
	
//===============================
//			Static Functions
//===============================



static void addTrail(GameView g, PlayerID p, LocationID loc)
{	
	int i;
	for (i = TRAIL_SIZE-2; i>=0; i--) {
		g->trails[p][i+1] = g->trails[p][i];
	}
	
	g->trails[p][0] = loc;
}

static void makeActionHunter(GameView g, PlayerID p, char a) {

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
			g->health[PLAYER_DRACULA] -= LIFE_LOSS_HUNTER_ENCOUNTER;
	}

	g->health[p] -= lifeLoss;
	
	if (g->health[p] <= 0) {
		g->health[p] = GAME_START_HUNTER_LIFE_POINTS;
		g->score -= 6;
	}
}
	
	
static void makeActionDracula(GameView g, PlayerID p, char a, int index) {

	switch (a) {
		case '.':		//nothing happens
			break;
		case 'T':		//trap is made by game
			break;
		case 'M':		//trap is destroyed by game
			break;
		case 'V':		//immature vampire matures
			if (index == 5){
				g->score -= 13;
			}
			break;
	}
}

void dracMove (char *abbrev, char *out)
{
	printf("evaluating dracs move: %s\n",abbrev);
	if (!strcmp("C?",abbrev)) {
		char num = CITY_UNKNOWN + '0';
		strcpy(out,&num);
	} else if (!strcmp("S?",abbrev)) {
		char num = SEA_UNKNOWN + '0';
		strcpy(out,SEA_UNKNOWN);
		g->health[PLAYER_DRACULA] -= 2;				
	}
	else if (!strcmp("HI",abbrev)) strcpy(out,HIDE);
	else if (abbrev[0] == 'D') {
		int backID =  abbrev[1] - '0';
		printf("doubling back to %c %d\n", abbrev[1],backID);
		strcpy(out,102+backID);
		printf("made it to here\n");
		if(!strcmp("S?",g->trails[PLAYER_DRACULA][backID]) g->health[PLAYER_DRACULA] -= 2;
	}
		
	else {
		LocationID loc = abbrevToID(abbrev);
		strcpy(out,loc);
		if(idToType(loc) == SEA) g->health[PLAYER_DRACULA] -= 2;
	}
}

/*
void dracMove (char *abbrev, char *out)
{
	printf("evaluating dracs move: %s\n",abbrev);
	if (!strcmp("C?",abbrev)) addTrail(g,p,CITY_UNKNOWN);
	else if (!strcmp("S?",abbrev)) {
		addTrail(g,p,SEA_UNKNOWN);
		g->health[PLAYER_DRACULA] -= 2;				
	}
	else if (!strcmp("HI",abbrev)) addTrail(g,p,HIDE);
	else if (abbrev[0] == 'D') {
		int backID =  abbrev[1] - '0';
		printf("doubling back to %c %d\n", abbrev[1],backID);
		addTrail(g,p,102+backID);
		printf("made it to here\n");
		if(!strcmp("S?",g->trails[PLAYER_DRACULA][backID]) g->health[PLAYER_DRACULA] -= 2;
	}
		
	else {
		LocationID loc = abbrevToID(abbrev);
		addTrail(g, p, loc);
		if(idToType(loc) == SEA) g->health[PLAYER_DRACULA] -= 2;
	}
}
*/

//===============================
//			Interface Functions
//===============================

// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[])
{
	GameView g = malloc(sizeof(struct gameView));
	
	g->map = newGraph(NUM_MAP_LOCATIONS);	
	addConnections(g->map);

	//printf("Game is at %p and map is at %p\n",g,g->map);
	
	//make score
	g->score = GAME_START_SCORE;
	
	//init turn number
	g->turnNum = 0;
	
	//initialises player and dracular health
	g->health[PLAYER_LORD_GODALMING] = GAME_START_HUNTER_LIFE_POINTS;
	g->health[PLAYER_DR_SEWARD] = GAME_START_HUNTER_LIFE_POINTS;
	g->health[PLAYER_VAN_HELSING] = GAME_START_HUNTER_LIFE_POINTS;
	g->health[PLAYER_MINA_HARKER] = GAME_START_HUNTER_LIFE_POINTS;
	g->health[PLAYER_DRACULA] = GAME_START_BLOOD_POINTS;
	
	int sl;
	for (sl = 0; sl < NUM_PLAYERS; sl++) {
		g->trails[sl][0] = UNKNOWN_LOCATION;
	}
	
	//go forward through past plays and make actions
	int curr = 0;
	while (pastPlays[curr] != '\0') {
		//printf("evaluating %c pos %d\n", pastPlays[curr], curr);
		//determine which player
		PlayerID p;
		switch (pastPlays[curr]) {
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
				goto EndWhile;
				fprintf(stderr, "An error occured: Player could not be recognised\n");
				exit(0);
		}
		
		//get location id from string from lab
		//using Places.c
		char abbrev[3];
		abbrev[0] = pastPlays[curr+1];
		abbrev[1] = pastPlays[curr+2];
		abbrev[2] = '\0';
		if (p == PLAYER_DRACULA) {
			char *out;
			LocationID loc = dracMove(abbrev,out);
			addTrail(g, p, loc);
		} else {
			LocationID loc = abbrevToID(abbrev);
			addTrail(g, p, loc);
		}
		//make actions
		int index;
		if (p == PLAYER_DRACULA) {
			for (index = 3; index<7; index++) {
				makeActionDracula(g, p, pastPlays[curr+index], index);	//makes the action on the dracular	
			}
		} else {
			for (index = 3; index<7; index++) {
				makeActionHunter(g, p, pastPlays[curr+index]);			//makes the action on the player	
			}
		}
		
		if (p==PLAYER_DRACULA) {
			g->score--;
				printf("drac ends turn at %d<============\n", getLocation(g,PLAYER_DRACULA));
		}
		
		curr += 8;
		g->turnNum++;
	}
	
	EndWhile: ;
	
	return g;
}


	

// Frees all memory previously allocated for the GameView toBeDeleted
void disposeGameView(GameView toBeDeleted)
{
	//printf("Game is at %p and map is at %p\n",toBeDeleted,toBeDeleted->map);
	dropGraph(toBeDeleted->map);
	free(toBeDeleted);
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round getRound(GameView currentView)
{
	return currentView->turnNum/5;
}

// Get the id of current player - ie whose turn is it?
PlayerID getCurrentPlayer(GameView currentView)
{
	return currentView->turnNum%5;
}

// Get the current score
int getScore(GameView currentView)
{
	return currentView->score;
}

// Get the current health points for a given player
int getHealth(GameView currentView, PlayerID player)
{
	return currentView->health[player];
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player)
{
	return currentView->trails[player][0];;
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
//first location is most recent
void getHistory(GameView currentView, PlayerID player,
	                        LocationID trail[TRAIL_SIZE])
{
	int i;
	for (i = 0; i<TRAIL_SIZE; i++) {
		trail[i] = currentView->trails[player][i];
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

//void main () {
//	printf("This is now working\n");
//}
