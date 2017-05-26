/*
Author: Joshua Kluthe

Description: This program unit tests the function isGameOver() in dominion.c

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
    
    struct gameState *game = newGame();
	int i;

	printf("Testing function isGameOver().\n");

	//we only have to look at the supplyCount values for this function.

	//all supplies initialized negative
	for(i = curse; i <= treasure_map; i++)
		game->supplyCount[i] = -1;

    if(isGameOver(game) != 1)
        printf("PASS\n");
    else
        printf("FAIL\n");
	
	//all supplies initialized zero
	for(i = curse; i <= treasure_map; i++)
		game->supplyCount[i] = 0;

    if(isGameOver(game) == 1)
        printf("PASS\n");
    else
        printf("FAIL\n");

	//all supplies initialized positive
	for(i = curse; i <= treasure_map; i++)
		game->supplyCount[i] = 1;

    if(isGameOver(game) != 1)
        printf("PASS\n");
    else
        printf("FAIL\n");

	//provinces = 0
	game->supplyCount[province] = 0;
	if(isGameOver(game) == 1)
        printf("PASS\n");
    else
        printf("FAIL\n");

	//provinces = 1, estates adventurers and gardens = 0
	game->supplyCount[province] = 1;
	game->supplyCount[estate] = 0;
	game->supplyCount[adventurer] = 0;
	game->supplyCount[gardens] = 0;
	if(isGameOver(game) == 1)
        printf("PASS\n");
    else
        printf("FAIL\n");

	//gardens = 1
	game->supplyCount[gardens] = 1;
	if(isGameOver(game) != 1)
        printf("PASS\n");
    else
        printf("FAIL\n");

	printf("Testing function isGameOver() complete.\n");

    return 0;
}
