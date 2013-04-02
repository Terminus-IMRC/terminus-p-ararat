/*
 * follow.c - make true code from code and chain.
 * Created in 20130112
 */
/* Anyway the wind blows */
#include "code.h"

#define isitconsist(m) (((m>0)&&(m<=OneLine)) ? True:False)
#define isitpropernum(m) (((m>0) && (m<=Ceilings)) ? True:False)

usetype tcode[X][X];
_Bool dned[Ceilings];
usetype sum_tate[X], sum_yoko[X], sum_name[2];

#define if_name0(s) (s.x==s.y ? True:False)
#define if_name1(s) ((X-s.y-1)==s.x ? True:False)

void follow(usetype m){
	usetype i=0, j, k, l;
	usetype local_tate[X], local_yoko[X], local_name[2];
	_Bool local_dned[Ceilings];

	dprintf("Entering #%d\n", m);

	/*There used to be storetynd here.*/
	for(j=0; j<X; j++){
		local_tate[j]=sum_tate[j];
		local_yoko[j]=sum_yoko[j];
	}
	for(j=0; j<2; j++)
		local_name[j]=sum_name[j];
	for(j=0; j<Ceilings; j++)
		local_dned[j]=dned[j];

	while(find_next_j(&i)!=Ceilings){
		i++;
		dprintf("Trying to subst i(%d) to tcode[%d][%d]\n", i,	\
						chain[m].x, chain[m].y);
		if( ((chain[m].x==X-1) && (chain[m].y==0)) && !(tcode[0][0]<i) )
				continue;
		tcode[chain[m].x][chain[m].y]=i;
		dned[i-1]=True;

		/*There used to be settcodeval here.*/
		sum_tate[chain[m].x]+=i;
		sum_yoko[chain[m].y]+=i;
		if(if_name0(chain[m]))
			sum_name[0]+=i;
		if(if_name1(chain[m]))
			sum_name[1]+=i;

		for(j=0; j<chain[m].toafillcont; j++){
			dprintf("Trying to chain[%d]'s toafill #%d[%d][%d].\n", m, j,	\
				chain[m].toafill[j][0], chain[m].toafill[j][0]);
			l=OneLine;
			for(k=0; k<X-1; k++){
				l-=
					tcode[	\
					chain[m].toafillroad[j][k].x	]	\
					[chain[m].toafillroad[j][k].y	];
			}
			if(!isitpropernum(l)){
				dputs("Isn't proper. Continuing.");
				goto ncot;
			}
			if(dned[l-1]){
				dprintf("TT: dned[tcode[%d][%d](%d)] is already in use.\n",	\
					chain[m].toafill[j][0],	\
					chain[m].toafill[j][1],	\
					l-1);
				goto ncot;
			}

			if( ((chain[m].toafill[j].x==X-1) && (chain[m].toafill[j].y==X-1)) && (!(l>tcode[0][0])) )
				goto ncot;	/*TODO: return; is OK here. Why?*/
			if( ((chain[m].toafill[j].x==0) && (chain[m].toafill[j].y==X-1)) &&	\
					 ((!(l>tcode[X-1][0])) ) )
				goto ncot;	/*TODO: return; is OK here. Why?*/

			tcode[chain[m].toafill[j].x][chain[m].toafill[j].y]=l;
			dned[l-1]=True;
			sum_tate[chain[m].toafill[j].x]+=l;
			sum_yoko[chain[m].toafill[j].y]+=l;
			if(if_name0(chain[m].toafill[j]))
				sum_name[0]+=l;
			if(if_name1(chain[m].toafill[j]))
				sum_name[1]+=l;

			if(!(isitconsist(sum_tate[chain[m].x]) &&	\
				 isitconsist(sum_yoko[chain[m].y]) &&	\
				 ((if_name0(chain[m].toafill[j])) ? isitconsist(sum_name[0]):True) &&	\
				 ((if_name1(chain[m].toafill[j])) ? isitconsist(sum_name[1]):True))	){
				dprintf("tate or yoko or name is not consist. Giving up.\n");
				goto ncot;
			}
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
				puts("------------");
				#endif
				mpz_add_ui(total, total, 1);
			}
		}else{
			dprintf("main tyn is not consist. So don't following.\n");
			dprintf("BTW t:%d y:%d n:%d,%d\n", sum_tate[chain[m].x],	\
					sum_yoko[chain[m].y], sum_name[0],	\
					sum_name[1]);
		}
		
ncot:
		/*There used to be restoretynd here.*/
		dprintf("Restoring\n");
		for(j=0; j<X; j++){
			sum_tate[j]=local_tate[j];
			sum_yoko[j]=local_yoko[j];
		}
		for(j=0; j<2; j++)
			sum_name[j]=local_name[j];
		for(j=0; j<Ceilings; j++)
			dned[j]=local_dned[j];
	}
	dprintf("Leaving from #%d\n", m);
	return;
}
