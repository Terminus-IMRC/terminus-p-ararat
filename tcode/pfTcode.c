#include "def.h"

void pfTcode_1dim(signed short int* code)
{
	int i;
	for(i=0; i<X*X; i++){
		printf("%2d ", code[i]);
		if(i%X==X-1)
			putchar('\n');
	}
	return;
}

void pfTcode(signed short int** code)
{
	int i, j;
	for(i=0; i<X; i++){
		for(j=0; j<X; j++)
			printf("%2d ", code[j][i]);
		putchar('\n');
	}
	return;
}
