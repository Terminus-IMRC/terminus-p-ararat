#20130111 from [gitlh]. forget [MaybeCode] on school.
#20130309 We are ANSI and pedantic. With Seasons Of Love.
PROG=Terminus
CC=mpicc
HEADERFLAGS=-Iheader
OPTFLAGS=-g -O0
WARNFLAGS=-Wall -Wextra -W -Wundef -Wshadow	\
		-Wcast-qual -Winline -Wno-long-long	\
		-fsigned-char -ansi -pedantic
#CFLAGS+=-mcmodel=medium
LOCALLDFLAGS=-lgmp
HDRS=header/def.h header/chain.h header/code.h header/debug.h header/parallel.h
GCHDRS=$(HDRS:%.h=%.h.gch)
SRCS=chain/chain_init.c chain/chain_main.c chain/printChain.c	\
		code/addChainOrder.c code/allfilled.c code/bfcode.c	\
		code/counttri.c code/findFinalPlace.c code/pfCode.c	\
		main/Terminus.c main/caught_signal.c tcode/find_next_j.c	\
		tcode/follow.c main/will_and_die.c tcode/follow_pa.c	\
		chain/addRestNameChain.c
OBJS=$(SRCS:%.c=%.c.o)
INSTALL=install -s -p -o imrc -g staff -m 0777
GIT=git

X=3
VALFLAGS+=-DX=$(X)

XNUM=.x
PFBOOL=.pf
DEP=$(XNUM)

N+=3
VALFLAGS+=-DN=$(N)

PROC:=2

ifneq ($(PF),)
	VALFLAGS+=-DPF
endif
$(shell ([ -f $(PFBOOL) ] && [ "`cat $(PFBOOL)`" = "$(PF)" ])	\
	|| echo $(PF) >$(PFBOOL))

$(shell ([ -f $(XNUM) ] && [ `cat $(XNUM)` -eq $(X) ])	\
	|| echo $(X) >$(XNUM))

COMPILE.c=$(CC) $(HEADERFLAGS) $(OPTFLAGS) $(WARNFLAGS) $(VALFLAGS) $(CFLAGS) -c
LINK.o=$(CC) $(LOCALLDFLAGS) $(LDFLAGS)

all:	$(PROG) $(DEP)

$(PROG):	$(GCHDRS) $(OBJS) $(DEP)
	@echo -e "\tLINK\t$@"
	@$(LINK.o) $(OUTPUT_OPTION) $(OBJS)

%.c.o:	%.c $(GCHDRS) $(MAKEFILE_LIST) $(DEP)
	@echo -e "\tCC\t$@"
	@$(COMPILE.c) $(OUTPUT_OPTION) $<

%.h.gch:	%.h $(MAKEFILE_LIST) $(DEP)
	@echo -e "\tCC\t$@"
	@$(COMPILE.c) $(OUTPUT_OPTION) $<

header/code.h.gch header/chain.h.gch: header/def.h
tcode/follow.c.o main/Terminus.c.o code/pfCode.c.o header.def.h:	$(PFBOOL)

clean:
	$(RM) $(OBJS) $(GCHDRS) $(PROG)

run:	$(PROG)
	mpiexec -n $(PROC) ./$<

install:	$(PROG)
	$(INSTALL) $< $(DEST)

line:
	@wc -c -l $(SRCS) $(HDRS) $(MAKEFILE_LIST)

vrun:	$(PROG)
	valgrind --leak-check=yes --track-origins=no -v ./$<

load:
	@tce-load -i compiletc git less gdb gmp gmp-dev

greptodo:
	-grep -F -n TODO $(HDRS) $(SRCS)

gitinit:
	$(GIT) init
	$(GIT) config --global user.name "Terminus"
	$(GIT) config --global user.email "i.can.speak.c.and.basic@gmail.com"
	$(GIT) config --global color.ui auto

product: $(PROG)
	strip --strip-all $<

.PHONY:	load
