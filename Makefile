#20130111 from [gitlh]. forget [MaybeCode] on school.
#20130309 We are ANSI and pedantic. With Seasons Of Love.
PROG=Terminus
CFLAGS=-Iheader -g -O0
CFLAGS+=-Wall -Wextra -W -Wundef -Wshadow	\
		-Wcast-qual -Winline -Wno-long-long	\
		-fsigned-char -ansi -pedantic
LDFLAGS=-lc -lgmp
HDRS=header/def.h header/chain.h header/code.h header/debug.h
GCHDRS=$(HDRS:%.h=%.h.gch)
SRCS=chain/chain_init.c chain/chain_main.c chain/printChain.c	\
		code/addChainOrder.c code/allfilled.c code/bfcode.c	\
		code/counttri.c code/findFinalPlace.c code/pfCode.c	\
		main/Terminus.c main/caught_signal.c tcode/find_next_j.c	\
		tcode/follow.c main/will_and_die.c
OBJS=$(SRCS:%.c=%.c.o)
INSTALL=install -s -p -o imrc -g staff -m 0777
GIT=git

X=3
CFLAGS+=-DX=$(X)

XNUM=.x
PFBOOL=.pf
DEP=$(XNUM)

ifneq ($(PF),)
	CFLAGS+=-DPF
endif
$(shell ([ -f $(PFBOOL) ] && [ "`cat $(PFBOOL)`" = "$(PF)" ])	\
										|| echo $(PF) >$(PFBOOL))

$(shell ([ -f $(XNUM) ] && [ `cat $(XNUM)` -eq $(X) ])	\
									|| echo $(X) >$(XNUM))

all:	$(PROG) $(DEP)

$(PROG):	$(GCHDRS) $(OBJS) $(DEP)
	$(LINK.o) $(OUTPUT_OPTION) $(OBJS)

%.c.o:	%.c $(GCHDRS) $(MAKEFILE_LIST) $(DEP)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

%.h.gch:	%.h $(MAKEFILE_LIST) $(DEP)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

header/code.h.gch header/chain.h.gch: header/def.h
tcode/follow.c.o:	$(PFBOOL)

clean:
	$(RM) $(OBJS) $(GCHDRS) $(PROG)

run:	$(PROG)
	time -p ./$<

install:	$(PROG)
	$(INSTALL) $< $(DEST)

line:
	@wc -c -l $(SRCS) $(HDRS) $(MAKEFILE_LIST)

vrun:	$(PROG)
	valgrind --leak-check=yes --track-origins=no -v ./$<

load:
	@tce-load -i compiletc git less gdb >/dev/null

greptodo:
	-grep -F -n TODO $(HDRS) $(SRCS)

gitinit:
	$(GIT) init
	$(GIT) config --global user.name "Terminus"
	$(GIT) config --global user.email "i.can.speak.c.and.basic@gmail.com"
	$(GIT) config --global color.ui auto
	$(GIT) remote add origin https://terminus.backlog.jp/git/TERM/terminus.git

.PHONY:	load
