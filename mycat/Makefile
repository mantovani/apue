include ../Make.defines

CFLAGS	= $(CFLAGSO)
# need -O in this directory, since we're timing the
# programs and we need the getc() and putf() macros
# expanded efficiently in-line.

PROGS =	copy fgetcfputc fgetsfputs getcputc mycat mycatosync

all:	${PROGS}

clean:
	rm -f ${PROGS} ${TEMPFILES}
