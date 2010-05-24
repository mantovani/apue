#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	"ourhdr.h"

/* Create a client endpoint and connect to a server. */

int			/* returns fd if all OK, <0 on error */
cli_conn(const char *name)
{
	int		fd;

				/* open the mounted stream */
	if ( (fd = open(name, O_RDWR)) < 0)
		return(-1);
	if (isastream(fd) == 0)
		return(-2);

	return(fd);
}
