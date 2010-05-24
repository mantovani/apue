include ../Make.defines

PROGS =	csize ctermid.o \
		settty t_isatty t_getpass t_raw t_raw2 t_ttyname winch

all:	${PROGS}

t_isatty: t_isatty.o isatty.o
		  ${LINK.c} -o $@ t_isatty.o isatty.o ${LDLIBS}

t_getpass: t_getpass.o getpass.o
		  ${LINK.c} -o $@ t_getpass.o getpass.o ${LDLIBS}

t_raw: t_raw.o
	   ${LINK.c} -o $@ t_raw.o ${LDLIBS}

t_ttyname: t_ttyname.o ttyname.o
		   ${LINK.c} -o $@ t_ttyname.o ttyname.o ${LDLIBS}

# SunOS has a problem with its tty ioctl definitions.  The definition
# for _IOR(x,y,t) assumes that 'x' on the right hand side gets replaced
# with the first argument.  This isn't the way ANSI C works.  With gcc
# you need to fix these headers or the winch.c file won't compile.

clean:
	rm -f ${PROGS} ${TEMPFILES}
