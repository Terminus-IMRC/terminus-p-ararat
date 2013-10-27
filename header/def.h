#ifndef DEF_INSIDE
	#define DEF_INSIDE

	/*#include"mpi.h"*/	/*IMRCの伝統的な神様*/
	#include <stdio.h>
	#include <stdint.h>
	#include <string.h>

	#define FLUSH
	#define NODP
	#define NOPASS
	#include "debug.h"

	#ifndef X
		#error Define X in compile
	#endif

	#define Ceilings (X*X)
	#define OneLine (X*(Ceilings+1)/2)

	/*enum bool{
		False, True
	};*/
	#define False (0)
	#define True (!False)

	enum trident{
		Unknown=0, Filled=1, AutoFilled=2
	};

	struct coord{
		signed short int x;
		signed short int y;
	};

	struct ring{
		signed short int x, y;	/*code[x][y]*/
		signed short int toafillcont;
		/*TODO: not needed to alloc so many*/
		struct coord toafill[Ceilings];
		/*TODO: not needed to alloc so many(maybe)*/
		struct coord toafillroad[Ceilings][X-1];
	};

	extern struct ring chain[Ceilings];
	extern signed short int chaincont;
	extern void pfCode(signed short int code[X][X]);
	extern void will_and_die(const char*, const int);
#endif
