#include "chain.h"

void chain_main(){
	int i;
	chain_init(&chain[0]);

	for(i=0; i<X-1; i++){
		addChainOrder(prepcode, i, i, True);
		if(!(X%2==1 && (X-1)/2==i))
			addChainOrder(prepcode, X-1-i, i, True);
	}

	chaincont--;

	prepcode[0][X-1]=AutoFilled;
	tate[0]++;
	yoko[X-1]++;
	chain[chaincont].toafill[chain[chaincont].toafillcont].x=0;
	chain[chaincont].toafill[chain[chaincont].toafillcont].y=X-1;
	for(i=0; i<X-1; i++){
		chain[chaincont].toafillroad[chain[chaincont].	\
			toafillcont][i].x=X-1-i;
		chain[chaincont].toafillroad[chain[chaincont].	\
			toafillcont][i].y=i;
	}
	chain[chaincont].toafillcont++;

	prepcode[X-1][X-1]=AutoFilled;
	tate[X-1]++;
	yoko[X-1]++;
	chain[chaincont].toafill[chain[chaincont].toafillcont].x=X-1;
	chain[chaincont].toafill[chain[chaincont].toafillcont].y=X-1;
	for(i=0; i<X-1; i++){
		chain[chaincont].toafillroad[chain[chaincont].	\
			toafillcont][i].x=i;
		chain[chaincont].toafillroad[chain[chaincont].	\
			toafillcont][i].y=i;
	}
	chain[chaincont].toafillcont++;

	addChainOrder(prepcode, 0, X-1, False);
	addChainOrder(prepcode, X-1, X-1, False);

	chaincont++;

	if(!allfilled()){
		dputs("All code aren't filled. Entering bruteforce mode.");
		bfcode(prepcode);
	}
}
