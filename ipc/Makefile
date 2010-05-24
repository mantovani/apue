include ../Make.defines

PROGS =	add2 add2stdio fifo1 myuclc \
		pipeawk pipe1 pipe2 pipe3 pipe4 pipe5 \
		pipe4stdio pipetype pollin pollout \
		popen1 popen2 popen3 popen4 posixex \
		selectin selectout spipe4 \
		tpassfd tpopen tshm ttellwait1 ttellwait2

all:	${PROGS}

ttellwait1: ttellwait1.o tellwait.o
		  	$(LINK.c) -o $@ ttellwait1.o tellwait.o $(LDLIBS)

ttellwait2: ttellwait2.o tellwait.o
		  	$(LINK.c) -o $@ ttellwait2.o tellwait.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
