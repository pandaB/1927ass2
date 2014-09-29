// testGameView.c ... test the GameView ADT

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "GameView.h"

int main()
{
	int i;
	GameView gv;
	
	printf("Test basic empty initialisation\n");
	PlayerMessage messages1[] = {};
	gv = newGameView("", messages1);
	assert(getCurrentPlayer(gv) == PLAYER_LORD_GODALMING);
	assert(getRound(gv) == 0);
	assert(getHealth(gv,PLAYER_DR_SEWARD) == GAME_START_HUNTER_LIFE_POINTS);
	//printf("Lord G's health is %d\n", getHealth(gv,PLAYER_LORD_GODALMING));	
	//printf("Dracula's health is %d\n", getHealth(gv,PLAYER_DRACULA));
	assert(getHealth(gv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
	assert(getScore(gv) == GAME_START_SCORE);
	assert(getLocation(gv,PLAYER_LORD_GODALMING) == UNKNOWN_LOCATION);
	printf("passed_01\n");

	disposeGameView(gv);

	printf("Test for Dracula trail and basic functions\n");
	PlayerMessage messages2[] = {"Hello","Rubbish","Stuff","","Mwahahah"};
		printf("Check_101\n");
	gv = newGameView("GST.... SAO.... HZU.... MBB.... DC?....", messages2);
	printf("current turn is %d\n", getCurrentPlayer(gv));
	assert(getCurrentPlayer(gv) == PLAYER_LORD_GODALMING);
	printf("current round is %d\n", getRound(gv));
	assert(getRound(gv) == 1);
	assert(getLocation(gv,PLAYER_LORD_GODALMING) == STRASBOURG);
	assert(getLocation(gv,PLAYER_DR_SEWARD) == ATLANTIC_OCEAN);
	assert(getLocation(gv,PLAYER_VAN_HELSING) == ZURICH);
	assert(getLocation(gv,PLAYER_MINA_HARKER) == BAY_OF_BISCAY);
		printf("drac loc is %d\n", getLocation(gv,PLAYER_DRACULA));
	assert(getLocation(gv,PLAYER_DRACULA) == CITY_UNKNOWN);
	assert(getHealth(gv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
	printf("passed_02\n");
	disposeGameView(gv);

	printf("Test for encountering Dracula and hunter history\n");
	PlayerMessage messages3[] = {"Hello","Rubbish","Stuff","","Mwahahah","Aha!"};
	gv = newGameView("GST.... SAO.... HCD.... MAO.... DGE.... GGED...", messages3);
	printf("drac loc is %d\n", getLocation(gv,PLAYER_DRACULA));
	assert(getLocation(gv,PLAYER_DRACULA) == GENEVA);
	assert(getHealth(gv,PLAYER_LORD_GODALMING) == 5);
	assert(getHealth(gv,PLAYER_DRACULA) == 30);
	assert(getLocation(gv,PLAYER_LORD_GODALMING) == GENEVA);
	LocationID history[TRAIL_SIZE];
	getHistory(gv,PLAYER_DRACULA,history);
	assert(history[0] == GENEVA);
	assert(history[1] == UNKNOWN_LOCATION);
	getHistory(gv,PLAYER_LORD_GODALMING,history);
	assert(history[0] == GENEVA);
	assert(history[1] == STRASBOURG);
	assert(history[2] == UNKNOWN_LOCATION);
	getHistory(gv,PLAYER_DR_SEWARD,history);
	assert(history[0] == ATLANTIC_OCEAN);
	assert(history[1] == UNKNOWN_LOCATION);
	printf("passed\n");        
	disposeGameView(gv);

	printf("Test for Dracula doubling back at sea, and losing blood points (Hunter View)\n");
	PlayerMessage messages4[] = {"Hello","Rubbish","Stuff","","Mwahahah","Aha!","","","","Back I go"};
	gv = newGameView("GGE.... SGE.... HGE.... MGE.... DS?.... "
	                 "GST.... SST.... HST.... MST.... DD1....", messages4);
	printf("drac loc is %d\n", getLocation(gv,PLAYER_DRACULA));	
	assert(getLocation(gv,PLAYER_DRACULA) == DOUBLE_BACK_1);
	getHistory(gv,PLAYER_DRACULA,history);
	assert(history[0] == DOUBLE_BACK_1);
	assert(history[1] == SEA_UNKNOWN);
	printf("Dracula is on %d health\n",getHealth(gv,PLAYER_DRACULA));
	assert(getHealth(gv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS - 4);
	assert(getCurrentPlayer(gv) == 0);
	printf("passed\n");
	disposeGameView(gv);

	printf("Test for Dracula doubling back at sea, and losing blood points (Drac View)\n");
	PlayerMessage messages5[] = {"Hello","Rubbish","Stuff","","Mwahahah","Aha!","","","","Back I go"};
	gv = newGameView("GGE.... SGE.... HGE.... MGE.... DEC.... "
	                 "GST.... SST.... HST.... MST.... DD1....", messages5);
	assert(getLocation(gv,PLAYER_DRACULA) == DOUBLE_BACK_1);
	getHistory(gv,PLAYER_DRACULA,history);
	assert(history[0] == DOUBLE_BACK_1);
	assert(history[1] == ENGLISH_CHANNEL);
	assert(getHealth(gv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS - 4);
	assert(getCurrentPlayer(gv) == 0);
	printf("passed\n");
	disposeGameView(gv);

	printf("Test for connections\n");
	int size, seen[NUM_MAP_LOCATIONS], *edges;
	gv = newGameView("", messages1);    
	printf("Checking Galatz road connections\n");
	edges = connectedLocations(gv,&size,GALATZ,PLAYER_LORD_GODALMING,0,1,0,0);
	memset(seen, 0, NUM_MAP_LOCATIONS*sizeof(int));
	printf("size is %d\n",size);
	for (i = 0; i< size ; i++) seen[edges[i]] = TRUE;
	assert(size == 5); assert(seen[GALATZ]); assert(seen[CONSTANTA]);
	assert(seen[BUCHAREST]); assert(seen[KLAUSENBURG]); assert(seen[CASTLE_DRACULA]);
	free(edges);
	printf("Checking Ionian Sea sea connections\n");
	edges = connectedLocations(gv,&size,IONIAN_SEA,PLAYER_LORD_GODALMING,0,0,0,1);
	memset(seen, 0, NUM_MAP_LOCATIONS*sizeof(int));
	for (i = 0; i < size; i++) seen[edges[i]] = 1;
	assert(size == 7); assert(seen[IONIAN_SEA]); assert(seen[BLACK_SEA]);
	assert(seen[ADRIATIC_SEA]); assert(seen[TYRRHENIAN_SEA]);
	assert(seen[ATHENS]); assert(seen[VALONA]); assert(seen[SALONICA]);
	free(edges);
	printf("Checking Athens rail connections (none)\n");
	edges = connectedLocations(gv,&size,BUDAPEST,PLAYER_LORD_GODALMING,0,0,1,0);
	assert(size == 1);
	assert(edges[0] == BUDAPEST);
	free(edges);
	printf("Dr Seward\n");
	edges = connectedLocations(gv,&size,BUDAPEST,PLAYER_DR_SEWARD,0,0,1,0);
	assert(size == 3);
	//assert(edges[0] == BUDAPEST);
	
	free(edges);
	printf("Van Helsings\n");
	edges = connectedLocations(gv,&size,BUDAPEST,PLAYER_VAN_HELSING,0,0,1,0);
	assert(size == 5);
	printf("passed\n");
	printf("Mina\n");
	edges = connectedLocations(gv,&size,BUDAPEST,PLAYER_MINA_HARKER,0,0,1,0);
	assert(size == 5);
	printf("passed\n");	
	
	printf("Bernice is awesome\n");
	disposeGameView(gv);
	return 0;
}

