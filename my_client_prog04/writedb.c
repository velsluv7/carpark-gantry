/*
 * writedb.c
 *
 *  Created on: Apr 22, 2011
 *      Author: Velu
 */

#include<globalstruct.h>

int DB_WriteEntry(DB_OP *val)
{
	DB_OP *v =(DB_OP*)val;
	qdb_hdl_t *hdl;
	//qdb_result_t *res;

	int label;
	char *type;
	char *user;
	int ent_hr;
	int ent_min;
	int amt1;
	int amt2;
	int rc;
	//int row;
	int gid;
	char *errmsg;


	char s1[500] = "INSERT INTO optable(label,type,user,entry_hr,entry_mn,AvailAmount1,AvailAmount2,gid) VALUES(";
	char s2[2] = ",";
	char s3[2] = "'";
	char s4[3] = ");";


	label = v->label;
	type  = v->type;
	user = v->user;
	ent_hr = v->entry_hr;
	ent_min = v->entry_mn;
	amt1 = v->AvailAmount1;
	amt2 = v ->AvailAmount2;
	gid = v->g_id;

	sprintf(s1,"%s%d%s%s%s%s%s%s%s%s%s%d%s%d%s%d%s%d%s%d%s",s1,label,s2,s3,type,s3,s2,s3,user,s3,s2,ent_hr,s2,ent_min,s2,amt1,s2,amt2,s2,gid,s4);

	printf(" the query = %s\n",s1);

	// Connect to the database

	hdl = qdb_connect("/dev/qdb/operdb", 0);
		if (hdl == NULL)
		{
			fprintf(stderr, "Error connecting to database: %s\n", strerror(errno));
			return EXIT_FAILURE;
		}
		printf(" successfully connected\n");

	rc = qdb_statement(hdl,s1);
		if (rc == -1)
		{
			 errmsg = qdb_geterrmsg(hdl);
		 	 fprintf(stderr, "Error executing INSERT statement: %s\n", errmsg);
		 	 return EXIT_FAILURE;
	    }

		printf(" successfully inserted in db\n");

		qdb_disconnect(hdl);

    return 1;
}
