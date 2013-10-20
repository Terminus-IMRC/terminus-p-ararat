/*
 * main/Terminus.c - main source code of Terminus project
 * Created in 20130111
 */

#include "chain.h"
#include "code.h"
#include "timing.h"
#include "parallel.h"
#include <signal.h>
#undef NDEBUG
#include <assert.h>

extern int tosend;
int commrank, commsize;
signed short int chaincont;

/* Only for making chain. */
enum trident prepcode[X][X];
struct ring chain[Ceilings];	/*TODO: will be formula line Ceilings-X*2*/
int tate[X], yoko[X];

/* Only for making ms. */
signed short int* tcode_as_1dim;
mpz_t eachtotal, total;
FILE *wholeCorrespondingTimeFp, *realCorrespondingTimeFp, *eachFollowTimeFp;
struct wtime_linear_list *wtime_for_whole_corresponding_list, *wtime_for_real_corresponding_list, *wtime_for_each_follow_list;
struct wtime_linear_list *wtime_for_whole_corresponding_list_def, *wtime_for_real_corresponding_list_def, *wtime_for_each_follow_list_def;
#ifdef PF
struct tcode_linear_list *proper_ms, *proper_ms_def;
FILE* myfp;
#endif

void caught_signal(const int);
void initialization_before_chain_main();
void initialization_before_follow();
void probe_len_and_gather_total();
void pfPrepcode();
void output_times(double start_wtime, double end_wtime);

int main(int argc, char* argv[])
{
	int i, j;
	unsigned char contflag;
	double start_wtime, end_wtime;
	#ifdef PF
	char filename[0xff];
	#endif

	MPI_Init(&argc, &argv);

	initialization_before_chain_main();

	chain_main();
	/* I want to distribute chain. */

	if(!commrank){
		dputs("Long overdue. This program will follow below steps.");
		printChain();
		dputs("\nThe structure is this.");
		/*TODO: Can't use pfCode because the argument type is different.*/
		pfPrepcode();
		printf("Chaincount:%d\n", chaincont);
	}

	initialization_before_follow();

	MPI_Barrier(MPI_COMM_WORLD);
	if(!commrank){
		start_wtime=MPI_Wtime();
		follow(0);
		contflag=0;	/*"Let's give up", she said me.*/
		i=commsize-1;
		while(i--){
			MPI_Recv(&j, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD,	\
				MPI_STATUS_IGNORE);
			MPI_Send(&contflag, 1, MPI_UNSIGNED_CHAR,	\
				j, 1, MPI_COMM_WORLD);
		}
	}else
		follow_pa(N-1);

	MPI_Barrier(MPI_COMM_WORLD);
	if(!commrank)
		end_wtime=MPI_Wtime();

	ppass();

	free(tcode_as_1dim);
	free(tcode);
	free(sum_tate);
	free(sum_yoko);
	free(sum_name);
	free(dned);

	#ifdef PF
	if(commrank){	/* Master is only to make candidates. */
		/* All of solved mses will be put into this file. */
		sprintf(filename, "out%d.txt", commrank);
		myfp=fopen(filename, "w");
		tcode_linear_list_output_from_orig(myfp, proper_ms_def);
		fclose(myfp);
		tcode_linear_list_free_from_orig(proper_ms_def);
	}
	#endif

	probe_len_and_gather_total();
	mpz_clear(eachtotal);

	if(!commrank){
		fputs("Total: ", stdout);
		mpz_out_str(stdout, BASE, total);
		putchar('\n');
		mpz_clear(total);
	}

	output_times(start_wtime, end_wtime);

	MPI_Finalize();

	return 0;
}
 
void initialization_before_chain_main()
{
	int i, j;

	assert(signal(SIGINT, caught_signal) != SIG_ERR);
	assert(signal(SIGHUP, caught_signal) != SIG_ERR);

	chaincont=0;

	/* These are used only in chain making. */
	for(i=0; i<X; i++){
		for(j=0; j<X; j++)
			prepcode[i][j]=Unknown;
		tate[i]=0;
		yoko[i]=0;
	}

	MPI_Comm_rank(MPI_COMM_WORLD, &commrank);
	MPI_Comm_size(MPI_COMM_WORLD, &commsize);
	if(!commrank)
		tosend=1;

	ppass();

	return;
}

void initialization_before_follow()
{
	int i;

	tcode=(signed short int**)malloc(sizeof(signed short int*)*X);
	assert(tcode);

	tcode_as_1dim=(signed short int*)malloc(sizeof(signed short int)*X*X);
	assert(tcode_as_1dim);

	sum_tate=(signed short int*)malloc(sizeof(signed short int)*X);
	assert(sum_tate);

	sum_yoko=(signed short int*)malloc(sizeof(signed short int)*X);
	assert(sum_yoko);

	sum_name=(signed short int*)malloc(sizeof(signed short int)*2);
	assert(sum_name);

	dned=(unsigned char*)malloc(sizeof(unsigned char)*Ceilings);
	assert(dned);

	#ifdef PF
	proper_ms=proper_ms_def=tcode_linear_list_get_new_entry();
	#endif

	wtime_for_whole_corresponding_list=wtime_for_whole_corresponding_list_def=wtime_linear_list_get_new_entry();
	wtime_for_real_corresponding_list=wtime_for_real_corresponding_list_def=wtime_linear_list_get_new_entry();
	wtime_for_each_follow_list=wtime_for_each_follow_list_def=wtime_linear_list_get_new_entry();

	mpz_init(eachtotal);

	/* Going to make 2-dimentional tcode. */
	for(i=0; i<X; i++)
		tcode[i]=tcode_as_1dim+i*X;

	/* These are used only in ms making. */
	for(i=0; i<Ceilings; i++){
		tcode_as_1dim[i]=0;
		dned[i]=False;
	}
	for(i=0; i<X; i++)
		sum_tate[i]=sum_yoko[i]=0;
	for(i=0; i<2; i++)
		sum_name[i]=0;

	if(!commrank)
		mpz_init(total);

	ppass();

	return;
}

void probe_len_and_gather_total()
{
	int i;
	int len;
	char *str, **allstr, *allstr_1dim;

	len=mpz_sizeinbase(eachtotal, BASE);
	MPI_Allreduce(&len, &i, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
	len=i+1;	/*core + '\0'*/
	if(!commrank)
		printf("len is %d.\n", len);
	str=(char*)malloc(len*sizeof(char));
	assert(str);
	if(!commrank){
		allstr=(char**)malloc(commsize*sizeof(char*));
		assert(allstr);
		allstr_1dim=(char*)malloc(commsize*len*sizeof(char));
		assert(allstr_1dim);
		for(i=0; i<commsize; i++)
			allstr[i]=allstr_1dim+i*len;
	}
	mpz_get_str(str, BASE, eachtotal);
	MPI_Gather(str, len, MPI_CHAR, allstr_1dim, len, MPI_CHAR, 0, MPI_COMM_WORLD);
	if(!commrank){
		mpz_set(total, eachtotal);
		for(i=1; i<commsize; i++){
			mpz_set_str(eachtotal, allstr[i], BASE);
			mpz_add(total, total, eachtotal);
		}
		free(allstr);
		free(allstr_1dim);
	}
	free(str);

	return;
}

void pfPrepcode()
{
	/*Note that prepcode is global variable.*/
	int i, j;

	/*Note that the argument type of pfCode was originaly enum trident.*/
	for(i=0; i<X; i++){
		for(j=0; j<X; j++){
			if(!prepcode[j][i])
				will_and_die("There still be Unknown in prepcode.",	\
								EXIT_FAILURE);
			printf("%c", prepcode[j][i]==1?'f':'a');
		}
		putchar('\n');
	}
}

void output_times(double start_wtime, double end_wtime)
{
	char filename[0xff];
	FILE* nfp;

	/***************
	 * X: X        *
	 * N: N        *
	 * R: commrank *
	 * S: commsize *
	 ***************/

	if(!commrank){
		/*resX-N-S.txt: final ms total*/
		sprintf(filename, "res%d-%d-%d.txt", X, N, commsize);
		nfp=fopen(filename, "w");
		mpz_out_str(nfp, BASE, total);
		fputc('\n', nfp);
		fclose(nfp);

		/*timX-N-S.txt: wall clock time of all ms processes between barriers of the top and bottom*/
		sprintf(filename, "tim%d-%d-%d.txt", X, N, commsize);
		nfp=fopen(filename, "w");
		fprintf(nfp, "%g\n", end_wtime-start_wtime);
		fclose(nfp);
	}else{
		/*eflX-N-S-R.txt: each follow time*/
		sprintf(filename, "efl%d-%d-%d.%d.txt", X, N, commsize, commrank);
		eachFollowTimeFp=fopen(filename, "w");
		wtime_linear_list_output_from_orig(eachFollowTimeFp, wtime_for_each_follow_list_def);
		fclose(eachFollowTimeFp);
	}

	/*RIP: ticX-N-S-R.txt: corresponding wall clock time*/
	/*RIP: tieX-N-S-R.txt: wall clock time of each follow*/

	/*wcrX-N-S-R.txt: each whole corresponding time*/
	sprintf(filename, "wcr%d-%d-%d.%d.txt", X, N, commsize, commrank);
	wholeCorrespondingTimeFp=fopen(filename, "w");
	wtime_linear_list_output_from_orig(wholeCorrespondingTimeFp, wtime_for_whole_corresponding_list_def);
	fclose(wholeCorrespondingTimeFp);

	/*rcrX-N-S-R.txt: each real corresponding time*/
	sprintf(filename, "rcr%d-%d-%d.%d.txt", X, N, commsize, commrank);
	realCorrespondingTimeFp=fopen(filename, "w");
	wtime_linear_list_output_from_orig(realCorrespondingTimeFp, wtime_for_real_corresponding_list_def);
	fclose(realCorrespondingTimeFp);

	return;
}
