#include "chain.h"

int findFinalPlace(enum trident code[X][X], const _Bool tate_or_yoko, const int k){
	int i;
	for(i=0; i<X; i++)
		if(tate_or_yoko){	/*yoko*/
			if(code[i][k]==Unknown)
				return i;
		}else{
			if(code[k][i]==Unknown)
				return i;
		}
	printf("ERR %d%s\n", __LINE__, __FILE__);
	abort();
}
