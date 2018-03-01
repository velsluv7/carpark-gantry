/*
 * hour_user.c
 *
 *  Created on: Apr 24, 2011
 *      Author: Velu
 */

 /* program to get the number of hourly users from the database */

#include "hourseason.h"


int hcount()
{
	qdb_hdl_t *hdl;
	qdb_result_t *res;
	int rc;
	char *errmsg;
	int lcount;

	hdl = qdb_connect("/dev/qdb/operdb", 0);
	if (hdl == NULL)
	{
	fprintf(stderr, "Error connecting to database: %s\n", strerror(errno));
	}
	rc = qdb_statement(hdl,"SELECT COUNT (*) AS cnt FROM optable WHERE user ='H' ");
	if (rc == -1)
	{
		errmsg = qdb_geterrmsg(hdl);
		fprintf(stderr, "Error executing SELECT statement: %s\n", errmsg);
	}

res = qdb_getresult(hdl); // Get the result

	if (qdb_rows(res) == 1)
	{
	  //   printf("Got the count : %d\n", *(int *)qdb_cell(res, 0, 0));
	}
	lcount = *(int *)qdb_cell(res, 0, 0) ;
		
	// Free the result
	qdb_freeresult(res);
	// Disconnect from the database
	qdb_disconnect(hdl);
	return lcount;
}
