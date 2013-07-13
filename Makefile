#20130111 from [gitlh]. forget [MaybeCode] on school.
#20130309 We are ANSI and pedantic. With Seasons Of Love.
PROG=Terminus
LINKFLAGS=-lgmp
CC=mpicc

HDRDIRS:=header
SRCDIRS:=main chain code tcode

X?=3
VALFLAGS+=-DX=$(X)
XNUM=.x

N?=3
VALFLAGS+=-DN=$(N)
NNUM=.n

PFBOOL=.pf
ifneq ($(PF),)
	VALFLAGS+=-DPF
endif

$(shell ([ -f $(PFBOOL) ] && [ "`cat $(PFBOOL)`" = "$(PF)" ]) || echo $(PF) >$(PFBOOL))
$(shell ([ -f $(XNUM) ] && [ `cat $(XNUM)` -eq $(X) ]) || echo $(X) >$(XNUM))
$(shell ([ -f $(NNUM) ] && [ `cat $(NNUM)` -eq $(N) ]) || echo $(N) >$(NNUM))

include Makefile.universe

$(OBJS): $(XNUM)
$(GCHDRS) $(OBJS) $(SRCMODS) $(HDRMODS): ADDCFLAGS+=$(VALFLAGS)

OPTFLAGS:=-g -O0
WARNFLAGS:=-Wall -Wextra -W -Wundef -Wshadow -Wcast-qual -Winline -Wno-long-long -fsigned-char -ansi -pedantic

TOCLEAN+=res*.txt out*.txt

PROC?=2
run:	$(PROG)
	mpiexec -n $(PROC) ./$<
