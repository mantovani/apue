#include	"call.h"
#include	<poll.h>
#include	<stropts.h>

/* Copy everything from stdin to "remfd",
 * and everything from "remfd" to stdout. */

#define	BUFFSIZE	512

void
loop(int remfd)
{
	int				bol, n, nread;
	char			c, buff[BUFFSIZE];
	struct pollfd	fds[2];

	setbuf(stdout, NULL);		/* set stdout unbuffered */
								/* (for printfs in take() and put() */
	fds[0].fd = STDIN_FILENO;	/* user's terminal input */
	fds[0].events = POLLIN;
	fds[1].fd = remfd;			/* input from remote (modem) */
	fds[1].events = POLLIN;

	for ( ; ; ) {
		if (poll(fds, 2, INFTIM) <= 0)
			err_sys("poll error");

		if (fds[0].revents & POLLIN) {	/* data to read on stdin */
			if (read(STDIN_FILENO, &c, 1) != 1)
				err_sys("read error from stdin");

			if (c == escapec && bol) {
				if ( (n = doescape(remfd)) < 0)
					break;		/* user wants to terminate */
				else if (n == 0)
					continue;	/* escape seq has been processed */

				/* else, char following escape was not special,
				   so it's returned and echoed below */
				c = n;
			}
			if (c == '\r' || c == '\n')
				bol = 1;
			else
				bol = 0;

			if (write(remfd, &c, 1) != 1)
				err_sys("write error");
		}
		if (fds[0].revents & POLLHUP)
			break;		/* stdin hangup -> done */

		if (fds[1].revents & POLLIN) {	/* data to read from remote */
			if ( (nread = read(remfd, buff, BUFFSIZE)) <= 0)
				break;		/* error or EOF, terminate */

			if (writen(STDOUT_FILENO, buff, nread) != nread)
				err_sys("writen error to stdout");
		}
		if (fds[1].revents & POLLHUP)
			break;		/* modem hangup -> done */
	}
}
