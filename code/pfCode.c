#include "def.h"

void pfCode(int code[X][X]){
	int i, j;
	for(i=0; i<X; i++){
		for(j=0; j<X; j++)
			printf("%2d ", code[j][i]);
		putchar('\n');
	}
	return;
}
