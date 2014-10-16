// hunter.c
// Implementation of your "Fury of Dracula" hunter AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "HunterView.h"
#include <time.h>
#include "IntList.h"

int makeRandomMove(HunterView g);
int makeLeaderMove (HunterView g);
int makeFollowerMove (HunterView g, int rank);
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

//static int current_leader = 0;

void decideHunterMove(HunterView gameState)
{
	srand(time(NULL));
	
	/*
	int rank = getRank(gameState);
	if (rank == 0) {
		makeLeaderMove(gameState);
	} else {
		makeFollowerMove(gameState,rank);
	}
	*/
	
	int move = makeRandomMove(gameState);
	//Our Message format: "<hunter's leader value>" // TODO work out message format
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

/*
//Leader AI
//if no mission yet, and not on rest; move to a place in which no other hunter is on
//followers will follow ala conga line
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
int makeFollowerMove (HunterView g, int rank)
{
	if (isLeaderRested) {
		return //TODO get current location...
	} else {
		int trail[TRAIL_SIZE];
		giveMeTheTrail(g,current_leader,trail);//write this
		//int path[70];
		//djikstras(trail[rank], path);
		//return path[0];
		return trail[rank];	//TODO this does not work. Need to work out djikstras to GET to this point...
	}
}

int getRank(HunterView h)
{
	int turn = giveMeTurnNum(h);
	PlayerMessage messages[turn];
	getMessages(h,messages);
	
	int player = whoAmI(h);
	int playertmp = player+4;
	IntList l = newIntList();
	
	int tmp;
	int i;
	for (i=0;i<5;i++) {
		if (i!=player) { //skips drac
			sscanf(messages[turn-i],"%d",&tmp); //extract the turn number from the message TODO need help with maths
			IntListInsertInOrder(l,tmp,playertmp%4);
			playertmp--;
		}
	}
	
	current_leader = getFirstPlayer(l);
	
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

giveMeTheTrail(HunterView currentView, PlayerID player,
							LocationID trail[TRAIL_SIZE])
							
*/				 



//-===================================================-//

/*
// EXPLODE TACIC
// returns next possible move that's furthest from all players
// determination (ranking) of the location is from
// the summation of  distance from all other players to that possible location
static LocationID bestExplodeMove (HunterView g) 
{
   PlayerID currPlayer = WhoAmI(g);

   int *numLocations;
   LocationID *possibleMove = whereCanIGo(g, numLocations, 1, 1, 1 );
   //initially set to player's current location
   LocationID furthestMove = possibleMove[0];
   int maxDist = 0;

   int i;
   for (i=0; i<numLocations; i++) {
      LocationID moveOption = possibleMove[i];
      int sumDist = 0;
      PlayerID p;
      for (p=0; p<(NUM_PLAYERS-1); p++) {
         if (p!=currPlayer) {
            sumDist += findPathDist(g, moveOption, whereIs(g, p) );
         }
      }
   }

   if (sumDist > maxDist) {
      furthestMove = moveOption;
   }

   return furthestMove;
}


//returns the playerID of the player whose position is closest to CASTLE_DRACULA
static PlayerID whoIsClosestToCastle (HunterView g) 
{
   PlayerID closestPlayer = 0;
   int minDist = findPathDist(g, whereIs(g,closestPlayer) );

   PlayerID p;
   for (p=1; p<(NUM_PLAYERS-1); p++) {
      int distToCast = findPathDist(g, whereIs(g,p) );
      if (distToCast < minDist) {
         closestPlayer = p;
      }
   }

   return closestPlayer;
}


//returns the next possible move closest to CASTLE_DRACULA
static LocationID bestMoveToCast (HunterView g, PlayerID player)
{
   int *numLocations;
   LocationID *possibleMove = whereCanTheyGo(g, numLocations, player, 1, 1, 1);

   LocationID closestToCast = possibleMove[0];
   int minDistToCast = findPathDist(g, closestToCast, CASTLE_DRACULA);

   int i;
   for (i=1; i<numLocations; i++) {
      LocationID checkMove = possibleMove[i];
      int distToCast = findPathDist(g, checkMove, CASTLE_DRACULA);

      if (distToCast < minDistToCast) {
         closestToCast = checkMove;
      }
   }

   return closestToCast;
}


////
//main function to decide player's next best move//
static LocationID bestLeaderMove (HunterView g) 
{
   PlayerID currPlayer = WhoAmI(g);

   LocationID nextBestMove;
   //if player happens to be closest to CASTLE_DRACULA, move closer
   if (whoIsClosestToCastle(g) == currPlayer) {
      nextBestMove = bestMoveToCast(g, currPlayer);
   }
   //else move to location furthest to every other player
   //aka: EXPLODE TACTIC
   else {
      nextBestMove = bestExplodeMove(g);
   }

   return nextBestMove;
}


*/




