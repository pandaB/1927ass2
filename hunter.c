// hunter.c
// Implementation of your "Fury of Dracula" hunter AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "HunterView.h"
#include <time.h>
#include "IntList.h"

int makeRandomMove(HunterView g);
int getRank(HunterView h);
/*
Possible stategy:
	1) Place players scattered over the map, with Lord Goldamin in the middle of the map
	2) Players converge to Lord Goldaming (initial default Leader), do this for 6 turns
	3) Every 6 turns, all players rest a turn to reveal Dracula's 6th location of his trail
	4) Leader moves towards the revealed location, other players converge/follow the leader
	5) At any point in the game, if any hunter lands on Dracula's trail, make that hunter the new leader.
		5.1) Every player has a "Leader Value". The "Leader Value" is determined by 
			[(Dracula's trail location that hunter has landed on last)+num of turns passed after that] which needs to be reset when relevant
	
*/



void decideHunterMove(HunterView gameState)
{
	srand(time(NULL));
	// TODO ...
	// Replace the line below by something better
	//registerBestPlay("GE","I'm on holiday in Geneva");
	
	int move = makeRandomMove(gameState);
	//Our Message format: "<hunter's leader value>" //TODO change to convert loc id TODO authenticate with some cahracters
	char *moveTo = idToAbbrev(move);
	registerBestPlay(moveTo,"No Message Yet");
}

// generate a random move
int makeRandomMove(HunterView g)
{
	int *numLocations = NULL;
	int *locs = whereCanIgo(g,numLocations,TRUE,TRUE,FALSE);
	int selectRandIndex = (rand()%(*numLocations-1))+1; //so we don't select current loc (element 0)
	return locs[selectRandIndex];
}

//Leader AI
//if no mission yet, and not on rest; move to a place in which no other hunter is on
int makeLeaderMove (HunterView g)
{
	int move;
	//int curLeader = whoAmI(g);
	int flag1 = TRUE;
	int flag2;
	while(flag1) {
		flag2 = FALSE;
		int r_move = makeRandomMove(g);
		int i;
		for (i=0;i<NUM_PLAYERS-1;i++) {
			if (whereIs(g,i) == r_move) {
				flag2 = TRUE;
			}
		}
		if (flag2 == FALSE) {
			move = r_move;
			flag1 = FALSE;
		}
	}
	return move;
}



//Conga Line AI
//follow the Leader AI's trail - each minion is assigned a particular index Leader's trail
int makeFollowerMove (HunterView g)
{
	int move = 1;
	//int rank = getRank(g); //write this
	//int trail[TRAIL_SIZE];
	//#giveMeTheTrail(g,getLeader(),trail);//write this
	//move = djikstras(trail[rank]);
	
	return move;
}

int getRank(HunterView h)
{
	int turn = giveMeTurnNum(h);
	PlayerMessage messages[turn];
	getMessages(h,messages);
	
	int player = whoAmI(h);
	
	IntList l = newIntList();
	
	int tmp;
	int i;
	for (i=0;i<5;i++) {
		if (i!=player && i!=getLeader(h)) {
			sscanf(messages[turn-i],"%d",&tmp); //extract the turn number from the message TODO need help with maths
			IntListInsertInOrder(l,tmp,(5-player+id)%5);
		}
	}
	
	return playerPos(l,player);
}

// returns TRUE if all other hunters have rested in their last turn
// return PLAYER_LORD_GODALMING

int isLeaderRested (g)
{
	//int isAllRested = FALSE;
	//if (PLAYER_DR_SEWARD)
	
	return 0;
}
/*
giveMeTheTrail(HunterView currentView, PlayerID player,
							LocationID trail[TRAIL_SIZE])
							
*/				 
