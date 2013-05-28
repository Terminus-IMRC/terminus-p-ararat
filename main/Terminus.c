/*
 * main/Terminus.c - main source code of Terminus project
 * Created in 20130111
 */

#include "chain.h"
#include "code.h"
#include "parallel.h"
#include <signal.h>
#include <assert.h>

extern int tosend;
int commrank, commsize;

void caught_signal(int);

enum trident prepcode[X][X];
struct ring chain[Ceilings];	/*TODO: will be formula line Ceilings-X*2*/
int tate[X], yoko[X];
usetype chaincont;
mpz_t eachtotal, total;

int main(int argc, char* argv[]){
	int i, j;
	int len;
	int* recvcounts;
	unsigned char contflag;
	char *str, **allstr;

	assert(signal(SIGINT, caught_signal) != SIG_ERR);

	mpz_init(eachtotal);
	for(i=0; i<X;i++){
		for(j=0; j<X; j++){
			prepcode[i][j]=Unknown;
			tcode[i][j]=0;
		}
		tate[i]=0;
		yoko[i]=0;
	}
	chaincont=0;

	chain_main();

	/* Note that it is needed to broadcast chain */

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &commrank);
	MPI_Comm_size(MPI_COMM_WORLD, &commsize);

	if(!commrank){
		tosend=1;
		mpz_init(total);

		dputs("Long overdue. This program will follow below steps.");
		printChain();
		dputs("\nThe structure is this.");
		/*TODO: Can't use pfCode because the argument type is different.*/
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
		printf("Chaincount:%d\n", chaincont);
	}

	for(i=0; i<Ceilings; i++)
		dned[i]=False;
	for(i=0; i<X; i++)
		sum_tate[i]=sum_yoko[i]=0;
	for(i=0; i<2; i++)
		sum_name[i]=0;

	if(!commrank){
		follow(0);
		contflag=0;	/*"Let's give up", she said me.*/
		for(i=1; i<commsize; i++){
			MPI_Recv(&i, 1, MPI_INT, i, 2, MPI_COMM_WORLD,	\
				MPI_STATUS_IGNORE);
			MPI_Send(&contflag, 1, MPI_UNSIGNED_CHAR,	\
				i, 1, MPI_COMM_WORLD);
		}
	}else
		follow_pa(N-1);
	fprintf(stdout, "EachTotal(%d): ", commrank);
	mpz_out_str(stdout, BASE, eachtotal);
	putchar('\n');

	recvcounts=(int*)malloc(sizeof(int)*commsize);
	for(i=0; i<commsize; i++)
		recvcounts[i]=1;
	len=mpz_sizeinbase(eachtotal, BASE);
	MPI_Reduce_scatter(&i, &len, recvcounts, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
	len=i+1;
	if(!commrank)
		printf("len is %d.\n", len);
	str=(char*)malloc(sizeof(char)*(len+1));	/*len plus \0*/
	assert(str);
	if(!commrank){
		allstr=(char**)malloc(sizeof(char*)*commsize);
		assert(allstr);
		for(i=0; i<commsize; i++){
			allstr[i]=(char*)malloc(sizeof(char)*len);
			assert(allstr[i]);
		}
	}
	mpz_get_str(str, BASE, eachtotal);
	/*It can be bug. I do not know how to use this...
	MPI_Gather(str, len, MPI_INT, allstr, len, MPI_INT, 0, MPI_COMM_WORLD);*/
	if(!commrank){
		mpz_set(total, eachtotal);
		for(i=1; i<commsize; i++){
			MPI_Recv(str, len+1, MPI_CHAR, i, MPI_ANY_TAG,	\
				MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			mpz_set_str(eachtotal, str, BASE);
			mpz_add(total, total, eachtotal);
		}
		fputs("Total: ", stdout);
		mpz_out_str(stdout, BASE, total);
		putchar('\n');
		mpz_clear(total);
	}else
		MPI_Send(str, len+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	mpz_clear(eachtotal);

	MPI_Finalize();

	return 0;
}
 
