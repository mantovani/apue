#include	<sys/types.h>
#include	<sys/stat.h>
#include	<stropts.h>
#include	"ourhdr.h"

#define	FIFO_MODE  (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
					/* user rw, group rw, others rw */

int			/* returns fd if all OK, <0 on error */
serv_listen(const char *name)
{
	int		tempfd, fd[2], len;

					/* create a file: mount point for fattach() */
	unlink(name);
	if ( (tempfd = creat(name, FIFO_MODE)) < 0)
		return(-1);
	if (close(tempfd) < 0)
		return(-2);

	if (pipe(fd) < 0)
		return(-3);
							/* push connld & fattach() on fd[1] */
	if (ioctl(fd[1], I_PUSH, "connld") < 0)
		return(-4);
	if (fattach(fd[1], name) < 0)
		return(-5);

	return(fd[0]);	/* fd[0] is where client connections arrive */
}
