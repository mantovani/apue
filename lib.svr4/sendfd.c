#include	<sys/types.h>
#include	<stropts.h>
#include	"ourhdr.h"

/* Pass a file descriptor to another process.
 * If fd<0, then -fd is sent back instead as the error status. */

int
send_fd(int clifd, int fd)
{
	char	buf[2];		/* send_fd()/recv_fd() 2-byte protocol */

	buf[0] = 0;			/* null byte flag to recv_fd() */
	if (fd < 0) {
		buf[1] = -fd;	/* nonzero status means error */
		if (buf[1] == 0)
			buf[1] = 1;	/* -256, etc. would screw up protocol */
	} else {
		buf[1] = 0;		/* zero status means OK */
	}

	if (write(clifd, buf, 2) != 2)
		return(-1);

	if (fd >= 0)
		if (ioctl(clifd, I_SENDFD, fd) < 0)
			return(-1);
	return(0);
}
