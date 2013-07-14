/*
 * follow.c - make true code from code and chain.
 * Created in 20130112
 */
/* Anyway the wind blows */
#include "code.h"
#include "parallel.h"

#define isitconsist(m) (((m>0)&&(m<=OneLine)) ? True:False)
#define isitpropernum(m) (((m>0) && (m<=Ceilings)) ? True:False)

usetype tcode[X][X];
unsigned char dned[Ceilings];
usetype sum_tate[X], sum_yoko[X], sum_name[2];

#define if_name0(s) (s.x==s.y ? True:False)
#define if_name1(s) ((X-s.y-1)==s.x ? True:False)

short int follow_chain(int m);
int grope4initialValueOfLove(usetype m);
void storetynd(usetype local_tate[X], usetype local_yoko[X], usetype local_name[X], unsigned char local_dned[Ceilings]);
void restoretynd(usetype local_tate[X], usetype local_yoko[X], usetype local_name[X], unsigned char local_dned[Ceilings]);
void settcodeval(usetype i, usetype m);

void follow(const usetype m){
	usetype i=-1;
	usetype local_tate[X], local_yoko[X], local_name[2];
	unsigned char local_dned[Ceilings];

	dprintf("Entering #%d\n", m);

	if((!commrank) && (m==N-1)){
		dprintf("Now let master broadcast ms.\n");
		follow_pa(m);
		return;	/*Don't forget!!!*/
	}

	/*There used to be unfolded storetynd here.*/
	storetynd(local_tate, local_yoko, local_name, local_dned);

	i=grope4initialValueOfLove(m);

	while(find_next_j(&i)!=Ceilings){
		i++;
		dprintf("Trying to subst i(%d) to tcode[%d][%d]\n", i,	\
						chain[m].x, chain[m].y);
		if( ((chain[m].x==X-1) && (chain[m].y==0)) && !(tcode[0][0]<i) )
				continue;
		tcode[chain[m].x][chain[m].y]=i;
		dned[i-1]=True;

		/*There used to be unfolded settcodeval here.*/
		settcodeval(i, m);

		switch(follow_chain(m)){
			case 0:
				break;
			case 1:
				goto ncot;
				break;
			case 2:
				return;
				break;
			default:
				will_and_die("follow_chain did not returned 0, 1 or 2.", 1);
				break;
		}

		if(isitconsist(sum_tate[chain[m].x]) &&	\
			isitconsist(sum_yoko[chain[m].y]) &&	\
			((if_name0(chain[m])) ? isitconsist(sum_name[0]):True) &&	\
			((if_name1(chain[m])) ? isitconsist(sum_name[1]):True)){
			if(m<chaincont-1)
				follow(m+1);
			else{
				dprintf("Max depth(m) reached.\n");
				#ifdef PF
				pfCode(tcode);
				fputs("------------\n", myfp);
				#endif
				if(!commrank){
					dputs("root rearched max depth. Are you sure?");
				}
				mpz_add_ui(eachtotal, eachtotal, 1);
			}
		}else{
			dprintf("main tyn is not consist. So don't following.\n");
			dprintf("BTW t:%d y:%d n:%d,%d\n", sum_tate[chain[m].x],	\
					sum_yoko[chain[m].y], sum_name[0],	\
					sum_name[1]);
		}
		
ncot:
		/*There used to be unfolded restoretynd here.*/
		dprintf("Restoring\n");
		restoretynd(local_tate, local_yoko, local_name, local_dned);
	}
	dprintf("Leaving from #%d\n", m);
	return;
}

short int follow_chain(int m)
{
	/*return value
	  0: go ahead
	  1: to goto ncot
	  2: to return
	 */

	int i, j, tobes;

	for(i=0; i<chain[m].toafillcont; i++){
		dprintf("Trying to chain[%d]'s toafill #%d[%d][%d].\n", m, i,	\
			chain[m].toafill[i][0], chain[m].toafill[i][0]);
		tobes=OneLine;
		for(j=0; j<X-1; j++){
			tobes-=
				tcode[	\
				chain[m].toafillroad[i][j].x	]	\
				[chain[m].toafillroad[i][j].y	];
		}
		if(!isitpropernum(tobes)){
			dputs("Isn't proper. Continuing.");
			return 1;
		}
		if(dned[tobes-1]){
			dprintf("TT: dned[tcode[%d][%d](%d)] is already in use.\n",	\
				chain[m].toafill[i][0],	\
				chain[m].toafill[i][1],	\
				tobes-1);
			return 1;
		}

#if 0
		if( ((chain[m].toafill[i].x==X-1) && (chain[m].toafill[i].y==X-1)) && (!(tobes>tcode[0][0])) )
			return 2;
		if( ((chain[m].toafill[i].x==0) && (chain[m].toafill[i].y==X-1)) &&	\
				 ((!(tobes>tcode[X-1][0])) ) )
			return 2;
#endif

		tcode[chain[m].toafill[i].x][chain[m].toafill[i].y]=tobes;
		dned[tobes-1]=True;
		sum_tate[chain[m].toafill[i].x]+=tobes;
		sum_yoko[chain[m].toafill[i].y]+=tobes;
		if(if_name0(chain[m].toafill[i]))
			sum_name[0]+=tobes;
		if(if_name1(chain[m].toafill[i]))
			sum_name[1]+=tobes;

		if(!(isitconsist(sum_tate[chain[m].x]) &&	\
			 isitconsist(sum_yoko[chain[m].y]) &&	\
			 ((if_name0(chain[m].toafill[i])) ? isitconsist(sum_name[0]):True) &&	\
			 ((if_name1(chain[m].toafill[i])) ? isitconsist(sum_name[1]):True))	){
			dprintf("tate or yoko or name is not consist. Giving up.\n");
			return 1;
		}
	}
	return 0;
}

int grope4initialValueOfLove(usetype m)
{
#if 1
	/*TODO: is it code[][]+1 or code[][]?*/

	if(((chain[m].x==X-1) && (chain[m].y==0)) ||	\
		((chain[m].x==X-1) && (chain[m].y==X-1)))
		return tcode[0][0];
	else if((chain[m].x==0) && (chain[m].y==X-1))
		return tcode[X-1][0];
	else if((chain[m].x==0) && (chain[m].y==0))
		return 0;/*Ceilings/2+1;*/
	else
		return 0;
#elif 0
	if(((chain[m].x==X-1) && (chain[m].y==0)) ||	\
		((chain[m].x==X-1) && (chain[m].y==X-1)))
		return tcode[0][0];
	else
		return 0;
#else
	return 0;
#endif
}

void storetynd(usetype local_tate[X], usetype local_yoko[X], usetype local_name[X], unsigned char local_dned[Ceilings])
{
	int j;

	for(j=0; j<X; j++){
		local_tate[j]=sum_tate[j];
		local_yoko[j]=sum_yoko[j];
	}
	for(j=0; j<2; j++)
		local_name[j]=sum_name[j];
	for(j=0; j<Ceilings; j++)
		local_dned[j]=dned[j];

	return;
}

void restoretynd(usetype local_tate[X], usetype local_yoko[X], usetype local_name[X], unsigned char local_dned[Ceilings])
{
	int j;

	for(j=0; j<X; j++){
		sum_tate[j]=local_tate[j];
		sum_yoko[j]=local_yoko[j];
	}
	for(j=0; j<2; j++)
		sum_name[j]=local_name[j];
	for(j=0; j<Ceilings; j++)
		dned[j]=local_dned[j];

	return;
}

void settcodeval(usetype i, usetype m)
{
	sum_tate[chain[m].x]+=i;
	sum_yoko[chain[m].y]+=i;
	if(if_name0(chain[m]))
		sum_name[0]+=i;
	if(if_name1(chain[m]))
		sum_name[1]+=i;

	return;
}
