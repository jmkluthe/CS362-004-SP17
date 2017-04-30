/*
Author: Joshua Kluthe

My fuzzing process is fairly straightforward. For the c character, I just 
produced a random integer from 0 to 96, and then added 32 to it. Casting 
this to char produces an ASCII character from the ' ' character to the '~' 
character, which will at some point hit the values needed.

For the string, I created a five char c-string and filled it with random 
chars between 'a' and 'z'. I again produced the random chars by getting a random 
int from 0 to 25, then adding in this case 97. After enough iterations, this 
string will end up being 'r' 'e' 's' 'e' 't' '\0'.

How many iterations? Theoretically, it must first pass nine stages, and at each
stage it has a 1 in 96 chance, and then getting the exact string "reset" has 
the probability of 26*26*26*26*26. Adding these together we get a the value

theoretical iterations = 9*96 + 26^5 = 11882240

I decided to test the theory, so I ran the testme 10 times and got the values 
shown in iterations in the program below. I then ran the program to get the 
average, which is:

average iterations = 10050083.2

This is not too far off from the theory, so that makes me happy.

*/

#include <stdio.h>

int main() {

	int sum = 0;
	int i;
	int iterations[10];
	iterations[0] = 11534717;
	iterations[1] = 14967179;
	iterations[2] = 2922656;
	iterations[3] = 7127919;
	iterations[4] = 9301731;
	iterations[5] = 11676917;
	iterations[6] = 23539104;
	iterations[7] = 7044126;
	iterations[8] = 851769;
	iterations[9] = 11534717;

	for(i = 0; i < 10; i++)
		sum += iterations[i];

	printf("%f\n", ((float) sum) / 10.0);

	return 0;
}


