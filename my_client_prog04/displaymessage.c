#include <entryheader.h>


void DisplayMessage(int state1,char *message,int data_selector,int case_selector_indisplay,char *return_string)
{
	char finalmsg[512],temp_disp[200];
	//printf("In display \n");
	//if(state1 != 2) //not required now, noe itsjust debugmsg$displaymsg.
	strcpy(finalmsg,DEMARCATE); //only in state 2 we may need to add Gantry 01 message for sashi to find out whether insufficient balance or IU validation failed.
	//printf("In display after copying demarcate \n");
	switch(state1)
	{
		case 1:
			printf("In display case 1 \n");
			if(case_selector_indisplay == 1)
			{
				strcat(finalmsg,"Welcome to Carpark");
			}
			else if(case_selector_indisplay == 2) 
			{
				strcat(finalmsg,"Gantry 01");
			}
		break;
		

		case 2:

			//sprintf(temp_disp, "%f", (((float)GetData(message,CASH,temp_disp))/10));
			sprintf(temp_disp,"%d.%d",(GetData(message,CASH_DOLLAR,(unsigned char *)temp_disp)),(GetData(message,CASH_CENTS,(unsigned char *)temp_disp)));
			if(case_selector_indisplay == 1)
			{
				//printf("In Display Cash available is: \n");
				strcat(finalmsg,"Cash available is:");
				strcat(finalmsg,temp_disp);
			}
			else if(case_selector_indisplay == 2) 
			{
				//strcpy(finalmsg,"CashFail");
				//strcat(finalmsg,DEMARCATE);
				strcat(finalmsg,"Insufficient Balance:");
				strcat(finalmsg,temp_disp);
			}
			else if(case_selector_indisplay == 3)
			{
				strcat(finalmsg,"Welcome season user:");
			}
			else if(case_selector_indisplay == 4)
			{
				//strcpy(finalmsg,"LabelFail");
				//strcat(finalmsg,DEMARCATE);
				
				if(GetData(message,MSG_ID,(unsigned char *)temp_disp)==4)
				strcat(finalmsg,"IU validation failed: Insert Cash card");
				if(GetData(message,MSG_ID,(unsigned char *)temp_disp)==6)
				strcat(finalmsg,"Cash card validation failed:");
				if(GetData(message,MSG_ID,(unsigned char *)temp_disp)==8)
				strcat(finalmsg,"Complementary card validation failed:");
			}
			else if(case_selector_indisplay == 5)
			{
				strcat(finalmsg,"Welcome guest:");
			}
		break;

		case 3:
			if(case_selector_indisplay == 1)
			{
				strcat(finalmsg,"Please wait...");
				//strcat(finalmsg,temp_disp);
			}
			else if(case_selector_indisplay == 2) 
			{
				strcat(finalmsg,"Please proceed....");
				//strcat(finalmsg,temp_disp);
			}
			break;

		case 4:
			if(case_selector_indisplay == 1)
			{
				strcat(finalmsg,"Please wait...");
				//strcat(finalmsg,temp_disp);
			}
			else if(case_selector_indisplay == 2) 
			{
				strcat(finalmsg,"Please proceed....");
				//strcat(finalmsg,temp_disp);
			}
			break;

		case 5:
			if(case_selector_indisplay == 1)
			{
				strcat(finalmsg,"Please proceed");
				//strcat(finalmsg,temp_disp);
			}
			else if(case_selector_indisplay == 2) 
			{
				strcat(finalmsg,"Please wait....");
				//strcat(finalmsg,temp_disp);
			}
			break;			
		
		case 6:
			if(case_selector_indisplay == 1)
			{
				strcat(finalmsg,"Please proceed");
				//strcat(finalmsg,temp_disp);
			}
			else if(case_selector_indisplay == 2) 
			{
				strcat(finalmsg,"Please wait....");
				//strcat(finalmsg,temp_disp);
			}
			break;

		case 50:
			if(case_selector_indisplay == 1)
			{
				strcat(finalmsg,"Wait for operator to authorize entry:");
				//strcat(finalmsg,temp_disp);
			}
			else if(case_selector_indisplay == 2)
			{
				strcat(finalmsg,"Press voice intercom and speak to operator:");
				//strcat(finalmsg,temp_disp);
			}
			break;

		case 51:
			if(case_selector_indisplay == 1)
			{
				strcat(finalmsg,"Entry authorized:");
				//strcat(finalmsg,temp_disp);
			}
			else if(case_selector_indisplay == 2)
			{
				strcat(finalmsg,"Entry not authorized:");
				//strcat(finalmsg,temp_disp);
			}
			break;

		default:
			strcat(finalmsg,"Dont know what to send....");
			//strcat(finalmsg,temp_disp);
	}
	strcpy(return_string,finalmsg);
	printf("String that will be displayed is %s, \n",return_string);
}
