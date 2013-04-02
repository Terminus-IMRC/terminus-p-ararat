#include "code.h" /* for total */
void caught_signal(int signo)
{
	fprintf(stderr, "Terminus caught a signal %d.\nTotal(present): ", signo);
	mpz_out_str(stderr, BASE, total);
	fputc('\n', stderr);
	will_and_die("Bismillah!", signo);
}
