#include <entryheader.h>


time_t t;
struct tm *ptr_time;

int database_operations(int action,char *message)
{
    unsigned char temp_str[100];
    char *label_type = NULL;
    int amount1 =0,amount2=0;
    int label=0,val_ret=0;




    if(4 == GetData(message,MSG_ID,temp_str))
         label = GetData(message,IULABEL,temp_str);
    else if(6 == GetData(message,MSG_ID,temp_str))
             label = GetData(message,CASHLABEL,temp_str);
    else if(8 == GetData(message,MSG_ID,temp_str))
             label = GetData(message,CCLABEL,temp_str);

    printf("Label is %d\n", label);
    db->label = label;

    if(action==WRITE)
    {
        if((GetData(message,MSG_ID,temp_str)) == 4)
        {
            amount1 = GetData(message,CASH_DOLLAR,temp_str);
            amount2 = GetData(message,CASH_CENTS,temp_str);
            label_type = "IU";
        }
        else if((GetData(message,MSG_ID,temp_str)) == 6)
        {
            amount1 = GetData(message,CASH_DOLLAR,temp_str);
            amount2 = GetData(message,CASH_CENTS,temp_str);
            label_type = "CA";
        }
        else if((GetData(message,MSG_ID,temp_str)) == 8)
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
	case VALIDATE:			//VALIDATE
			printf("In validate: \n");
			db->label = label;
			//globalstruct.type = label_type; // IU or CA or CO - from the simulator u ll know
			val_ret = DB_ValidateEntry(db); //TEMPORARILY COMMENTED
			//val_ret = -1; //returning this value for testing
			break;
			
	case WRITE:		//WRITE TO DATABASE

		t=time(NULL);
		ptr_time = localtime(&t);
		db->label = label;
		db->type = label_type; // IU or CA or CO - from the simulator u ll know
		db->entry_hr = ptr_time->tm_hour;
		db->entry_mn = ptr_time->tm_min;
		db->AvailAmount1 = amount1;
		db->AvailAmount2 = amount2;
		db->g_id = GetData(message,GANTRY_ID,temp_str);

			val_ret = DB_WriteEntry(db);
			break;

	case READ:		//READ FROM DATABASE
			//val_ret = ReadDatabase(db);
		break;

	default :
	val_ret  = -1;

	}
	
	printf("database operation, value returned is %d, \n",val_ret);
	return val_ret;
}
