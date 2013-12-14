#define NDEBUG
#include <assert.h>
#include <stdlib.h>
#include "code.h"

void tcode_linear_list_initialize(struct tcode_linear_list* s)
{
	s->next=NULL;
	return;
}

struct tcode_linear_list* tcode_linear_list_get_new_entry()
{
	struct tcode_linear_list* stl;

	stl=(struct tcode_linear_list*)malloc(sizeof(struct tcode_linear_list));
	assert(stl);
	tcode_linear_list_initialize(stl);

	return stl;
}

void tcode_linear_list_subst(struct tcode_linear_list** dest, signed short int* localtcode_as_1dim)
{
	tcode_linear_list_tcode_mv((*dest)->tcode_as_1dim, localtcode_as_1dim);
	(*dest)->next=tcode_linear_list_get_new_entry();
	*dest=(*dest)->next;
	return;
}

void tcode_linear_list_tcode_mv(signed short int dest[Ceilings], signed short int* source)
{
	int i;

	for(i=0; i<Ceilings; i++)
		dest[i]=source[i];

	return;
}

void tcode_linear_list_output(FILE* fp, struct tcode_linear_list* s)
{
	int i;

	for(i=0; i<Ceilings; i++)
		fprintf(fp, "%d ", s->tcode_as_1dim[i]);
	fputc('\n', fp);

	return;
}

void tcode_linear_list_output_from_orig(FILE* fp, struct tcode_linear_list* orig)
{
	while(orig->next){
		tcode_linear_list_output(fp, orig);
		orig=orig->next;
	}

	return;
}

void tcode_linear_list_free_from_orig(struct tcode_linear_list* orig)
{
	struct tcode_linear_list* next;

	while(orig){
		next=orig->next;
		free(orig);
		orig=next;
	}

	return;
}
