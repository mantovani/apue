#include	"lprps.h"

static void	usage(void);

int
main(int argc, char *argv[])
{
	int			c;

	log_open("lprps", LOG_PID, LOG_LPR);

	opterr = 0;		/* don't want getopt() writing to stderr */
	while ( (c = getopt(argc, argv, "cdh:i:l:n:x:y:w:")) != EOF) {
		switch (c) {
		case 'c':		/* control chars to be passed */
		case 'x':		/* horizontal page size */
		case 'y':		/* vertical page size */
		case 'w':		/* width */
		case 'l':		/* length */
		case 'i':		/* indent */
			break;	/* not interested in these */

		case 'd':		/* debug (interactive) */
			debug = 1;
			break;

		case 'n':		/* login name of user */
			loginname = optarg;
			break;

		case 'h':		/* host name of user */
			hostname = optarg;
			break;
		case '?':
			log_msg("unrecognized option: -%c", optopt);
			usage();
		}
	}

	if (hostname == NULL || loginname == NULL)
		usage();	/* require both hostname and loginname */

	if (optind < argc)
		acct_file = argv[optind];	/* remaining arg = acct file */

	if (debug)
		tty_open();

	if (atexit(close_mailfp) < 0)	/* register func for exit() */
		log_sys("main: atexit error");

	get_status();

	get_page(&start_page);

	send_file();			/* copies stdin to printer */

	get_page(&end_page);

	do_acct();

	exit(EXIT_SUCCESS);
}

static void
usage(void)
{
	log_msg("lprps: invalid arguments");
	exit(EXIT_THROW_AWAY);
}
