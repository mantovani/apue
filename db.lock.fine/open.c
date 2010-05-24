#include	"db.h"

/* Open or create a database.  Same arguments as open(). */

DB *
db_open(const char *pathname, int oflag, int mode)
{
	DB			*db;
	int			i, len;
	char		asciiptr[PTR_SZ + 1],
				hash[(NHASH_DEF + 1) * PTR_SZ + 2];
					/* +2 for newline and null */
	struct stat	statbuff;

		/* Allocate a DB structure, and the buffers it needs */
	len = strlen(pathname);
	if ( (db = _db_alloc(len)) == NULL)
		err_dump("_db_alloc error for DB");

	db->oflag = oflag;		/* save a copy of the open flags */

		/* Open index file */
	strcpy(db->name, pathname);
	strcat(db->name, ".idx");
	if ( (db->idxfd = open(db->name, oflag, mode)) < 0) {
		_db_free(db);
		return(NULL);
	}
		/* Open data file */
	strcpy(db->name + len, ".dat");
	if ( (db->datfd = open(db->name, oflag, mode)) < 0) {
		_db_free(db);
		return(NULL);
	}

		/* If the database was created, we have to initialize it */
	if ((oflag & (O_CREAT | O_TRUNC)) == (O_CREAT | O_TRUNC)) {
			/* Write lock the entire file so that we can stat
			   the file, check its size, and initialize it,
			   as an atomic operation. */
		if (writew_lock(db->idxfd, 0, SEEK_SET, 0) < 0)
			err_dump("writew_lock error");

		if (fstat(db->idxfd, &statbuff) < 0)
			err_sys("fstat error");
		if (statbuff.st_size == 0) {
				/* We have to build a list of (NHASH_DEF + 1) chain
				   ptrs with a value of 0.  The +1 is for the free
				   list pointer that precedes the hash table. */
			sprintf(asciiptr, "%*d", PTR_SZ, 0);
			hash[0] = 0;
			for (i = 0; i < (NHASH_DEF + 1); i++)
				strcat(hash, asciiptr);
			strcat(hash, "\n");

			i = strlen(hash);
			if (write(db->idxfd, hash, i) != i)
				err_dump("write error initializing index file");
		}
		if (un_lock(db->idxfd, 0, SEEK_SET, 0) < 0)
			err_dump("un_lock error");
	}
	db->nhash   = NHASH_DEF;/* hash table size */
	db->hashoff = HASH_OFF;	/* offset in index file of hash table */
							/* free list ptr always at FREE_OFF */
	db_rewind(db);

	return(db);
}
