#include "def.h"

void pfCode(usetype code[X][X]){
	#ifdef PF
	int i, j;
	for(i=0; i<X; i++){
		for(j=0; j<X; j++)
			fprintf(FP, "%2d ", code[j][i]);
		fputc('\n', PF);
	}
	#endif
	return;
}
