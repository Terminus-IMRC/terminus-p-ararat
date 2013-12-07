#include <stdlib.h>
#include "def.h"
#include "dned.h"
#include <assert.h>

signed short int maxValueInDned;

static struct dned_part* dned_alloc_internal(int elem)
{
	int i;
	struct dned_part *toret;
	
	pass();
	toret=(struct dned_part*)malloc(elem*sizeof(struct dned_part));
	pass();
	assert(toret);
	pass();

	for(i=1; i<elem-1; i++){
		toret[i].prior=toret+(i-1);
		toret[i].self=toret+i;
		toret[i].next=toret+(i+1);
	}
	toret[0].prior=NULL;
	toret[0].self=toret;
	toret[0].next=toret+1;
	toret[elem-1].prior=toret+((elem-1)-1);
	toret[elem-1].self=toret+(elem-1);
	toret[elem-1].next=NULL;

	return toret;
}

struct dned_part* dned_alloc()
{
	return dned_alloc_internal(Ceilings);
}

dned_entire dned_entire_alloc()
{
	pass();
	return dned_alloc_internal(Ceilings);
	pass();
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
	parts[i-1].next=NULL;

	return;
}

void dned_cp(struct dned_part *dest, struct dned_part *src)
{
	for(; src; dest=dest->next, src=src->next)
		dest->num=src->num;

	return;
}

void dned_store_entire(dned_entire dest, struct dned_part *src)
{
	int i;

	/* Not to mind i<chaincont because the length of src is unknown. */
	for(i=0; src; src=src->next, i++){
		dest[i].num=src->num;
		dest[i].prior=src->prior?src->prior->self:NULL;
		dest[i].next=src->next?src->next->self:NULL;
		dest[i].self=src->self->self;
	}

	return;
}

void dned_restore_entire(struct dned_part *dest, dned_entire src)
{
	int i;

	/* Not to mind src because the length of src is unknown. */
	i=-1;
	do{
		i++;
		dest->num=src[i].num;
		dest->prior=src[i].prior?src[i].prior->self:NULL;
		dest->next=src[i].next?src[i].next->self:NULL;
		dest->self=src[i].self->self;
		dest=dest->next;
	}while(dest);

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

void dned_entire_free(dned_entire parts)
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
			return start->self;
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
			dprintf("parts:%p dned:%p\n", parts, dned);
			dprintf("parts->num:%d dned->num:%d\n", parts->num, dned->num);
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

void dned_print_chain(FILE *fp, struct dned_part *parts)
{
	do
		fprintf(fp, "%p(%d)->", parts, parts->num);
	while((parts=parts->next));
	fprintf(fp, "(nil)\n");

	return;
}

void dned_print_chain_full(FILE *fp, struct dned_part *parts)
{
	do{
		if(!parts->prior)
			fprintf(fp, "[^(nil)<-");
		else
			fprintf(fp, "[%d(%p)<-", parts->prior->num, parts->prior);
		fprintf(fp, "%d(%p)->", parts->num, parts->self);
		if(!parts->next)
			fprintf(fp, "$(nil)]");
		else
			fprintf(fp, "%d(%p)]", parts->next->num, parts->next);
	}while((parts=parts->next));

	return;
}

void dned_print_chain_only_num(FILE *fp, struct dned_part *parts)
{
	do
		fprintf(fp, "%d->", parts->num);
	while((parts=parts->next));
	fprintf(fp, "(nil)\n");

	return;
}

void dned_print_chain_only_num_full(FILE *fp, struct dned_part *parts)
{
	do{
		if(!parts->prior)
			fprintf(fp, "[^<-");
		else
			fprintf(fp, "[%d<-", parts->prior->num);
		fprintf(fp, "%d->", parts->num);
		if(!parts->next)
			fprintf(fp, "$]");
		else
			fprintf(fp, "%d]", parts->next->num);
	}while((parts=parts->next));

	return;
}

struct dned_part* dned_follow_to_last(struct dned_part *parts)
{
	while(parts->next)
		parts=parts->next;
	return parts->self;
}

_Bool dned_check_consistency(struct dned_part *parts)
{
	do{
		if(parts->prior){
			if(parts->self!=parts->prior->next)
				return 1;
			if(parts->num<=parts->prior->num)
				return 1;
		}
		if(parts->next){
			if(parts->self!=parts->next->prior)
				return 1;
		}else
			if(maxValueInDned!=parts->num)
				return 1;
	}while((parts=parts->next));

	return 0;
}
