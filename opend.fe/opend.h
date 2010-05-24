#include	<sys/types.h>
#include	<errno.h>
#include	"ourhdr.h"

#define	CL_OPEN "open"				/* client's request for server */

			/* declare global variables */
extern char	 errmsg[];	/* error message string to return to client */
extern int	 oflag;		/* open() flag: O_xxx ... */
extern char	*pathname;	/* of file to open() for client */

			/* function prototypes */
int		 cli_args(int, char **);
void	 request(char *, int, int);
