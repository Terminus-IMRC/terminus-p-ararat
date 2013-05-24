#ifndef PARALLEL_INSIDE
#define PARALLEL_INSIDE

#include "def.h"
#include "mpi.h"

	extern int tosend;
	extern int commrank, commsize;

	void follow_pa(usetype m);
#endif
