#include "def.h"

void will_and_die(char* str, int exitno)
{
	fprintf(stderr, "Terminus said \"%s\" So exiting.\n", str);
	exit(exitno);
}
