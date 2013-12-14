#define NDEBUG
#include <assert.h>
#include <stdlib.h>
#include "timing.h"

void wtime_linear_list_initialize(struct wtime_linear_list* s)
{
	s->next=NULL;
	return;
}

struct wtime_linear_list* wtime_linear_list_get_new_entry()
{
	struct wtime_linear_list* stl;

	stl=(struct wtime_linear_list*)malloc(sizeof(struct wtime_linear_list));
	assert(stl);
	wtime_linear_list_initialize(stl);

	return stl;
}

void wtime_linear_list_subst(struct wtime_linear_list** dest, double localwtime)
{
	(*dest)->wtime=localwtime;
	(*dest)->next=wtime_linear_list_get_new_entry();
	*dest=(*dest)->next;
	return;
}

void wtime_linear_list_output_from_orig(FILE* fp, struct wtime_linear_list* orig)
{
	while(orig->next){
		fprintf(fp, "%g\n", orig->wtime);
		orig=orig->next;
	}

	return;
}

void wtime_linear_list_free_from_orig(struct wtime_linear_list* orig)
{
	struct wtime_linear_list* next;

	while(orig){
		next=orig->next;
		free(orig);
		orig=next;
	}

	return;
}
