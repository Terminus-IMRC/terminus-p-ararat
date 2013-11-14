#include "code.h"
#include "parallel.h"
#include "timing.h"

extern struct wtime_linear_list *wtime_for_whole_corresponding_list, *wtime_for_each_follow_list, *wtime_for_idle;
signed short int dned_tosend[Ceilings];

void follow_pa(const signed short int m)
{
	int tosend;
	int dned_len;
	unsigned char contflag;
	double start_tmp_wtime, end_tmp_wtime;
	double end_idle_wtime;

	if(!commrank){
		memset(dned_tosend, 0, sizeof(signed short int)*Ceilings);
		dned_len=dned_probe_length(dned);
		dned_num_serialize(dned_tosend, dned);

		start_tmp_wtime=MPI_Wtime();
		MPI_Recv(&tosend, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		end_idle_wtime=MPI_Wtime();

		contflag=1;
		MPI_Send(&contflag, 1, MPI_UNSIGNED_CHAR, tosend, 1, MPI_COMM_WORLD);

		MPI_Send(tcode_as_1dim, X*X, MPI_SHORT, tosend,	0, MPI_COMM_WORLD);
		MPI_Send(sum_tate, X, MPI_SHORT, tosend, 0, MPI_COMM_WORLD);
		MPI_Send(sum_yoko, X, MPI_SHORT, tosend, 0, MPI_COMM_WORLD);
		MPI_Send(sum_name, 2, MPI_SHORT, tosend, 0, MPI_COMM_WORLD);
		MPI_Send(&dned_len, 1, MPI_INT, tosend, 0, MPI_COMM_WORLD);
		if(dned_len)
			MPI_Send(dned_tosend, Ceilings, MPI_SHORT, tosend, 0, MPI_COMM_WORLD);
		end_tmp_wtime=MPI_Wtime();

		wtime_linear_list_subst(&wtime_for_whole_corresponding_list, end_tmp_wtime-start_tmp_wtime);
		wtime_linear_list_subst(&wtime_for_idle, end_idle_wtime-start_tmp_wtime);
	}else{
		for(;;){
			start_tmp_wtime=MPI_Wtime();
			MPI_Send(&commrank, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
			end_idle_wtime=MPI_Wtime();

			MPI_Recv(&contflag, 1, MPI_UNSIGNED_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if(!contflag)
				break;

			MPI_Recv(tcode_as_1dim, X*X, MPI_SHORT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(sum_tate, X, MPI_SHORT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(sum_yoko, X, MPI_SHORT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(sum_name, 2, MPI_SHORT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&dned_len, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if(dned_len)
				MPI_Recv(dned_tosend, Ceilings, MPI_SHORT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			end_tmp_wtime=MPI_Wtime();

			wtime_linear_list_subst(&wtime_for_whole_corresponding_list, end_tmp_wtime-start_tmp_wtime);
			wtime_linear_list_subst(&wtime_for_idle, end_idle_wtime-start_tmp_wtime);

			dned_subst_particular_value(dned_tosend, dned);

			start_tmp_wtime=MPI_Wtime();
			follow(m);
			end_tmp_wtime=MPI_Wtime();
			wtime_linear_list_subst(&wtime_for_each_follow_list, end_tmp_wtime-start_tmp_wtime);
		}
	}

	return;
}
