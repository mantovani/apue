include ../Make.defines

PROGS =	open
OBJS = main.o open.o

all:	${PROGS}

${OBJS}: open.h

open:	${OBJS}
		${LINK.c} -o $@ ${OBJS} ${LDLIBS}

clean:
		rm -f ${PROGS} ${TEMPFILES}
