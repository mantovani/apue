include ../Make.defines

PROGS =	abort.o child critical mask queue \
		raise.o read1 read2 readpart reenter \
		segv setops.o sigtstp sigusr \
		suspend1 suspend2 \
		system.o systest1 systest2 \
		trestart tsavedid tsiglist tsleep tsleep1 tsleep2 tsleep3 \
		ttellwait1 ttellwait2

all:	${PROGS}

systest1.o:
		${NOANSICOMPILE.c} systest1.c

# We want to link with our own version of system() for systest[12].
systest1: system.o systest1.o
		  $(LINK.c) -o $@ systest1.o system.o $(LDLIBS)

systest2: system.o systest2.o
		  $(LINK.c) -o $@ systest2.o system.o $(LDLIBS)

tsleep1:  sleep1.o tsleep1.o
		  $(LINK.c) -o $@ sleep1.o tsleep1.o $(LDLIBS)

tsleep2:  sleep2.o tsleep2.o
		  $(LINK.c) -o $@ sleep2.o tsleep2.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
