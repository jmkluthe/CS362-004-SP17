/*
Author: Joshua Kluthe

Description: This program unit tests the card "village" found in dominion.c

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//set VERBOSE = 1 for extra print statements
#define VERBOSE 0

int main() {
    
	//initial game state to test card on    
    struct gameState *initGame = newGame();

	//game state after card is played
    struct gameState *testGame = newGame();

	int numPlayers = 2;

	int seed = 5000;
    
    int *cards = kingdomCards(adventurer, council_room, feast, gardens, mine,
                    remodel, smithy, village, baron, great_hall);

	int testPlayer;
	
	int handPos = 0;

	int i;

	printf("Testing card Village.\n");

    if(initializeGame(numPlayers, cards, seed, initGame) != 0)
		printf("Failed to initialize game.\n");
    
	testPlayer = whoseTurn(initGame);
	//replace one of the cards in current player's hand with village
	initGame->hand[testPlayer][handPos] = village;
	//copy game state to perform test
	memcpy(testGame, initGame, sizeof(struct gameState));
	//play village
	if(playCard(handPos, 0, 0, 0, testGame) != 0)
		printf("Failed to play card with playCard().\n");;

	//testPlayer drew and discarded a card, so should have same hand size
	if(VERBOSE) {
		printf("hand size: %d, expected: %d\n",testGame->handCount[testPlayer], initGame->handCount[testPlayer]);
		for(i = 0; i < testGame->handCount[testPlayer]; i++)
			printf("testPlayer card %d: %d\n", i, testGame->hand[testPlayer][i]);
	}
	if(testGame->handCount[testPlayer] != initGame->handCount[testPlayer])
		printf("FAIL: hand size incorrect.\n");
	else
		printf("PASS: hand size correct.\n");

	//testPlayer should now have +1 actions (1 spent, 2 gained)
	if(testGame->numActions != initGame->numActions + 1)
        printf("FAIL: actions not updated correctly.\n");
    else
		printf("PASS: actions updated correctly.\n");

	//playedCards should contain only 1 card
	if(testGame->playedCardCount != 1)
        printf("FAIL: playedCardCount not the expected value.\n");
    else
		printf("PASS: playedCardCount not the expected value.\n");

	//the played card should be village
	if(testGame->playedCards[0] != village)
        printf("FAIL: card played is not village.\n");
    else
		printf("PASS: card played is village.\n");
    
	printf("Testing card Village complete.\n");

    return 0;
}
