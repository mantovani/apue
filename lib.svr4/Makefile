include ../Make.defines

# Makefile for library.

AR	= ar
COMM_OBJ   = bufargs.o cliconn.o clrfl.o \
			 daemoninit.o error.o errorlog.o lockreg.o locktest.o \
			 openmax.o pathalloc.o popen.o prmask.o \
			 ptyfork.o ptyopen.o readn.o recvfd.o \
			 senderr.o sendfd.o servaccept.o servlisten.o \
			 setfl.o signal.o signalintr.o \
			 sleep.o sleepus.o spipe.o strerror.o \
			 tellwait.o ttymodes.o writen.o
NOANSI_OBJ = prexit.o	# Sun's <sys/wait.h> ain't ANSI C
# BSD_OBJ  =
S5_OBJ	   = semaph.o
RANLIB     = ranlib

all:
	make `systype.sh`

lib:	${OBJS}
	${AR} rv ${LIB} $?
	${RANLIB} ${LIB}

bsd:
	make "CFLAGS = -O" \
		"OBJS = $(COMM_OBJ) $(BSD_OBJ)" "RANLIB = ranlib" lib

sun:
	make "CFLAGS = $(CFLAGS) -O" \
		"OBJS = $(COMM_OBJ) $(BSD_OBJ) $(S5_OBJ)" "RANLIB = ranlib" lib
	make "CFLAGS = $(NOANSICFLAGS) -O" \
		"OBJS = $(NOANSI_OBJ)" "RANLIB = ranlib" lib

svr4:
	make "CFLAGS = -O" \
		"OBJS = $(COMM_OBJ) $(NOANSI_OBJ) $(S5_OBJ)" "RANLIB = ls -l" lib

clean:
	rm -f *.o a.out core temp.* $(LIBMISC)
