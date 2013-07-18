#include "def.h"

#ifdef PF
#define FP myfp
#else
#define FP stdout
#endif

void pfTcode(signed short int* code){
	int i;
	for(i=0; i<X*X; i++){
		fprintf(FP, "%2d ", code[i]);
		if(i%X==X-1)
			fputc('\n', FP);
	}
	return;
}
