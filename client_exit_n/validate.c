/*
 * validate.c
 *
 *  Created on: Apr 22, 2011
 *      Author: Velu
 */



#include<globalstruct.h>

int DB_ValidateExit(DB_OP *val)
{
	DB_OP *v =(DB_OP*)val;
	qdb_hdl_t *hdl;
	qdb_result_t *res;
	int rc;
	char *errmsg;
	int row;
	int label;

	label = v->label;
	char try2[2] = ";";
	char try[100] = "SELECT * FROM optable WHERE label = ";
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
	res = qdb_getresult(hdl); // Get the result
	if (res == NULL)
		{
			fprintf(stderr, "Error getting result: %s\n", strerror(errno));
			return EXIT_FAILURE;
		}
	printf(" the result is obtained successfully\n");

	row = qdb_rows(res);
	if (row == 0)
		{
			printf(" entry not in the table \n");
			qdb_freeresult(res);
			qdb_disconnect(hdl);
			return -1;
		}
	else
		{
			printf(" entry in table\n");
			row = row -1;
			printf(" the row is %d\n",row);

			v->label = *(int*)qdb_cell(res, row, 0);
			v->type  = (char*)qdb_cell(res,row,1);
			v->user = (char*)qdb_cell(res,row,2);
			v->entry_hr = *(int*)qdb_cell(res,row,3);
			v->entry_mn = *(int*)qdb_cell(res,row,4);
			v->AvailAmount1 = *(int*)qdb_cell(res,row,8);
			v->AvailAmount2 = *(int*)qdb_cell(res,row,9);
			v->g_id = *(int*)qdb_cell(res,row,12);

		     // Free the result
		     qdb_freeresult(res);

		     qdb_disconnect(hdl);
			}
		     return 1;
	}
