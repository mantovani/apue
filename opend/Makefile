include ../Make.defines

PROGS =	opend
OBJS = cliargs.o client.o loop.o main.o request.o

all:	${PROGS}

${OBJS}:opend.h

opend:	${OBJS}
		${LINK.c} -o $@ ${OBJS} ${LDLIBS}

clean:
		rm -f ${PROGS} ${TEMPFILES}
