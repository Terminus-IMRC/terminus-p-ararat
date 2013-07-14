#ifndef CODE_INSIDE
	#define CODE_INSIDE
	#include "def.h"
	#include "gmp.h"
	/*20130112*/
	extern void follow(const signed short int);
	extern signed short int find_next_j(signed short int*);

	/*20130113*/
	extern signed short int tcode[X][X];
	extern unsigned char dned[Ceilings];
	extern signed short int sum_tate[X], sum_yoko[X], sum_name[2];

	/*20130202*/
	/*extern int total;*/
	/*20130309*/
	extern mpz_t total, eachtotal;
	#define BASE 10
#endif
