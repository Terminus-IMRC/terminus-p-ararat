#ifndef __DNED_INSIDE__
#define __DNED_INSIDE__
	struct dned_part{
		signed short int num;
		struct dned_part *prior, *next;
	};
	
	extern struct dned_part *dned, *dned_def, *dned_first, *alllocal_dned;
	extern signed short int maxValueInDned;

	struct dned_part* dned_alloc();
	void dned_subst_normal_value(struct dned_part *parts);
	void dned_subst_particular_value(signed short int *tosubst, struct dned_part *parts);
	void dned_cp(struct dned_part *dest, struct dned_part *src);
	void dned_cp_array(struct dned_part *dest, struct dned_part *src);
	void dned_free(struct dned_part *parts);
	struct dned_part* dned_whereis_num(signed short int, struct dned_part*);
	struct dned_part* usedned_symbolic(struct dned_part*);
	void dned_num_serialize(signed short int tostore[Ceilings], struct dned_part *parts);
#endif
