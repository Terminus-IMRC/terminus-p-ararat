#include "def.h"
#include <stdlib.h>

void will_and_die(const char* str, const int exitno)
{
	fprintf(stderr, "Terminus said \"%s\" So exiting.\n", str);
	exit(exitno);
}
