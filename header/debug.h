#ifndef printpass
	#define printpass() printf("passed line %d on %s\n",	\
							__LINE__, __FILE__)
#endif
#ifdef NOPASS
	#define pass()
#else
	#ifdef FLUSH
		#define pass() printpass(); fflush(stdout)
	#else
		#define pass() printpass()
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
