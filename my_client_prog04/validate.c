/*
 * validate.c
 *
 *  Created on: Apr 22, 2011
 *      Author: Velu
 */

/*
 * ValidateEntry.c
 *
 *  Created on: Apr 21, 2011
 *      Author: Velu
 */

#include<globalstruct.h>

int DB_ValidateEntry(DB_OP *val)
{
	DB_OP *v =(DB_OP*)val;
	qdb_hdl_t *hdl;
	qdb_result_t *res;
	char *errmsg;
	int rc,row;
	int label;
	int Checkmonth;
	int Currentmonth,Updatemonth;
	int Endmonth;
    label = v->label;
    char try2[3] = "';";
    char try[100] = "SELECT * FROM season WHERE iulabel = '";
   	sprintf(try,"%s%d%s",try,label,try2);
   	printf(" the query = %s\n",try);

	hdl = qdb_connect("/dev/qdb/seasondb", 0);
		if (hdl == NULL)
			{
				fprintf(stderr, "Error connecting to database: %s\n", strerror(errno));
				return EXIT_FAILURE;
			}
	printf(" successfully connected\n");


			// Select a query
	rc = qdb_statement(hdl,try);
	if (rc == -1)
		{
		 	 errmsg = qdb_geterrmsg(hdl);
			 fprintf(stderr, "Error executing SELECT statement: %s\n", errmsg);
			 return EXIT_FAILURE;
	    }
	res = qdb_getresult(hdl); // Get the result
    if (res == NULL)
    	{
			fprintf(stderr, "Error getting result: %s\n", strerror(errno));
			return EXIT_FAILURE;
        }

    row = qdb_rows(res);
	if (row == 0)
		{
			qdb_freeresult(res);
			qdb_disconnect(hdl);
     		return -1;
     	}
   	else
   	{
   		row = row -1 ;

			     // print the result
   		printf("The IU label is : %d\n", *(int *)qdb_cell(res, row, 0));
		printf("The Starting month is  : %d\n", *(int *)qdb_cell(res, row, 1));
		printf("The End month is  : %d\n", *(int *)qdb_cell(res, row, 2));
		printf("The Amount is : %d\n", *(int *)qdb_cell(res, row, 3));
        Endmonth = ((*(int *)qdb_cell(res, row, 2)));
	    Currentmonth = ((v->month)+1);
	    printf(" the Current month is %d\n",Currentmonth);
	    Checkmonth =  Endmonth - Currentmonth;
        printf(" the Check month is %d\n",Checkmonth);
        if (Checkmonth < 0 )
        	{
				if ((Currentmonth == 10)||(Currentmonth == 11)||(Currentmonth == 12))
			    	 {
			    		 printf(" its 10 or 11 or 12 \n");
			    		 Updatemonth = Currentmonth + 3 ;
			    		 	 if(Updatemonth > 12)
			    		 	 {
			    		 		 Updatemonth = Updatemonth - 12;
			    		 		 Updatemonth = Updatemonth - Endmonth;
			    		 		 if(Updatemonth >=0)
			    		 		 {
			    		 			 qdb_disconnect(hdl);
			    		 			 return 1;
			    		 		 }
			    		 	 }
			    	 }

			    qdb_disconnect(hdl);
			    return -1;
        	}
	}
	qdb_disconnect(hdl);
	return 1;
}
