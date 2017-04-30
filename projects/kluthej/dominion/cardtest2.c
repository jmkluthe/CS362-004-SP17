/*
Author: Joshua Kluthe

Description: This program unit tests the card "adventurer" found in dominion.c

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

int numTreasureCards(const int *cards, int numCards);

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

	int testHand[MAX_HAND];
	
	int i, j, k;

	printf("Testing card Adventurer.\n");

    if(initializeGame(numPlayers, cards, seed, initGame) != 0)
		printf("Failed to initialize game.\n");
    
	testPlayer = whoseTurn(initGame);

	//replace one of the cards in current player's hand with adventurer
	initGame->hand[testPlayer][handPos] = adventurer;

	//copy game state to perform test
	memcpy(testGame, initGame, sizeof(struct gameState));

	//play adventurer
	if(playCard(handPos, 0, 0, 0, testGame) != 0)
		printf("Failed to play card with playCard().\n");;

	//testPlayer should now have previous hand size + 1 cards in hand
	if(VERBOSE) {
		printf("hand size: %d, expected: %d\n",testGame->handCount[testPlayer], initGame->handCount[testPlayer] + 1);
		for(i = 0; i < testGame->handCount[testPlayer]; i++)
			printf("testPlayer card %d: %d\n", i, testGame->hand[testPlayer][i]);
	}
	if(testGame->handCount[testPlayer] != initGame->handCount[testPlayer] + 1)
		printf("FAIL: hand size incorrect.\n");
	else
		printf("PASS: hand size correct.\n");
	
	//testPlayer should now have two more treasure cards in hand
	if(numTreasureCards(testGame->hand[testPlayer], testGame->handCount[testPlayer]) != numTreasureCards(initGame->hand[testPlayer], initGame->handCount[testPlayer]) + 2)
        printf("FAIL: player did not draw expected number of treasure cards.\n");
    else
		printf("PASS: player did draw expected number of treasure cards.\n");

	//playedCards should contain no treasure 
	if(numTreasureCards(testGame->playedCards, testGame->playedCardCount) != 0)
        printf("FAIL: player drew and discarded treasure cards.\n");
    else
		printf("PASS: player did not discard treasure cards.\n");

	//the sum of treasures in playedCards and deck should equal the number in 
	//initGame deck -2
	if(numTreasureCards(testGame->playedCards, testGame->playedCardCount) +
		numTreasureCards(testGame->deck[testPlayer], testGame->deckCount[testPlayer])
		!= numTreasureCards(initGame->deck[testPlayer], initGame->deckCount[testPlayer]) - 2)
        printf("FAIL: Expected number of treasures not moved from deck to hand.\n");
    else
		printf("PASS: Expected number of treasures moved from deck to hand.\n");
    
	printf("Testing card Adventurer complete.\n");

    return 0;
}

//returns the number of treasure cards in an array of cards
int numTreasureCards(const int *cards, int numCards) {
	
	int i;
	int tCards = 0;
	for(i = 0; i < numCards; i++) {
		if(cards[i] > province && cards[i] < adventurer)
			tCards++;
	}
	return tCards;
}
