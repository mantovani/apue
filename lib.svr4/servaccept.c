#include	<sys/types.h>
#include	<sys/stat.h>
#include	<stropts.h>
#include	"ourhdr.h"

/* Wait for a client connection to arrive, and accept it.
 * We also obtain the client's user ID. */

int			/* returns new fd if all OK, -1 on error */
serv_accept(int listenfd, uid_t *uidptr)
{
	struct strrecvfd	recvfd;

	if (ioctl(listenfd, I_RECVFD, &recvfd) < 0)
		return(-1);		/* could be EINTR if signal caught */

	if (uidptr != NULL)
		*uidptr = recvfd.uid;	/* effective uid of caller */

	return(recvfd.fd);	/* return the new descriptor */
}
