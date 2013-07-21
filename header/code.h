#ifndef CODE_INSIDE
	#define CODE_INSIDE
	#include "def.h"
	#include "gmp.h"
	/*20130112*/
	extern void follow(const signed short int);
	extern signed short int find_next_j(signed short int*);
	extern void pfTcode(signed short int*);

	/*20130113*/
	extern signed short int** tcode;
	extern signed short int* tcode_as_1dim;
	extern unsigned char* dned;
	extern signed short int *sum_tate, *sum_yoko, *sum_name;

	/*20130202*/
	/*extern int total;*/
	/*20130309*/
	extern mpz_t total, eachtotal;
	#define BASE 10
#endif
