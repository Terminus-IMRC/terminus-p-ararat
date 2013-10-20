#ifndef TIMING_INSIDE
	#define TIMING_INSIDE
	#include "def.h"
	struct wtime_linear_list{
		double wtime;
		struct wtime_linear_list* next;
	};

	struct wtime_linear_list* wtime_linear_list_get_new_entry();
	void wtime_linear_list_initialize(struct wtime_linear_list* s);
	void wtime_linear_list_subst(struct wtime_linear_list** dest, double localwtime);
	void wtime_linear_list_output(FILE* fp, struct wtime_linear_list* s);
	void wtime_linear_list_output_from_orig(FILE* fp, struct wtime_linear_list* orig);
	void wtime_linear_list_free_from_orig(struct wtime_linear_list* orig);
#endif
