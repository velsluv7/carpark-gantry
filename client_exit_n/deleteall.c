/*
 * deleteall.c
 *
 *  Created on: Apr 24, 2011
 *      Author: Velu
 */


#include<globalstruct.h>

int DeleteAll()
{

	qdb_hdl_t *hdl;

	int rc;
	char *errmsg;


	hdl = qdb_connect("/dev/qdb/operdb", 0);
			if (hdl == NULL)
			{
				fprintf(stderr, "Error connecting to database: %s\n", strerror(errno));
				return EXIT_FAILURE;
			}
			printf(" successfully connected\n");

		rc = qdb_statement(hdl,"DELETE FROM optable");
			if (rc == -1)
			{
				 errmsg = qdb_geterrmsg(hdl);
			 	 fprintf(stderr, "Error executing SELECT statement: %s\n", errmsg);
			 	 return EXIT_FAILURE;
		    }

			printf(" Deleted  successfully executed\n");

return 1;
}
