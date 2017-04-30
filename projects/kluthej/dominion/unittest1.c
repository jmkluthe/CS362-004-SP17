/*
Author: Joshua Kluthe

Description: unit test for the dominion.c function whoseTurn()

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// test whoseTurn
int main() {

    struct gameState *game = newGame();

    int testWhoseTurn = 0;

	printf("Testing function whoseTurn().\n");

    game->whoseTurn = testWhoseTurn;
    if(whoseTurn(game) == testWhoseTurn)
        printf("PASS\n");
    else
        printf("FAIL\n");
    
	testWhoseTurn = 1;
	game->whoseTurn = testWhoseTurn;    
    if(whoseTurn(game) == testWhoseTurn)
        printf("PASS\n");
    else
        printf("FAIL\n");

	testWhoseTurn = 3;
	game->whoseTurn = testWhoseTurn;    
    if(whoseTurn(game) == testWhoseTurn)
        printf("PASS\n");
    else
        printf("FAIL\n");

	testWhoseTurn = 4;
	game->whoseTurn = testWhoseTurn;    
    if(whoseTurn(game) == testWhoseTurn)
        printf("PASS\n");
    else
        printf("FAIL\n");

	testWhoseTurn = -1;
	game->whoseTurn = testWhoseTurn;    
    if(whoseTurn(game) == testWhoseTurn)
        printf("PASS\n");
    else
        printf("FAIL\n");

	printf("Testing function whoseTurn() complete.\n");

    return 0;
}



