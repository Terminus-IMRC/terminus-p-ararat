#20130111 from [gitlh]. forget [MaybeCode] on school.
#20130309 We are ANSI and pedantic. With Seasons Of Love.
PROG=Terminus
LINKFLAGS=-lgmp
CC=mpicc

HDRDIRS:=header
SRCDIRS:=main chain code tcode

X?=5
VALFLAGS_X=-DX=$(X)
XNUM=.x

N?=8
VALFLAGS_N=-DN=$(N)
NNUM=.n

PFBOOL=.pf
ifneq ($(PF),)
	VALFLAGS_PF=-DPF
endif

$(shell ([ -f $(PFBOOL) ] && [ "`cat $(PFBOOL)`" = "$(PF)" ]) || echo $(PF) >$(PFBOOL))
$(shell ([ -f $(XNUM) ] && [ `cat $(XNUM)` -eq $(X) ]) || echo $(X) >$(XNUM))
$(shell ([ -f $(NNUM) ] && [ `cat $(NNUM)` -eq $(N) ]) || echo $(N) >$(NNUM))

include Makefile.universe

$(GCHDRS) $(OBJS): $(XNUM)
$(PROG) $(GCHDRS) $(OBJS) $(SRCMODS) $(HDRMODS): $(MAKEFILE_LIST_SANS_MODS)
$(GCHDRS) $(OBJS) $(SRCMODS) $(HDRMODS): ADDCFLAGS+=$(VALFLAGS_X)

DEP_N=$(addsuffix .o, $(DEP_N_C)) $(addsuffix .gch, $(DEP_N_H)) $(addsuffix .mod, $(DEP_N_C) $(DEP_N_H))
$(DEP_N): $(NNUM)
$(DEP_N): ADDCFLAGS+=$(VALFLAGS_N)

DEP_PF=$(addsuffix .o, $(DEP_PF_C)) $(addsuffix .gch, $(DEP_PF_H)) $(addsuffix .mod, $(DEP_PF_C) $(DEP_PF_H))
$(DEP_PF): $(PFBOOL)
$(DEP_PF): ADDCFLAGS+=$(VALFLAGS_PF)

OPTFLAGS:=-g -O0
WARNFLAGS:=-Wall -Wextra -W -Wundef -Wshadow -Wcast-qual -Winline -Wno-long-long -fsigned-char -ansi -pedantic

TOCLEAN+=res*.txt out*.txt

PROC?=2
run:	$(PROG)
	mpiexec -n $(PROC) ./$<
