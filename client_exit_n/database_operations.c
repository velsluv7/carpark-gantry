/*
 * database_operations.c
 *
 *  Created on: Apr 22, 2011
 *      Author: Nishin
 */
#include "exit_top_header.h"

extern int database_operations(int action,char *message)
{
	unsigned char temp_str[100];
	char *label_type;
	int amount1,amount2,msgid;
	int label=0,val_ret=0;

	msgid = GetData(message,MSG_ID,temp_str);

    if(4 == msgid)
        label = GetData(message,IULABEL,temp_str);
    else if(6 == msgid)
        label = GetData(message,CASHLABEL,temp_str);
    else if(8 == msgid)
        label = GetData(message,CCLABEL,temp_str);

    printf("Label is %d\n", label);
    db->label = label;

    if(action==WRITE)
    {
		if(msgid == 4)
        {
            amount1 = GetData(message,CASH_DOLLAR,temp_str);
            amount2 = GetData(message,CASH_CENTS,temp_str);
            label_type = "IU";
		}
        else if(msgid == 6)
        {
		    amount1 = GetData(message,CASH_DOLLAR,temp_str);
            amount2 = GetData(message,CASH_CENTS,temp_str);
			label_type = "CA";
		}
        else if(msgid == 8)
        {
			amount1 = 0;
            amount2 = 0;
			label_type = "CO";
		}
    }
    else
    {
    }
	switch(action)
	{
        case VALIDATE:			
            //printf("In validate: \n");
            // globalstruct->label = label;
            DB_ValidateExit(db);
            printf(" label is %x \n",db->label);
            label_type = db->user;
            //globalstruct->entry_hr = 10;
            //globalstruct->entry_mn = 50;
            if(msgid == 4)
            {
				if(label_type[0] == 'H')
				{
					printf(" \n Hourly user \n ");
					val_ret = -1; //returning this value for testing
				}
				else
				{
					printf(" \n Season user \n ");
					val_ret =  1;
				}
            }
            break;


        default :
            val_ret  = 999;
        break;

	}

	printf("database operation, value returned is %d, \n",val_ret);
	return val_ret;
}
