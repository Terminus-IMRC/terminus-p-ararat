#ifndef CODE_INSIDE
	#define CODE_INSIDE
	#include "def.h"
	#include "gmp.h"
	#include "dned.h"
	/*20130112*/
	extern void follow(const signed short int);
	extern signed short int find_next_j(signed short int*);
	extern void pfTcode_1dim(signed short int*);
	extern void pfTcode(signed short int**);

	/*20130113*/
	extern signed short int** tcode;
	extern signed short int* tcode_as_1dim;
	struct tcode_linear_list{
		signed short int tcode_as_1dim[Ceilings];
		struct tcode_linear_list* next;
	};
	extern struct tcode_linear_list *proper_ms;
	extern struct dned_part *dned;
	extern signed short int *sum_tate, *sum_yoko, *sum_name;

	struct tcode_linear_list* tcode_linear_list_get_new_entry();
	void tcode_linear_list_initialize(struct tcode_linear_list* s);
	void tcode_linear_list_tcode_mv(signed short int dest[Ceilings], signed short int* source);
	void tcode_linear_list_subst(struct tcode_linear_list** dest, signed short int* localtcode_as_1dim);
	void tcode_linear_list_output(FILE* fp, struct tcode_linear_list* s);
	void tcode_linear_list_output_from_orig(FILE* fp, struct tcode_linear_list* orig);
	void tcode_linear_list_free_from_orig(struct tcode_linear_list* orig);

	/*20130202*/
	/*extern int total;*/
	/*20130309*/
	extern mpz_t total, eachtotal;
	#define BASE 10
#endif
