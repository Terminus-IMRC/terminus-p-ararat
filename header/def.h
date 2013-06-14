#ifndef DEF_INSIDE
	#define DEF_INSIDE

	/*#include"mpi.h"*/	/*IMRCの伝統的な神様*/
	#include <stdio.h>
	#include <stdint.h>

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

	typedef signed short usetype;

	enum trident{
		Unknown=0, Filled=1, AutoFilled=2
	};

	struct coord{
		usetype x;
		usetype y;
	};

	struct ring{
		usetype x, y;	/*code[x][y]*/
		usetype toafillcont;
		/*TODO: not needed to alloc so many*/
		struct coord toafill[Ceilings];
		/*TODO: not needed to alloc so many(maybe)*/
		struct coord toafillroad[Ceilings][X-1];
	};

	extern struct ring chain[Ceilings];
	extern usetype chaincont;
	extern void pfCode(usetype code[X][X]);
	extern void will_and_die(char*, int);
	#ifdef PF
	extern FILE* myfp;
	#endif
#endif
