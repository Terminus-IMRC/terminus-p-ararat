#ifndef PARALLEL_INSIDE
#define PARALLEL_INSIDE

#include "def.h"
#include "mpi.h"

	#ifndef N
		#error Define N in compile.
	#endif

	extern int tosend;
	extern int commrank, commsize;

	void follow_pa(const signed short int m);
#endif
