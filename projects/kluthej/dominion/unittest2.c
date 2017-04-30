/*
Author: Joshua Kluthe

Description: unit test for the dominion.c function scoreFor()

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//set VERBOSE = 1 for extra print statements
#define VERBOSE 0

// test scoreFor
int main() {
    
    struct gameState *game = newGame();

	printf("Testing function scoreFor().\n");

	//game only needs one player for this test    
	game->numPlayers = 1;

	//set up empty deck/hand/discard
	game->handCount[0] = 0;
	game->discardCount[0] = 0;
	game->deckCount[0] = 0;

	if(VERBOSE)
		printf("score: %d, fulldeckcount: %d\n", scoreFor(0, game), fullDeckCount);
    if(scoreFor(0, game) == 0)
        printf("PASS\n");
    else
        printf("FAIL\n");

	//add cards with no value
	game->hand[0][0] = adventurer;
	game->discard[0][0] = smithy;
	game->deck[0][0] = minion;
	game->handCount[0]++;
	game->discardCount[0]++;
	game->deckCount[0]++;

	if(VERBOSE)
		printf("score: %d, fulldeckcount: %d\n", scoreFor(0, game), fullDeckCount);
    if(scoreFor(0, game) == 0)
        printf("PASS\n");
    else
        printf("FAIL\n");
	
	//prev val 0
	//add cards total value -1
	game->hand[0][1] = curse;
	game->discard[0][1] = curse;
	game->deck[0][1] = estate;
	game->handCount[0]++;
	game->discardCount[0]++;
	game->deckCount[0]++;

	if(VERBOSE)
		printf("score: %d, fulldeckcount: %d\n", scoreFor(0, game), fullDeckCount);
    if(scoreFor(0, game) == -1)
        printf("PASS\n");
    else
        printf("FAIL\n");

	//prev val -1
	//add cards total value 1
	game->hand[0][2] = curse;
	game->discard[0][2] = curse;
	game->deck[0][2] = duchy;
	game->handCount[0]++;
	game->discardCount[0]++;
	game->deckCount[0]++;

	if(VERBOSE)
		printf("score: %d, fulldeckcount: %d\n", scoreFor(0, game), fullDeckCount);
    if(scoreFor(0, game) == 0)
        printf("PASS\n");
    else
        printf("FAIL\n");

	//prev val 0
	//add cards total value 4 + gardens (12/10 = 1)
	game->hand[0][3] = estate;
	game->discard[0][3] = duchy;
	game->deck[0][3] = gardens;
	game->handCount[0]++;
	game->discardCount[0]++;
	game->deckCount[0]++;

	if(VERBOSE)
		printf("score: %d, fulldeckcount: %d\n", scoreFor(0, game), fullDeckCount);
    if(scoreFor(0, game) == 5)
        printf("PASS\n");
    else
        printf("FAIL\n");

	//prev val 4 + gardens (gardens = 15/10 = 1)
	//add cards total value 7
	game->hand[0][4] = village;
	game->discard[0][4] = province;
	game->deck[0][4] = great_hall;
	game->handCount[0]++;
	game->discardCount[0]++;
	game->deckCount[0]++;

	if(VERBOSE)
		printf("score: %d, fulldeckcount: %d\n", scoreFor(0, game), fullDeckCount);
    if(scoreFor(0, game) == 12)
        printf("PASS\n");
    else
        printf("FAIL\n");

	//prev val 11 + gardens (gardens = 18/10 = 1)
	//add cards total value 0 + gardens (18/10 = 1)
	game->hand[0][5] = curse;
	game->discard[0][5] = gardens;
	game->deck[0][5] = great_hall;
	game->handCount[0]++;
	game->discardCount[0]++;
	game->deckCount[0]++;

	if(VERBOSE)
		printf("score: %d, fulldeckcount: %d\n", scoreFor(0, game), fullDeckCount);
    if(scoreFor(0, game) == 13)
        printf("PASS\n");
    else
        printf("FAIL\n");

	//prev val 11 + 2*gardens (gardens = 21/10 = 2)
	//add cards total value 0
	game->hand[0][6] = adventurer;
	game->discard[0][6] = minion;
	game->deck[0][6] = embargo;
	game->handCount[0]++;
	game->discardCount[0]++;
	game->deckCount[0]++;

	if(VERBOSE)
		printf("score: %d, fulldeckcount: %d\n", scoreFor(0, game), fullDeckCount);
    if(scoreFor(0, game) == 15)
        printf("PASS\n");
    else
        printf("FAIL\n");

	printf("Testing function scoreFor() complete.\n");

    return 0;
}


