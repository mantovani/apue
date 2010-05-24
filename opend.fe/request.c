#include	"opend.h"
#include	<fcntl.h>

void
request(char *buf, int nread, int fd)
{
	int		newfd;

	if (buf[nread-1] != 0) {
		sprintf(errmsg, "request not null terminated: %*.*s\n",
									nread, nread, buf);
		send_err(STDOUT_FILENO, -1, errmsg);
		return;
	}

			/* parse the arguments, set options */
	if (buf_args(buf, cli_args) < 0) {
		send_err(STDOUT_FILENO, -1, errmsg);
		return;
	}

	if ( (newfd = open(pathname, oflag)) < 0) {
		sprintf(errmsg, "can't open %s: %s\n",
								pathname, strerror(errno));
		send_err(STDOUT_FILENO, -1, errmsg);
		return;
	}

			/* send the descriptor */
	if (send_fd(STDOUT_FILENO, newfd) < 0)
		err_sys("send_fd error");
	close(newfd);		/* we're done with descriptor */
}
