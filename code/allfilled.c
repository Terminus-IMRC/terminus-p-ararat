#include "chain.h"

_Bool allfilled(){
	int i;
	for(i=0; i<X; i++)
		if(tate[i]!=X || yoko[i]!=X)
			return False;
	return True;
}
