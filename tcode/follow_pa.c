#include "code.h"
#include "parallel.h"

int tosend;

void follow_pa(usetype m)
{
	int i;

	if(!commrank){
		for(i=0; i<X; i++)
			MPI_Send(&tcode[i], X, MPI_INT, tosend,	\
				MPI_ANY_TAG, MPI_COMM_WORLD);
		tosend=(tosend+1)%commsize;
	}else{
		for(i=0; i<X; i++)
			MPI_Recv(&tcode[i], X, MPI_INT, 0, MPI_ANY_TAG,	\
				MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	return;
}
