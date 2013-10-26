#include "def.h"

#if 0
/*When tcode is 1-dimentional array*/
void pfTcode(signed short int* code)
{
	int i;
	for(i=0; i<X*X; i++){
		printf("%2d ", code[i]);
		if(i%X==X-1)
			putchar('\n');
	}
	return;
}
#else
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
#endif
