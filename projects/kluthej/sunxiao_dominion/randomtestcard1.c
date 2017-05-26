/*
Author: Joshua Kluthe

Description: This runs random tests on the adventurer card

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//for extra info on failures, #define NOISY 1
#define NOISY 1

struct gameState* random_game_state(int *player, int *handPos, int card);

int testCard(int handPos, struct gameState *G);

int numTreasureCards(const int *cards, int numCards);

int main() {

	int tests = 100000;
	int i, player, handPos;
	int card = adventurer;
	
	struct gameState *G;

	int fails = 0;

	srand(0);

	printf("Testing card Adventurer.\n");

	for(i = 0; i < tests; i++) {
		G = random_game_state(&player, &handPos, card);
		fails += testCard(handPos, G);
		free(G);
	}

	printf("Failed %d tests, passed %d tests.\n", fails, tests - fails);
	printf("Testing card Adventurer complete.\n\n");

	return 0;
}


//create a reandom valid game state
struct gameState* random_game_state(int *player, int *handPos, int card) {
	
	int i;

	//counter to make sure we don't have too many cards in play
	//minus 1 so player can have at least one card in hand
	int maxCards = MAX_DECK - 1;

	//valid random number of players (2 to 4)
	int numPlayers = (rand() % 2) + 2;

	//card set including card under test
	int cards[] = {adventurer, council_room, feast, gardens, mine,
				  remodel, smithy, village, baron, great_hall};
	
	//create and initialize game with a random seed
	struct gameState *G = newGame();
	initializeGame(numPlayers, cards, (rand() % 10000) + 1, G);

	//player is the player whose turn it is
	*player = whoseTurn(G);
	//randomize player deck/hand/discard
	G->deckCount[*player] = rand() % maxCards;
	maxCards -= G->deckCount[*player];
	for(i = 0; i < G->deckCount[*player]; i++)
		G->deck[*player][i] = cards[rand() % (treasure_map + 1)];

	G->discardCount[*player] = rand() % maxCards;
	maxCards -= G->discardCount[*player];
	for(i = 0; i < G->discardCount[*player]; i++)
		G->discard[*player][i] = cards[rand() % (treasure_map + 1)];

	G->handCount[*player] = (rand() % maxCards) + 1;
	for(i = 0; i < G->handCount[*player]; i++)
		G->hand[*player][i] = cards[rand() % (treasure_map + 1)];

	//choose a random hand position, set card in position to card
	*handPos = rand() % G->handCount[*player];
	G->hand[*player][*handPos] = card;

	return G;
}

//test playing the card. Return 1 on fail, else 0
int testCard(int handPos, struct gameState *G) {

	//malloc a new gameState instead of using a local variable so I don't have 
	//keep switching between -> and . notation
	struct gameState *testGame = newGame();
	
	int p = whoseTurn(G);

    int retval = 0;

	memcpy(testGame, G, sizeof(struct gameState));
	
	//int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
	if(playCard(handPos, 0, 0, 0, testGame) != 0)
		return 1;
	
	/*	
	printf("Gdeck: %d, Gdiscard: %d, TestDeck: %d, TestDiscard: %d\n",
		 numTreasureCards(G->deck[p], G->deckCount[p]),
		 numTreasureCards(G->discard[p], G->discardCount[p]),
		 numTreasureCards(testGame->deck[p], testGame->deckCount[p]),
		 numTreasureCards(testGame->discard[p], testGame->discardCount[p]));
	*/

	//check case that there are at least two treasures available to draw
	if(numTreasureCards(G->deck[p], G->deckCount[p]) + numTreasureCards(G->discard[p], G->discardCount[p]) > 1) {
		//check that player drew enough cards
		if(testGame->handCount[p] != G->handCount[p] + 1) {
			if(NOISY) {
				printf(">2 treasures, player didn't draw enough cards.\n");
			}
			retval = 1;
		}
		//check that player drew enough treasure		
		if(numTreasureCards(testGame->hand[p], testGame->handCount[p]) != numTreasureCards(G->hand[p], G->handCount[p]) + 2) {
			if(NOISY) {
				printf(">2 treasures, player didn't draw enough treasures.\n");
			}
			retval = 1;
		}
		//check that the treasures have been removed from the deck
		if(numTreasureCards(testGame->deck[p], testGame->deckCount[p]) + numTreasureCards(testGame->discard[p], testGame->discardCount[p])
			!= numTreasureCards(G->deck[p], G->deckCount[p]) + numTreasureCards(G->discard[p], G->discardCount[p]) - 2) {
			if(NOISY) {
				printf(">2 treasures, not enough removed from deck.\n");
			}
			retval = 1;
		}
	//check case only 1 treasure
	} else if(numTreasureCards(G->deck[p], G->deckCount[p]) + numTreasureCards(G->discard[p], G->discardCount[p]) > 0) {
		//check that player drew enough cards
		if(testGame->handCount[p] != G->handCount[p] + 0) {
			if(NOISY) {
				printf("1 treasure, player didn't draw enough cards.\n");
			}
			retval = 1;
		}
		//check that player drew enough treasure		
		if(numTreasureCards(testGame->hand[p], testGame->handCount[p]) != numTreasureCards(G->hand[p], G->handCount[p]) + 1) {
			if(NOISY) {
				printf("1 treasure, player didn't draw it.\n");
			}
			retval = 1;
		}
		//check that the treasures have been removed from the deck
		if(numTreasureCards(testGame->deck[p], testGame->deckCount[p]) + numTreasureCards(testGame->discard[p], testGame->discardCount[p])
			!= numTreasureCards(G->deck[p], G->deckCount[p]) + numTreasureCards(G->discard[p], G->discardCount[p]) - 1) {
			if(NOISY) {
				printf("1 treasure, not removed from deck.\n");
			}
			retval = 1;
		}
	//check case that there is no treasure to draw
	} else {
		//check that player drew enough cards
		if(testGame->handCount[p] != G->handCount[p] - 1) {
			if(NOISY) {
				printf("0 treasure, player didn't draw correct number cards.\n");
			}
			retval = 1;
		}
		//check that player drew enough treasure		
		if(numTreasureCards(testGame->hand[p], testGame->handCount[p]) != numTreasureCards(G->hand[p], G->handCount[p])) {
			if(NOISY) {
				printf("0 treasure, player didn't draw correct number of treasure.\n");
			}
			retval = 1;
		}
		//check that the treasures have been removed from the deck
		if(numTreasureCards(testGame->deck[p], testGame->deckCount[p]) + numTreasureCards(testGame->discard[p], testGame->discardCount[p])
			!= numTreasureCards(G->deck[p], G->deckCount[p]) + numTreasureCards(G->discard[p], G->discardCount[p])) {
			if(NOISY) {
				printf("0 treasure, incorrect number cards in deck.\n");
			}
			retval = 1;
		}
	}

	//check that actions decreased by 1
	if(testGame->numActions != G->numActions - 1) {
		if(NOISY) {
			printf("incorrect number of actions remaining.\n");
		}
		retval = 1;
	}

	free(testGame);

	return retval;
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



