#include "def.h"

#ifdef PF
#define FP myfp
#else
#define FP stdout
#endif

#if 0
/*When tcode is 1-dimentional array*/
void pfTcode(signed short int* code){
	int i;
	for(i=0; i<X*X; i++){
		fprintf(FP, "%2d ", code[i]);
		if(i%X==X-1)
			fputc('\n', FP);
	}
	return;
}
#else
void pfTcode(signed short int** code)
{
	int i, j;
	for(i=0; i<X; i++){
		for(j=0; j<X; j++)
			fprintf(FP, "%2d ", code[j][i]);
		fputc('\n', FP);
	}
	return;
}
#endif
