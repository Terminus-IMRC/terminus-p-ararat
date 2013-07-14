#include "code.h"
#include "parallel.h"

int tosend;

void follow_pa(const signed short int m)
{
	unsigned char contflag;

	if(!commrank){
		MPI_Recv(&tosend, 1, MPI_INT, MPI_ANY_SOURCE, 2,	\
			MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		contflag=1;
		MPI_Send(&contflag, 1, MPI_UNSIGNED_CHAR, tosend,	\
			1, MPI_COMM_WORLD);
		MPI_Send(tcode, X*X, MPI_SHORT, tosend,	\
			0, MPI_COMM_WORLD);
		MPI_Send(dned, Ceilings, MPI_UNSIGNED_CHAR, tosend,	\
			0, MPI_COMM_WORLD);
		MPI_Send(sum_tate, X, MPI_SHORT, tosend,	\
			0, MPI_COMM_WORLD);
		MPI_Send(sum_yoko, X, MPI_SHORT, tosend,	\
			0, MPI_COMM_WORLD);
		MPI_Send(sum_name, 2, MPI_SHORT, tosend,	\
			0, MPI_COMM_WORLD);
		tosend=(tosend+1)%commsize;
		if(!tosend)
			tosend++;
	}else{
		for(;;){
			MPI_Send(&commrank, 1, MPI_INT, 0, 2,	\
				MPI_COMM_WORLD);
			MPI_Recv(&contflag, 1, MPI_UNSIGNED_CHAR, 0,	\
				1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if(!contflag)
				break;
			MPI_Recv(tcode, X*X, MPI_SHORT, 0,	\
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
			follow(m);
		}
	}

	return;
}
