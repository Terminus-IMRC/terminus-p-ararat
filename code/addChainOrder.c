#include "chain.h"

void addChainOrder(enum trident code[X][X], const int x, const int y, const _Bool do_chain)
{
	/*TODO: code may be prepcode*/
	int i, j, k;
	if(do_chain){
		code[x][y]=Filled;
		chain[chaincont].x=x;
		chain[chaincont].y=y;
		tate[x]++;
		yoko[y]++;
	}
	if(yoko[y]==X-1){
		i=findFinalPlace(code, True, y);
		code[i][y]=AutoFilled;
		chain[chaincont].toafill[chain[chaincont].toafillcont].x=i;
		chain[chaincont].toafill[chain[chaincont].toafillcont].y=y;
		for(j=k=0; j<X; j++){
			if(j==i)
				continue;
			chain[chaincont].toafillroad[chain[chaincont].toafillcont][k].x=j;
			chain[chaincont].toafillroad[chain[chaincont].toafillcont][k].y=y;
			k++;
		}
		chain[chaincont].toafillcont++;
		tate[i]++;
		yoko[y]++;
		/*TODO: don't need to check yoko in this case!*/
		addChainOrder(code, i, y, False);
	}
	if(tate[x]==X-1){
		i=findFinalPlace(code, False, x);
		code[x][i]=AutoFilled;
		chain[chaincont].toafill[chain[chaincont].toafillcont].x=x;
		chain[chaincont].toafill[chain[chaincont].toafillcont].y=i;
		for(j=k=0; j<X; j++){
			if(j==i)
				continue;
			chain[chaincont].toafillroad[chain[chaincont].toafillcont][k].x=x;
			chain[chaincont].toafillroad[chain[chaincont].toafillcont][k].y=j;
			k++;
		}
		chain[chaincont].toafillcont++;
		tate[x]++;
		yoko[i]++;
		/*TODO: don't need to check tate in this case!*/
		addChainOrder(code, x, i, False);
	}
	if(do_chain){
		chaincont++;
		chain_init(chain+chaincont);
	}
	return;
}
