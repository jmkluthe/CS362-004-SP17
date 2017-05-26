//Random testing for adventurer
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "assert.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define total_loop 50
#define playernum 2

void randomTestingAdventurer(struct gameState *state, int *kingdomcard, int seed){
	int currentplayer;
	int beforedrawtreasure, afterdrawtreasure;
	int i,j;
	int card, hand_count, deck_count, discard_count, handPos;
	handPos = 0;

	for (i = 0; i < total_loop; i++)
	{
		state = newGame();
		initializeGame(playernum, kingdomcard, seed, state);
		currentplayer = state -> whoseTurn;
		beforedrawtreasure = 0;
		afterdrawtreasure = 0;
		hand_count = rand()% 10;
		state -> handCount[currentplayer] = hand_count;
		state -> hand[currentplayer][handPos] = adventurer;
		for(j=1; j<hand_count; j++){
			card = rand()%27;
			if(card == copper || card == silver || card == gold){
				beforedrawtreasure++;
			}
			state -> hand[currentplayer][j] = card;
		}
		deck_count = rand()%30;
		state -> deckCount[currentplayer] = deck_count;
		for(j=0; j<(deck_count-2);j++){
			card = rand()%27;
			state -> deck[currentplayer][j] = card;
		}
		discard_count = rand()%5;
		state -> discardCount[currentplayer] = discard_count;
		state -> discard[currentplayer][0] = copper;
		state -> discard[currentplayer][1] = copper;
		for(j=2; j<(discard_count - 1); j++){
			card = rand()%27;
			state -> discard[currentplayer][j] = card;
		}
		cardEffect_adventurer(currentplayer, state, 0, 0, 0);
		for(j=0; j<state -> handCount[currentplayer]; j++){
			if (state -> hand[currentplayer][j] == copper || state -> hand[currentplayer][j] == silver || state -> hand[currentplayer][j] == gold)
			{
				afterdrawtreasure++;
			}
		}

		if (afterdrawtreasure - beforedrawtreasure == 2){
			printf("Random Testing for adventurer: Success. Return correct number of treasure cards.\n");
		}else{
			printf("Random Testing for adventurer: Failed. Return wrong number of treasure cards.\n");
		}

		if(state -> handCount[currentplayer] == hand_count + 1){
			printf("Random Testing for adventurer: Success. Return correct number of hand count.\n");
		}else{
			printf("Random Testing for adventurer: Failed. Return wrong number of hand count.\n");
		}

		if(state -> playedCardCount == 1){
			printf("Random Testing for adventurer: Success. Return correct number of card played count.\n");
		}else{
			printf("Random Testing for adventurer: Failed. Return wrong number of card played count.\n");
		}
		free(state);
	}
}

int main(int argc, char const *argv[])
{
	struct gameState *randomTest;
	int kingdomCards[10] = {adventurer, minion, mine, cutpurse, sea_hag, tribute, smithy, gardens, embargo, village};
	int seed;
	time_t t;
	srand((unsigned) time(&t));
	if (argc == 2)
	{
		seed = atoi(argv[1]);
	}else{
		seed = rand()%10 + 1;
	}

	printf("Random Test for adventurer begins: \n");
	randomTestingAdventurer(randomTest, kingdomCards, seed);
	printf("Random Test for adventurer ends. \n");



	return 0;
}