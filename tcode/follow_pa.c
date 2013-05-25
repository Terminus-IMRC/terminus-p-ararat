#include "code.h"
#include "parallel.h"

int tosend;

void follow_pa(usetype m)
{
	int i;

	if(!commrank){
		for(i=0; i<X; i++)
			MPI_Send(tcode[i], X, MPI_SHORT, tosend,	\
				MPI_ANY_TAG, MPI_COMM_WORLD);
		MPI_Send(dned, Ceilings, MPI_UNSIGNED_CHAR, tosend,	\
			MPI_ANY_TAG, MPI_COMM_WORLD);
		MPI_Send(sum_tate, X, MPI_SHORT, tosend,	\
			MPI_ANY_TAG, MPI_COMM_WORLD);
		MPI_Send(sum_yoko, X, MPI_SHORT, tosend,	\
			MPI_ANY_TAG, MPI_COMM_WORLD);
		MPI_Send(sum_name, 2, MPI_SHORT, tosend,	\
			MPI_ANY_TAG, MPI_COMM_WORLD);
		tosend=(tosend+1)%commsize;
		if(!tosend)
			tosend++;
	}else{
		for(i=0; i<X; i++)
			MPI_Recv(&tcode[i], X, MPI_SHORT, 0,	\
				MPI_ANY_TAG, MPI_COMM_WORLD,	\
				MPI_STATUS_IGNORE);
		MPI_Recv(dned, Ceilings, MPI_UNSIGNED_CHAR, 0,	\
			MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(sum_tate, X, MPI_SHORT, 0, MPI_ANY_TAG,	\
			MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(sum_yoko, X, MPI_SHORT, 0, MPI_ANY_TAG,	\
			MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(sum_name, 2, MPI_SHORT, 0, MPI_ANY_TAG,	\
			MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		follow(m+1);
	}

	return;
}
