#ifndef CHAIN_INSIDE
	#define CHAIN_INSIDE
	#include "def.h"
	#include <stdlib.h>
	/*20130111*/
	extern enum trident prepcode[X][X];

	extern int tate[X], yoko[X];
	extern void addChainOrder(enum trident code[X][X],	\
						int x, int y, _Bool);
	extern int findFinalPlace(enum trident code[X][X], const _Bool, const int);
	extern void chain_init(struct ring*);
	extern void printChain();
	extern _Bool allfilled();
	extern void bfcode(enum trident code[X][X]);
	extern int counttri(enum trident code[X][X], const enum trident tri);
	
	/*20130205*/
	extern void chain_main();
#endif
