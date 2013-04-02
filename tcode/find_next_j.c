#include "code.h"

uint_fast8_t find_next_j(uint_fast8_t* stat){
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
