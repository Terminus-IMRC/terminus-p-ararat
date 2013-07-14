#include "code.h"

signed short int find_next_j(signed short int* stat){
	dprintf("find_next_j: ");
	for(; *stat<Ceilings; ++*stat){
		dprintf("[%d]%d ", *stat, dned[*stat]);
		if(!dned[*stat]){
			dputchar('\n');
			return *stat;
		}
	}
	return Ceilings;
}
