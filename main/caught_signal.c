#include "code.h" /* for total */
#include "parallel.h" /* for commrank */
#include <signal.h>
void caught_signal(const int signo)
{
	fprintf(stderr, "Terminus(%d) caught a signal %d. Total(present): ", commrank, signo);
	mpz_out_str(stderr, BASE, total);
	fputc('\n', stderr);
	if(signo!=SIGHUP)
		will_and_die("Bismillah!", signo);
}
