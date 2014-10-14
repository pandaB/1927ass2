// HunterView.c ... HunterView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "HunterView.h"


// #include "Map.h" ... if you decide to use the Map ADT
     
struct hunterView {
    GameView view;
    // int health[NUM_PLAYERS]; // can use getHealth() from GameView
    //int trails[NUM_PLAYERS][TRAIL_SIZE];

};
     

// Creates a new HunterView to summarise the current state of the game
HunterView newHunterView(char *pastPlays, PlayerMessage messages[])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    HunterView hunterView = malloc(sizeof(struct hunterView));
    assert(hunterView!=NULL);
    hunterView->view = newGameView(pastPlays, messages);
    /*
    int p;
    for (p=0; p<NUM_PLAYERS; p++) {
        getHistory(hunterView->view, p, hunterView->trails[p]);
    }
    */
    return hunterView;
}
     
     
// Frees all memory previously allocated for the HunterView toBeDeleted
void disposeHunterView(HunterView toBeDeleted)
{
    disposeGameView(toBeDeleted->view);
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
    //printf("%d\n", getCurrentPlayer(currentView->view));
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
/*
    if (player==PLAYER_DRACULA) {
        int revealDracLoc = 0;
        if ( playerLoc==CASTLE_DRACULA ) {
            // hunters will know when Dracula is at CASTLE_DRACULA
            revealDracLoc=1;
        } else if ( (!isSea(playerLoc)) && (getLocation(currentView->view, PLAYER_LORD_GODALMING)==playerLoc || getLocation(currentView->view, PLAYER_DR_SEWARD)==playerLoc || getLocation(currentView->view, PLAYER_VAN_HELSING)==playerLoc || getLocation(currentView->view, PLAYER_MINA_HARKER)==playerLoc ) ) {
            // if a hunter lands where Dracula is and is not at sea
            revealDracLoc = 1;
        }
                printf ("revealDracLoc is %d\n", revealDracLoc);
        if (revealDracLoc==0) {
                printf("HIIIIIII\n" );
                printf("typeOf(playerLoc) is %d\n", typeOf(playerLoc));
            if ( isLand(playerLoc) ) {
                playerLoc = CITY_UNKNOWN;
            } else if ( isSea(playerLoc) ) {
                playerLoc = SEA_UNKNOWN;
            } else {
                playerLoc = UNKNOWN_LOCATION;
            }
        }

    }
       printf("plauerLoc is %d", playerLoc);
       */
    return playerLoc;
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(HunterView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    assert (player<NUM_PLAYERS);
    getHistory(currentView->view, player, trail);
    //if player passed in is Dracula, need to omitt information!
    /*
    if (player==PLAYER_DRACULA) {
        //if a hunter is on the same city as Dracula, his current location is revealed
        trail[0] = whereIs(currentView, PLAYER_DRACULA);
        // Hunters only get approximate information about where Dracula has been
        //   (e.g. SEA_UNKNOWN) unless Dracula is in Castle Dracula or has been encountered
        int i;
        for (i=1; i<TRAIL_SIZE; i++) {
            if ( trail[i]==CASTLE_DRACULA ) continue;

            if ( isLand(trail[i]) ) {
                trail[i] = CITY_UNKNOWN;
            } else if ( isSea(trail[i]) ) {
                trail[i] = SEA_UNKNOWN;
            }

        }
    }
    */
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
    //LocationID playerLoc = whereIs(currentView, player);
    // If the given player is Dracula, sets numLocations to 0, unless you
    //   know Dracula's location precisely
/*    
    if (player == PLAYER_DRACULA &&
        (playerLoc==CITY_UNKNOWN || playerLoc==SEA_UNKNOWN || playerLoc==UNKNOWN_LOCATION ) ) {
        numLocations = 0;
        edges = connectedLocations(currentView->view, numLocations, getLocation(currentView->view, PLAYER_DRACULA), PLAYER_DRACULA, getRound(currentView->view), road, 0, sea);
    
    } else {
        edges = connectedLocations(currentView->view, numLocations, getLocation(currentView->view, player), player, getRound(currentView->view), road, rail, sea);
    }
*/    
    edges = connectedLocations(currentView->view, numLocations, getLocation(currentView->view, player), player, getRound(currentView->view), road, rail, sea);
    return edges;
}












