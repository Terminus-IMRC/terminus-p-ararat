#include "code.h"

usetype find_next_j(usetype* stat){
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
