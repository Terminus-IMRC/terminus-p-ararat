#include "chain.h"

/* NOTICE */
/* THIS FUNCTION DOES USE LOOP */
void bfcode(enum trident code[X][X])
{
	int i, j;
	for(i=0; i<X; i++)
		for(j=0; j<X; j++)
			if(code[j][i]==Unknown)
				addChainOrder(code, j, i, True);
	return;
}
