/*
Author: Joshua Kluthe

Description: This runs random tests on the smithy card

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//define NOISY 1 to print extra details about failures
#define NOISY 0

struct gameState* random_game_state(int *player, int *handPos, int card);

int testCard(int handPos, struct gameState *G);

int main() {

	int tests = 100000;
	int i, player, handPos;
	int card = smithy;
	
	struct gameState *G;

	int fails = 0;

	srand(0);

	printf("Testing card Smithy.\n");

	for(i = 0; i < tests; i++) {
		G = random_game_state(&player, &handPos, card);
		fails += testCard(handPos, G);
		free(G);
	}

	printf("Failed %d tests, passed %d tests.\n", fails, tests - fails);
	printf("Testing card Smithy complete.\n\n");

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


int testCard(int handPos, struct gameState *G) {

	//malloc a new gameState instead of using a local variable so I don't have 
	//keep switching between -> and . notation
	struct gameState *testGame = newGame();

	int p = whoseTurn(G);

	memcpy(testGame, G, sizeof(struct gameState));

	//int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
	if(playCard(handPos, 0, 0, 0, testGame) != 0) {
		if(NOISY) {
			printf("playCard() failed.\n");
		}
		return 1;
	}

	//check case that deck + discard had 3 or more cards to draw
	if(G->deckCount[p] + G->discardCount[p] > 2) {
		//check that enough cards were drawn
		if(testGame->handCount[p] != G->handCount[p] + 2) {
			if(NOISY) {
				printf("3 cards to draw, did not draw 2\n");
			}
			return 1;
		}
		if(testGame->deckCount[p] + testGame->discardCount[p] != G->deckCount[p] + G->discardCount[p] - 3) {
			if(NOISY) {
				printf("3 cards to draw, 3 cards not removed from deck.\n");
			}
			return 1;
		}
	//check if deck + discard has 2 cards, so 2 cards should be drawn
	} else if(G->deckCount[p] + G->discardCount[p] == 2) {
		//check that enough cards were drawn
		if(testGame->handCount[p] != G->handCount[p] + 1) {
			if(NOISY) {
				printf("2 cards to draw, did not draw 2.\n");
			}
			return 1;
		}
		if(testGame->deckCount[p] + testGame->discardCount[p] != G->deckCount[p] + G->discardCount[p] - 2) {
			if(NOISY) {
				printf("2 cards to draw, 2 cards not removed from deck.\n");
			}
			return 1;
		}
	//check if deck + discard has 1 card, so 1 card should be drawn
	} else if(G->deckCount[p] + G->discardCount[p] == 1) {
		//check that enough cards were drawn
		if(testGame->handCount[p] != G->handCount[p]) {
			if(NOISY) {
				printf("1 card to draw, did not draw 1.\n");
			}
			return 1;
		}
		if(testGame->deckCount[p] + testGame->discardCount[p] != G->deckCount[p] + G->discardCount[p] - 1) {
			if(NOISY) {
				printf("1 card to draw, 1 card not removed from deck.\n");
			}
			return 1;
		}
	//else no cards should be drawn, hand should be 1 smaller
	} else {
		if(testGame->handCount[p] != G->handCount[p] - 1) {
			if(NOISY) {
				printf("0 cards to draw, did not draw 0.\n");
			}
			return 1;
		}
		if(testGame->deckCount[p] + testGame->discardCount[p] != G->deckCount[p] + G->discardCount[p]) {
			if(NOISY) {
				printf("0 cards to draw, 0 not removed from deck.\n");
			}
			return 1;
		}
	}

	free(testGame);

	return 0;
}


