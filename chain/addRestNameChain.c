#include "chain.h"

void addRestNameChain(const int l, const int m, const _Bool isname1){
	int i, ti;	/*love and true love*/

	prepcode[l][m]=AutoFilled;
	tate[l]++;
	yoko[m]++;
	chain[chaincont].toafill[chain[chaincont].toafillcont].x=l;
	chain[chaincont].toafill[chain[chaincont].toafillcont].y=m;
	for(i=ti=0; i<X; i++){
		if(i==m)
			continue;
		if(isname1)
			chain[chaincont].toafillroad[chain[chaincont].	\
				toafillcont][ti].x=X-1-i;
		else
			chain[chaincont].toafillroad[chain[chaincont].	\
				toafillcont][ti].x=i;
		chain[chaincont].toafillroad[chain[chaincont].	\
			toafillcont][ti].y=i;

		ti++;
	}
	chain[chaincont].toafillcont++;

	addChainOrder(prepcode, l, m, False);

	return;
}

