/*




*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


/*
struct gameState {
  int numPlayers; //number of players
  int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
  int embargoTokens[treasure_map+1];
  int outpostPlayed;
  int outpostTurn;
  int whoseTurn;
  int phase;
  int numActions;
  int coins;
  int numBuys;
  int hand[MAX_PLAYERS][MAX_HAND];
  int handCount[MAX_PLAYERS];
  int deck[MAX_PLAYERS][MAX_DECK];
  int deckCount[MAX_PLAYERS];
  int discard[MAX_PLAYERS][MAX_DECK];
  int discardCount[MAX_PLAYERS];
  int playedCards[MAX_DECK];
  int playedCardCount;
};
*/

// test numHandCards
int main() {
    
    struct gameState *game = (struct gameState *)malloc(sizeof(struct gameState));
    int testWhoseTurn = 1;
    
    
    game->numPlayers = 2;
    game->whoseTurn = testWhoseTurn;
    
    if(whoseTurn(game) == testWhoseTurn)
        printf("PASS\n");
    else
        printf("FAIL\n");
    
    return 0;
}



