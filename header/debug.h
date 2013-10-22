#ifndef printpass
	#define printpass() printf("passed line %d on %s\n", __LINE__, __FILE__)
	#define pprintpass() printf("PD%d: passed line %d on %s\n", commrank, __LINE__, __FILE__)
#endif
#ifdef NOPASS
	#define pass()
	#define ppass()
#else
	#ifdef FLUSH
		#define pass() printpass(); fflush(stdout)
		#define ppass() pprintpass(); fflush(stdout)
	#else
		#define pass() printpass()
		#define ppass() pprintpass()
	#endif
#endif

#ifdef NODP
	#define dputchar(c)
	#define dputs(str)
	#define dprintf(...)
#else
	#define dputchar(c) putchar(c)
	#define dputs(str) puts(str)
	#define dprintf(...) printf(__VA_ARGS__)
#endif
