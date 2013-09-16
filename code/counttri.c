#include "chain.h"

int counttri(enum trident code[X][X], const enum trident tri)
{
	int i, j, count=0;
	for(i=0; i<X; i++)
		for(j=0; j<X; j++)
			if(code[j][i]==tri)
				count++;
	return count;
}
