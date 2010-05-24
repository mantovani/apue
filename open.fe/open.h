#include	<sys/types.h>
#include	<errno.h>
#include	"ourhdr.h"

#define	CL_OPEN "open"			/* client's request for server */

				/* our function prototypes */
int		csopen(char *, int);
