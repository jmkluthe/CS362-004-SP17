/*
Author: Joshua Kluthe

Description: This program unit tests the function fullDeckCount() in dominion.c

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// test fullDeckCount
int main() {
    
    struct gameState *game = newGame();

	printf("Testing function fullDeckCount().\n");

	//game only needs one player for this test    
	game->numPlayers = 1;

/*
set up a deck/hand/discard set containing
curse: 4
estate: 3
duchy: 2
province: 0
copper: 3
silver: 2
gold: 2
adventurer: 3
council_room: 2
feast: 2
gardens: 4
mine: 3
remodel: 3
smithy: 0
village: 2
baron: 2
great_hall: 2
minion: 1
steward: 2
tribute: 3
ambassador: 2
cutpurse: 2
embargo: 3
outpost: 1
salvager: 2
sea_hag: 2
treasure_map: 3 
*/

	game->handCount[0] = 20;
	game->hand[0][0] = curse;
	game->hand[0][1] = curse;
	game->hand[0][2] = estate;
	game->hand[0][3] = duchy;
	game->hand[0][4] = silver;
	game->hand[0][5] = adventurer;
	game->hand[0][6] = council_room;
	game->hand[0][7] = council_room;
	game->hand[0][8] = feast;
	game->hand[0][9] = feast;
	game->hand[0][10] = gardens;
	game->hand[0][11] = gardens;
	game->hand[0][12] = gardens;
	game->hand[0][13] = gardens;
	game->hand[0][14] = mine;
	game->hand[0][15] = mine;
	game->hand[0][16] = mine;
	game->hand[0][17] = remodel;
	game->hand[0][18] = remodel;
	game->hand[0][19] = remodel;

	game->discardCount[0] = 20;
	game->discard[0][0] = curse;
	game->discard[0][1] = estate;
	game->discard[0][2] = copper;
	game->discard[0][3] = silver;
	game->discard[0][4] = gold;
	game->discard[0][5] = adventurer;
	game->discard[0][6] = village;
	game->discard[0][7] = village;
	game->discard[0][8] = baron;
	game->discard[0][9] = baron;
	game->discard[0][10] = great_hall;
	game->discard[0][11] = great_hall;
	game->discard[0][12] = minion;
	game->discard[0][13] = steward;
	game->discard[0][14] = steward;
	game->discard[0][15] = tribute;
	game->discard[0][16] = tribute;
	game->discard[0][17] = tribute;
	game->discard[0][18] = ambassador;
	game->discard[0][19] = ambassador;

	game->deckCount[0] = 20;
	game->deck[0][0] = curse;
	game->deck[0][1] = estate;
	game->deck[0][2] = duchy;
	game->deck[0][3] = copper;
	game->deck[0][4] = copper;
	game->deck[0][5] = gold;
	game->deck[0][6] = adventurer;
	game->deck[0][7] = cutpurse;
	game->deck[0][8] = cutpurse;
	game->deck[0][9] = embargo;
	game->deck[0][10] = embargo;
	game->deck[0][11] = embargo;
	game->deck[0][12] = outpost;
	game->deck[0][13] = salvager;
	game->deck[0][14] = salvager;
	game->deck[0][15] = sea_hag;
	game->deck[0][16] = sea_hag;
	game->deck[0][17] = treasure_map;
	game->deck[0][18] = treasure_map;
	game->deck[0][19] = treasure_map;
   
    if(fullDeckCount(0, curse, game) == 4)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, estate, game) == 3)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, duchy, game) == 2)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, province, game) == 0)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, copper, game) == 3)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, silver, game) == 2)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, gold, game) == 2)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, adventurer, game) == 3)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, council_room, game) == 2)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, feast, game) == 2)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, gardens, game) == 4)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, mine, game) == 3)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, remodel, game) == 3)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, smithy, game) == 0)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, village, game) == 2)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, baron, game) == 2)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, great_hall, game) == 2)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, minion, game) == 1)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, steward, game) == 2)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, tribute, game) == 3)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, ambassador, game) == 2)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, cutpurse, game) == 2)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, embargo, game) == 3)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, outpost, game) == 1)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, salvager, game) == 2)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, sea_hag, game) == 2)
        printf("PASS\n");
    else
        printf("FAIL\n");

    if(fullDeckCount(0, treasure_map, game) == 3)
        printf("PASS\n");
    else
        printf("FAIL\n");

	printf("Testing function fullDeckCount() complete.\n");

    return 0;
}


