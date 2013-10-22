#include "chain.h"

void printChain()
{
	int i, j, k;
	for(i=0; i<chaincont; i++){
		printf("Chain%d:\t(%d, %d) toafill:%d", i, chain[i].x, chain[i].y, chain[i].toafillcont);
		putchar(' ');
		for(j=0; j<chain[i].toafillcont; j++){
			printf("(%d, %d)", chain[i].toafill[j].x, chain[i].toafill[j].y);
			for(k=0; k<X-1; k++)
				printf("[%d,%d]", chain[i].toafillroad[j][k].x, chain[i].toafillroad[j][k].y);
			printf(", ");
		}
		putchar('\n');
	}
	return;
}
