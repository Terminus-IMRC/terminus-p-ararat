#include "chain.h"

void addRestNameChain(const int l, const int m, const _Bool);

void chain_main()
{
	int i;
	chain_init(&chain[0]);

	addChainOrder(prepcode, 0, 0, True);
	addChainOrder(prepcode, X-1, 0, True);
	addChainOrder(prepcode, 0, X-1, True);
	addChainOrder(prepcode, X-1, X-1, True);

	for(i=1; i<X-1; i++){
		if(i==X-1-1)
			continue;
		addChainOrder(prepcode, i, i, True);
		if(!(X%2==1 && (X-1)/2==i))
			addChainOrder(prepcode, X-1-i, i, True);
	}

	chaincont--;

	/*RFC: it might be needed to write addChainOrder personaly.*/
	addRestNameChain(X-1-1, X-1-1, 0);
	addRestNameChain(1, X-1-1, 1);

#if 0
	prepcode[1][X-1-1]=AutoFilled;
	tate[1]++;
	yoko[X-1-1]++;
	chain[chaincont].toafill[chain[chaincont].toafillcont].x=1;
	chain[chaincont].toafill[chain[chaincont].toafillcont].y=X-1-1;
	for(i=0; i<X; i++){
		if((X-1-i)==1)	/*i.e. y==X-1-1*/
			continue;
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
#endif
	chaincont++;

	if(!allfilled()){
		dputs("All code aren't filled. Entering bruteforce mode.");
		bfcode(prepcode);
	}
}
