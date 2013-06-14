#include "def.h"

#ifdef PF
#define FP myfp
#else
#define FP stdout
#endif

void pfCode(usetype code[X][X]){
	int i, j;
	for(i=0; i<X; i++){
		for(j=0; j<X; j++)
			fprintf(FP, "%2d ", code[j][i]);
		fputc('\n', FP);
	}
	return;
}
