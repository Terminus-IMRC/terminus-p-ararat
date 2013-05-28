#include "def.h"

void pfCode(usetype code[X][X]){
	int i, j;
	for(i=0; i<X; i++){
		for(j=0; j<X; j++)
			fprintf(myfp, "%2d ", code[j][i]);
		fputc('\n', myfp);
	}
	return;
}
