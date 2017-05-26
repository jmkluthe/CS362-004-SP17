/*
Author: Joshua Kluthe

Description: This program unit tests the card "Smithy" found in dominion.c

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//verbose = 1 for print statements
#define VERBOSE 0

int compare(const void* a, const void* b);

// test smithy
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

	printf("Testing card Smithy.\n");

    if(initializeGame(numPlayers, cards, seed, initGame) != 0)
		printf("Failed to initialize game.\n");

	testPlayer = whoseTurn(initGame);
	//replace one of the cards in current player's hand with smithy
	initGame->hand[testPlayer][handPos] = smithy;
	//copy game state to perform test
	memcpy(testGame, initGame, sizeof(struct gameState));
	//play smithy
	if(playCard(handPos, 0, 0, 0, testGame) != 0)
		printf("Failed to play card with playCard().\n");

	//test player should now have previous hand size + 2 cards in hand
	if(testGame->handCount[testPlayer] != initGame->handCount[testPlayer] + 2)
		printf("FAIL: hand size incorrect.\n");
	else
		printf("PASS: hand size correct.\n");

	//now we compare the deck count, discard count, and hand contents.
	//the ways we do this will depend on whether the discards had be to
	//shuffled into the deck or not, but since here we are only considering an
	//initial game state there will always be enough cards in the deck

	//first, build a temp array containing the cards we know should be in hand
	for(i = 1; i < initGame->handCount[testPlayer]; i++)
		testHand[i-1] = initGame->hand[testPlayer][i];

	//add the cards from the deck to the testHand
	k = initGame->deckCount[testPlayer];
	for(j = 0; j < 3; j++) {
		testHand[i-1] = initGame->deck[testPlayer][k - j - 1];
		i++;
	}
	
	if(VERBOSE)
		printf("i: %d, handcount: %d\n", i, testGame->handCount[testPlayer]);

	//compare the testGame hand to known testHand
	qsort((void*)(testHand), i-1, sizeof(int), compare);
    qsort((void*)(testGame->hand[testPlayer]), testGame->handCount[testPlayer], sizeof(int), compare);

	if(VERBOSE)
		for(j = 0; j < i-1; j++)
			printf("test: %d, game: %d\n", testHand[j], testGame->hand[testPlayer][j]);

	if(memcmp(testHand, testGame->hand[testPlayer], (i-1)*sizeof(int)) != 0)
	    printf("FAIL: Hand contains wrong cards.\n");
	else
		printf("PASS: Hand contains correct cards.\n");  

	//deckCount should be initGame->deckCount[testPlayer] - 3
	if(testGame->deckCount[testPlayer] != initGame->deckCount[testPlayer] - 3)
	    printf("FAIL: deck count is incorrect.\n");
	else
		printf("PASS: deck count is correct.\n");
	
	//playedCardCount should be +1
	if(VERBOSE)
		printf("testGame played: %d, expected: %d\n", testGame->playedCardCount, initGame->playedCardCount + 1);

	if(testGame->playedCardCount != initGame->playedCardCount + 1)
	    printf("FAIL: played card count is incorrect.\n");
	else
		printf("PASS: played card count is correct.\n");

	printf("Testing card Smithy complete.\n");

    return 0;
}


