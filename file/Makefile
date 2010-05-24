include ../Make.defines

PROGS =	access cdpwd changemod conf devfd devrdev devstdin \
		fileflags filesize filetype ftruncate ftw1 ftw2 ftw3 ftw4 ftw5 \
		hello hole limits longpath ls1 mycd \
		rename savedid tatimes testerror testsymlink times truncate \
		uidgid umask unlink

all:	${PROGS}

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS) $(S5LIB)

clean:
	rm -f ${PROGS} ${TEMPFILES} file.hole
