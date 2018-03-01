/*
 * deletedb.c
 *
 *  Created on: Apr 22, 2011
 *      Author: Velu
 */

#include<globalstruct.h>

int DB_DeleteLabel(DB_OP *val)
{
	DB_OP *v =(DB_OP*)val;
	qdb_hdl_t *hdl;
	qdb_result_t *res;
	int rc;
	char *errmsg;
	int row;
	int label;

	label = v->label ;

	char try2[2] = ";";
	char try[100] = "DELETE FROM optable WHERE label = ";
	sprintf(try,"%s%d%s",try,label,try2);
	printf(" the query = %s\n",try);

	hdl = qdb_connect("/dev/qdb/operdb", 0);
			if (hdl == NULL)
			{
				fprintf(stderr, "Error connecting to database: %s\n", strerror(errno));
				return EXIT_FAILURE;
			}
			printf(" successfully connected\n");

		rc = qdb_statement(hdl,try);
			if (rc == -1)
			{
				 errmsg = qdb_geterrmsg(hdl);
			 	 fprintf(stderr, "Error executing SELECT statement: %s\n", errmsg);
			 	 return EXIT_FAILURE;
		    }

			printf(" query successfully executed\n");

return 1;
}
