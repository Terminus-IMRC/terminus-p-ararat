#ifndef __DNED_INSIDE__
#define __DNED_INSIDE__
	struct dned_part{
		signed short int num;
		struct dned_part *prior, *next;
		struct dned_part *self;
	};

	/* The number of element must be chaincont. */
	typedef struct *dned_part dned_entire;

	extern struct dned_part *dned, *dned_global_def, **alllocal_dned;
	extern signed short int maxValueInDned;

	struct dned_part* dned_alloc();
	dned_entire dned_entire_alloc();
	/*void dned_set_proper_pointer(struct dned_part *toret);*/
	void dned_subst_normal_value(struct dned_part *parts);
	void dned_subst_particular_value(signed short int *tosubst, struct dned_part *parts);
	void dned_cp(struct dned_part *dest, struct dned_part *src);
	void dned_cp_array(struct dned_part *dest, struct dned_part *src);
	void dned_free(struct dned_part *parts);
	struct dned_part* dned_whereis_num(signed short int, struct dned_part*);
	void usedned_symbolic(struct dned_part*);
	void dned_num_serialize(signed short int tostore[Ceilings], struct dned_part *parts);
	int dned_probe_length(struct dned_part*);
	void dned_store_entire(dned_entire dest, struct dned_part *src);
	void dned_restore_entire(struct dned_part *dest, dned_entire src);
#endif
