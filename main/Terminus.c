/*
 * main/Terminus.c - main source code of Terminus project
 * Created in 20130111
 */

#include "chain.h"
#include "code.h"
#include <signal.h>
#include <assert.h>

extern int tosend;

void caught_signal(int);

enum trident prepcode[X][X];
struct ring chain[Ceilings];	/*TODO: will be formula line Ceilings-X*2*/
int tate[X], yoko[X];
usetype chaincont;
mpz_t total;

int main(){
	int i, j;

	assert(signal(SIGINT, caught_signal) != SIG_ERR);

	mpz_init(total);
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

	/* TODO: broadcast chain */

	tosend=1l

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
	for(i=0; i<Ceilings; i++)
		dned[i]=False;
	for(i=0; i<X; i++)
		sum_tate[i]=sum_yoko[i]=0;
	for(i=0; i<2; i++)
		sum_name[i]=0;

	follow(0);
	fputs("Total: ", stdout);
	mpz_out_str(stdout, BASE, total);
	putchar('\n');
	mpz_clear(total);

	return 0;
}
 
