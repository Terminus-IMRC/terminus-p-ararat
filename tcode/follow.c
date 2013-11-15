/*
 * follow.c - make true code from code and chain.
 * Created in 20130112
 */
/* Anyway the wind blows */
#include "code.h"
#include "parallel.h"
#include "dned.h"

#define isitconsist(m) (((m>0)&&(m<=OneLine)) ? True:False)
#define isitpropernum(m) (((m>0) && (m<=Ceilings)) ? True:False)

signed short int** tcode;
struct dned_part *dned, *dned_global_def, *alllocal_dned;
signed short int *sum_tate, *sum_yoko, *sum_name;

#define if_name0(s) (s.x==s.y ? True:False)
#define if_name1(s) ((X-s.y-1)==s.x ? True:False)

short int follow_chain(int m);
int grope4initialValueOfLove(signed short int m);
void storetynd(signed short int local_tate[X], signed short int local_yoko[X], signed short int local_name[X], signed short int *local_maxValueInDned);
void restoretynd(signed short int local_tate[X], signed short int local_yoko[X], signed short int local_name[X], signed short int local_maxValueInDned);
void settcodeval(signed short int i, signed short int m);

void follow(const signed short int m)
{
	signed short int i=-1;
	signed short int local_tate[X], local_yoko[X], local_name[2], local_maxValueInDned;
	struct dned_part *dned_local_initial_locate=dned;
	struct dned_part *dned_local_significant_value, *dned_local_value_significant_def_locate;
	struct dned_part *dned_local=dned;

	dprintf("Entering #%d\n", m);

	if((!commrank) && (m==N-1)){
		dprintf("Now let master broadcast ms.\n");
		follow_pa(m);
		return;	/*Don't forget!!!*/
	}

	/*There used to be unfolded storetynd here.*/
	storetynd(local_tate, local_yoko, local_name, &local_maxValueInDned);

	i=grope4initialValueOfLove(m);
	if(i>maxValueInDned)
		return;
	else
		while(dned_local->num<i)
			dned_local=dned_local->next;

	dned_local_significant_value=alllocal_dned+m*Ceilings;
	dned_local_value_significant_def_locate=dned_local;
	dned_cp(dned_local_significant_value, dned_local_value_significant_def_locate);

	do{
		usedned_symbolic(dned_local);
		i=dned_local->num;
		dprintf("Trying to subst i(%d) to tcode[%d][%d]\n", i, chain[m].x, chain[m].y);
		tcode[chain[m].x][chain[m].y]=i;

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

		if(isitconsist(sum_tate[chain[m].x]) && isitconsist(sum_yoko[chain[m].y]) && ((if_name0(chain[m])) ? isitconsist(sum_name[0]):True) && ((if_name1(chain[m])) ? isitconsist(sum_name[1]):True)){
			if(m<chaincont-1)
				follow(m+1);
			else{
				dprintf("Max depth(m) reached.\n");
				#ifdef PF
				tcode_linear_list_subst(&proper_ms, tcode_as_1dim);
				#endif
				if(!commrank){
					dputs("root rearched max depth. Are you sure?");
				}
				mpz_add_ui(eachtotal, eachtotal, 1);
			}
		}else{
			dprintf("main tyn is not consist. So don't following.\n");
			dprintf("BTW t:%d y:%d n:%d,%d\n", sum_tate[chain[m].x], sum_yoko[chain[m].y], sum_name[0], sum_name[1]);
		}
		
ncot:
		/*There used to be unfolded restoretynd here.*/
		dprintf("Restoring\n");
		/*This also plays a part in unusedned_symbolic(dned_localdef);.*/
		restoretynd(local_tate, local_yoko, local_name, local_maxValueInDned);
		dned=dned_local_initial_locate;
		dned_cp(dned_local_value_significant_def_locate, dned_local_significant_value);
	}while((dned_local=dned_local->next));

	dned_cp(dned_local_value_significant_def_locate, dned_local_significant_value);
	dned=dned_local_initial_locate;

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
	struct dned_part *located;

	for(i=0; i<chain[m].toafillcont; i++){
		dprintf("Trying to chain[%d]'s toafill #%d[%d][%d].\n", m, i, chain[m].toafill[i][0], chain[m].toafill[i][0]);
		tobes=OneLine;
		for(j=0; j<X-1; j++){
			tobes-=
				tcode[chain[m].toafillroad[i][j].x][chain[m].toafillroad[i][j].y];
		}
		if(!isitpropernum(tobes)){
			dputs("Isn't proper. Continuing.");
			return 1;
		}
		located=dned_whereis_num(tobes, dned);
		if(!located){
			dprintf("TT: dned[tcode[%d][%d](%d)] is already in use.\n", chain[m].toafill[i][0], chain[m].toafill[i][1], tobes-1);
			return 1;
		}

#if 0
		if( ((chain[m].toafill[i].x==X-1) && (chain[m].toafill[i].y==X-1)) && (!(tobes>tcode[0][0])) )
			return 2;
		if( ((chain[m].toafill[i].x==0) && (chain[m].toafill[i].y==X-1)) && ((!(tobes>tcode[X-1][0])) ) )
			return 2;
#endif

		tcode[chain[m].toafill[i].x][chain[m].toafill[i].y]=tobes;
		usedned_symbolic(located);
		sum_tate[chain[m].toafill[i].x]+=tobes;
		sum_yoko[chain[m].toafill[i].y]+=tobes;
		if(if_name0(chain[m].toafill[i]))
			sum_name[0]+=tobes;
		if(if_name1(chain[m].toafill[i]))
			sum_name[1]+=tobes;

		if(!(isitconsist(sum_tate[chain[m].x]) && isitconsist(sum_yoko[chain[m].y]) && ((if_name0(chain[m].toafill[i])) ? isitconsist(sum_name[0]):True) && ((if_name1(chain[m].toafill[i])) ? isitconsist(sum_name[1]):True))	){
			dprintf("tate or yoko or name is not consist. Giving up.\n");
			return 1;
		}
	}
	return 0;
}

int grope4initialValueOfLove(signed short int m)
{
#if 1
	/*TODO: is it code[][]+1 or code[][]?*/

	if(((chain[m].x==X-1) && (chain[m].y==0)) || ((chain[m].x==X-1) && (chain[m].y==X-1)))
		return tcode[0][0];
	else if((chain[m].x==0) && (chain[m].y==X-1))
		return tcode[X-1][0];
	else if((chain[m].x==0) && (chain[m].y==0))
		return 1;/*Ceilings/2+1;*/
	else
		return 1;
#elif 0
	if(((chain[m].x==X-1) && (chain[m].y==0)) || ((chain[m].x==X-1) && (chain[m].y==X-1)))
		return tcode[0][0];
	else
		return 0;
#else
	return 0;
#endif
}

void storetynd(signed short int local_tate[X], signed short int local_yoko[X], signed short int local_name[X], signed short int *local_maxValueInDned)
{
	memcpy(local_tate, sum_tate, sizeof(local_tate[0])*X);
	memcpy(local_yoko, sum_yoko, sizeof(local_yoko[0])*X);
	memcpy(local_name, sum_name, sizeof(local_name[0])*2);
	*local_maxValueInDned=maxValueInDned;

	return;
}

void restoretynd(signed short int local_tate[X], signed short int local_yoko[X], signed short int local_name[X], signed short int local_maxValueInDned)
{
	memcpy(sum_tate, local_tate, sizeof(sum_tate[0])*X);
	memcpy(sum_yoko, local_yoko, sizeof(sum_yoko[0])*X);
	memcpy(sum_name, local_name, sizeof(sum_name[0])*2);
	maxValueInDned=local_maxValueInDned;

	return;
}

void settcodeval(signed short int i, signed short int m)
{
	sum_tate[chain[m].x]+=i;
	sum_yoko[chain[m].y]+=i;
	if(if_name0(chain[m]))
		sum_name[0]+=i;
	if(if_name1(chain[m]))
		sum_name[1]+=i;

	return;
}
