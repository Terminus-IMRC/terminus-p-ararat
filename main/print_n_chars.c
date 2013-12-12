#include "def.h"

void print_str_n_times(char *s, int n, FILE *fp)
{
	while(n-->0)
		fputs(s, fp);

	return;
}
