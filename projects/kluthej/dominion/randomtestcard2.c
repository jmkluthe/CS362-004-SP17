/*
Author: Joshua Kluthe

Description: This runs random tests on the baron card

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

int num_estates(int *cards, int numCards);

int main() {

	int tests = 100000;
	int i, player, handPos;
	int card = baron;
	
	struct gameState *G;

	int fails = 0;

	srand(0);

	printf("Testing card Baron.\n");

	for(i = 0; i < tests; i++) {
		G = random_game_state(&player, &handPos, card);
		fails += testCard(handPos, G);
		free(G);
	}

	printf("Failed %d tests, passed %d tests.\n", fails, tests - fails);
	printf("Testing card Baron complete.\n\n");

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

	int choice1 = 0;
	int choice2 = 0;

	memcpy(testGame, G, sizeof(struct gameState));

	//flip a coin for choice 1 or 2
	if(rand() % 2 == 1)
		choice2 = 1;
	else
		choice1 = 1;

	//int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
	if(playCard(handPos, choice1, choice2, 0, testGame) != 0) {
		return 1;
	}

	//check that numBuys increased
	if(testGame->numBuys != G->numBuys + 1) {
		if(NOISY) {
			printf("numbuys\n");
		}
		return 1;

	}

	//check that no cards where drawn from deck
	if(testGame->deckCount[p] != G->deckCount[p]) {
		if(NOISY) {
			printf("draw/discard\n");
		}
		return 1;
	}

	//check choice1 (discard estate, + 4 coin)
	if(choice1) {
		//check if player has no estate to discard
		if(num_estates(G->hand[p], G->handCount[p]) == 0) {
			//check if no estates are available
			if(supplyCount(estate, G) == 0) {
				//here the player can't discard or draw estate, so only change is handsize - 1
				if(testGame->handCount[p] != G->handCount[p] - 1) {
					if(NOISY) {
						printf("do nothing/handsize - 1\n");
					}
					return 1;
				}
			}
		//else, player can discard an estate
		} else {
			//hand should be -2
			if(testGame->handCount[p] != G->handCount[p] - 2) {
				if(NOISY) {
					printf("discard estate/handsize - 2\n");
					printf("prehand: %d posthand: %d\n", G->handCount[p], testGame->handCount[p]);
				}
				return 1;
			}
			//coin should be +4
			if(testGame->coins != G->coins + 4) {
				if(NOISY) {
					printf("coins + 4\n");
				}
				return 1;
			}
		}
	//check choice2 (draw an estate)
	} else {
		//check if no estates in supply
		if(supplyCount(estate, G) == 0) {
			//here the player can't draw estate, so only change is handsize - 1
			if(testGame->handCount[p] != G->handCount[p] - 1) 	{
				if(NOISY) {
					printf("handsize - 1 (do nothing)\n");
				}
				return 1;
			}
		} else {
			//hand size should be unchanged
			if(testGame->handCount[p] != G->handCount[p]) {
				if(NOISY) {
					printf("draw estate (handsize constant)\n");
				}
				return 1;
			}
			//estate supply should be -1
			if(supplyCount(estate, testGame) != supplyCount(estate, G) - 1) {
				if(NOISY) {
					printf("estate supply - 1\n");
					printf("pre: %d post: %d\n", supplyCount(estate, G), supplyCount(estate, testGame));
				}
				return 1;
			}
		}
	}

	free(testGame);

	return 0;
}

//looks through an array of cards and returns 1 if it find an estate, else 0
int num_estates(int *cards, int numCards) {

	int i;
	int numEstates = 0;

	for(i = 0; i < numCards; i++)
		if(cards[i] == estate)
			numEstates++;

	return numEstates;
}


