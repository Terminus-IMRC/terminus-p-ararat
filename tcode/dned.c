#include <stdlib.h>
#include "def.h"
#include "dned.h"
#include <assert.h>

signed short int maxValueInDned;

struct dned_part* dned_alloc()
{
	struct dned_part *toret;
	
	toret=(struct dned_part*)malloc(Ceilings*sizeof(struct dned_part));
	assert(toret);

	dned_set_proper_pointer(toret);

	return toret;
}

void dned_set_proper_pointer(struct dned_part *toret)
{
	int i;

	for(i=1; i<Ceilings-1; i++){
#if 0
		(*toret)[i].prior=(*toret)+(i-1);
		(*toret)[i].self=(*toret)+i;
		(*toret)[i].next=(*toret)+(i+1);
#else
		toret[i].prior=toret+(i-1);
		toret[i].self=toret+i;
		toret[i].next=toret+(i+1);
#endif
	}
#if 0
	(*toret)[0].prior=NULL;
	(*toret)[0].self=*toret;
	(*toret)[0].next=(*toret)+1;
	(*toret)[Ceilings-1].prior=(*toret)+((Ceilings-1)-1);
	(*toret)[Ceilings-1].self=(*toret)+(Ceilings-1);
	(*toret)[Ceilings-1].next=NULL;
#else
	toret[0].prior=NULL;
	toret[0].self=toret;
	toret[0].next=toret+1;
	toret[Ceilings-1].prior=toret+((Ceilings-1)-1);
	toret[Ceilings-1].self=toret+(Ceilings-1);
	toret[Ceilings-1].next=NULL;
#endif

	return;
}

void dned_subst_normal_value(struct dned_part *parts)
{
	int i;
	
	for(i=0; i<Ceilings; i++)
		parts[i].num=i+1;
	
	return;
}

/* Substitute the numbers in tosubst until 0 appears. */
void dned_subst_particular_value(signed short int *tosubst, struct dned_part *parts)
{
	int i;

	for(i=0; tosubst[i]!=0; i++)
		parts[i].num=tosubst[i];

	return;
}

void dned_cp(struct dned_part *dest, struct dned_part *src)
{
	for(; src; dest=dest->next, src=src->next)
		dest->num=src->num;

	return;
}

void dned_cp_array(struct dned_part *dest, struct dned_part *src)
{
	int i;

	for(i=0; i<Ceilings; i++)
		memcpy(dest, src, sizeof(struct dned_part));

	return;
}

void dned_free(struct dned_part *parts)
{
	free(parts);
	return;
}

struct dned_part* dned_whereis_num(signed short tofind, struct dned_part *start)
{
#if 0
	while(start->num!=tofind){
		if(!start->next)
			return NULL;
		start=start->next;
	}
	return start;
#else
	while(start){
		if(start->num==tofind)
			return start;
		start=start->next;
	}
	return NULL;
#endif
}

/* TODO: Be void and the argument would be struct dned_part **parts :) */
void usedned_symbolic(struct dned_part *parts)
{
	if(!parts->prior){
		if(parts->next){
			fprintf(stderr, "parts:%p dned:%p\n", parts, dned);
			fprintf(stderr, "parts->num:%d dned->num:%d\n", parts->num, dned->num);
			assert(parts->num == dned->num);
			parts->next->prior=NULL;
			dned=dned->next;
		}
		else
			dned=NULL;
	}else if(!parts->next){
		parts->prior->next=NULL;
		maxValueInDned=parts->prior->num;
	}else{
		parts->prior->next=parts->next;
		parts->next->prior=parts->prior;
	}
	
	return;
}

/* Of cource, the number of tostore elements must be equal or more than the number of parts elements.
   This function will NOT check this. */
void dned_num_serialize(signed short int tostore[Ceilings], struct dned_part *parts)
{
#if 0
	do{
		*tostore=parts->num;
		tostore++;
		parts=parts->next;
	}while(parts);
#else
	int i;

	assert(parts);
	for(i=0; i<Ceilings; i++){
		tostore[i]=parts->num;
		parts=parts->next;
		if(!parts)
			break;
	}
#endif

	return;
}

int dned_probe_length(struct dned_part* parts)
{
	int cnt=0;

	while(parts){
		cnt++;
		parts=parts->next;
	}

	return cnt;
}
