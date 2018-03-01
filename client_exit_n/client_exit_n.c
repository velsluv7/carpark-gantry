
#include "exit_top_header.h"

DB_OP *db;
DB_OP globalstruct;

int state = 1;


int main(int argc, char *argv[]) 
{
    name_attach_t *attach;
    int rcvid;
    unsigned char temp[50],temp1[50];
    char    message [512]; // big enough for our purposes
    char    cashmessage [50];
    char display [512];
    int count = 0, msg_id = 0;
    pid_t pid_sim;
    pid_sim = getpid();
    //DB_OP localDB;
   // DB_OP *localstruct;
    Message_Data Data_To_Send;
    //Message_Data msgtobesent;
    db = &globalstruct;
    printf("Welcome to the QNX Momentics IDE\n");
    printf("this is application process and the pid = %d\n",pid_sim);

    if ((attach = name_attach(NULL, ATTACH_POINT, 0)) == NULL) 
    {
        printf("In Photon:: Cannot attach to ATTACH_POINT \n");
        //return EXIT_FAILURE;
    }

    printf("Before while in Application \n");

    while(1)
    {
        printf ("Application : State is %d \n", state);
        rcvid = MsgReceive (attach->chid, message, sizeof (message),NULL);
        //*****Call routine here to convert message from whatever format to whatever format********//
        msg_id = GetData(message,MSG_ID,temp); //converting to integer from string
        printf ("Application : Got a message from Photon, rcvid is %X\n", rcvid);
        printf ("Application : IN while in Application \"%s\".\n", message);
        printf ("Application : MEssage ID is %d \n", msg_id);

        if(msg_id == 16)
        {
			Data_To_Send.msgid = 5;
			Data_To_Send.gantryid = 0x01;
			Data_To_Send.label = 0;
			Data_To_Send.entry_hr = 0;
			Data_To_Send.entry_min = 0;
			Data_To_Send.exit_hr = 0;
			Data_To_Send.exit_min =0;
			Data_To_Send.dollar_avail = 0;
			Data_To_Send.cents_avail = 0;
			Data_To_Send.dollar_deduct = 0;
			Data_To_Send.cents_deduct = 0;
			FormData(&Data_To_Send,TO_GANTRY,temp1);

			printf("\n\nFrom the application side %x %x \n\n",temp1[0],temp1[1]);
			MsgReply (rcvid, EOK, temp1, sizeof (temp1));
            if(GetData(message,FROM_BCS,temp)==1)
            {
               printf("Fire \n");
               DeleteAll();
            }
            else if(GetData(message,FROM_BCS,temp)==2)
            {
               printf("Power \n");
            }
            else
            {
            	printf("\n");
            }
        	state = 1;
        }
        switch(state)
        {
            case 0: //state 0 is when the application is waiting for start button to be pressed.
            
                printf ("Message was \"%x %x\".\n", message[0],message[1]);
                printf("Comparision result is %d, \n",(strcmp(message,"Application can now start")));
                if((strcmp(message,"Application can now start"))==0) //this is required is nameclose function is used in "start.c" GetData(message,beforeafter) (GetData(message,sensorstate) GetData(message,Cash)
                {
                	state = 1;
                	strcpy (message,"Application will now begin:");
                }
                else
                	strcpy (message,"Push Start to begin:");
                
                MsgReply (rcvid, EOK, message, sizeof (message));
            break;

            case 1: // state 1 is when application is wating for car to be sensed.
                if (msg_id == 2) //this can chage depending on how the message is decoded
                {
                	printf ("Message was \"%x %x\".\n", message[0],message[1]);
                	if((GetData(message,BEFOREAFTER,temp) == 0) && ((GetData(message,SENSORSTATE,temp)) == 1)) //before gantry is 0.
                	{
                		// now, prepare the reply.  We reuse "message"
                		DisplayMessage(state,message,0,1,display); //a special charater will be added to demarcate between message (bound for debug text box in photon and diaplay message
                		strcpy (message,"Vehicle present before Gantry01 - Entrance"); //Vehicle present before Gantry01 - Entrance
                		//**********Call Display routine by forming appropriate message***********//

                		printf ("Display message is \"%s\".\n", display);
                		state = 2;
                }
                else
                {
                	DisplayMessage(state,message,0,2,display); //a special charater will be added to demarcate between message (bound for debug text box in photon and diaplay message
                	strcpy (message, "Vehicle not present before Gantry01 - Entrance"); //Vehicle not present before Gantry01 - Entrance
                }
				strcat(message,display);
				MsgReply (rcvid, EOK, message, sizeof (message));
                }
                else
                {
                    display_default_message(rcvid,message);
                }
            break;

            case 2: // state 2 is when application is wating IU label message or cash card message or complementary card.
                if (((msg_id == 4) | (msg_id == 6) | (msg_id == 8)) && count < 3) //3 chances are give, if all 3 times user cannot provide a correct card, then he/she has to call the operator.
                {
                    printf ("In state 2 and the message was \"%s\". Msg id is %d\n", message,msg_id);
                    switch(msg_id)
                    {
                        case 4: //this is message id, dont confuse with State.

                        if((database_operations(VALIDATE,message)) == -1) //for hourly users, function returns a -1. database_operations(VALIDATE,message)
                        {
                            /* Obtain the entry time and exit time */
                            /* Cash charge 1 cents / 1 minute  */
                            /* Exit time is obtained from the current time */
                            printf("In the case 4 for hourly user \n");
                            //database_operations(READ,message); /* This function will populate the data from the database*/
                            //localstruct = db;

                            printf("In the case 4 for hourly user before charge calculation \n");
                            /* Will calculate the charge and populate the remaining fields */
                            calc_charge_time(db);
                            printf("In the case 4 for hourly user after charge calculation \n");
                            //display will return a message saying "Cash available is ...."


                            /* To antenna unit - message */
                            /* Send message for Gantry open */                            
                            /* Send message for Display */
                            // globalstruct = localstruct;
                            //database_operations(WRITE,message);
                            /*
                            Data_To_Send.msgid = 11;
                            Data_To_Send.gantryid = 0x01;
                            Data_To_Send.label = db->label;
                            Data_To_Send.entry_hr = db->entry_hr;
                            Data_To_Send.entry_min = db->entry_mn;
                            Data_To_Send.exit_hr = db->exit_hr;
                            Data_To_Send.exit_min = db->exit_mn;
                            Data_To_Send.dollar_avail = db->AvailAmount1;
                            Data_To_Send.cents_avail = db->AvailAmount2;
                            Data_To_Send.dollar_deduct = db->DeductAmount1;
                            Data_To_Send.cents_deduct = db->DeductAmount2;*/
                            Data_To_Send.msgid = 5;
                            Data_To_Send.gantryid = 0x01;
                            Data_To_Send.label = 0;
                            Data_To_Send.entry_hr = 0;
                            Data_To_Send.entry_min = 0;
                            Data_To_Send.exit_hr = 0;
                            Data_To_Send.exit_min =0;
                            Data_To_Send.dollar_avail = 0;
                            Data_To_Send.cents_avail = 0;
                            Data_To_Send.dollar_deduct = db->DeductAmount1;
                            Data_To_Send.cents_deduct = db->DeductAmount2;
                            FormData(&Data_To_Send,TO_ANTENNA,temp1);
                            //strcat(message,display);
                            printf("\n\nFrom the application side %x %x %x\n\n",temp1[0],temp1[1],temp1[2]);
                            MsgReply (rcvid, EOK, temp1, sizeof (temp1));


                            sleep(1);
                            rcvid = MsgReceive (attach->chid, message, sizeof (message),NULL);
                            //*****Call routine here to convert message from whatever format to whatever format********//
                            msg_id = GetData(message,MSG_ID,temp); //converting to integer from string (or character array.
                            printf ("Application : Got a message from Photon, rcvid is %X\n", rcvid);

                            printf ("Application : MEssage ID is %d \n", msg_id);

                            memset(&message[0],0,sizeof(message));
                            strcpy(message,"Gantry Open");
                            DisplayMessage(state,message,CASH_DOLLAR,1,display);
                            strcat(message,display);
                            printf("Cash deducted is %d.%d\n",db->DeductAmount1,db->DeductAmount1);
                            sprintf(cashmessage," %d.%d",db->DeductAmount1,db->DeductAmount2);
                            strcat(message,cashmessage);
                            MsgReply (rcvid, EOK, message, sizeof (message));
                            count = 0;
                            state = 3;
                        }
                        else if((database_operations(VALIDATE,message)) == 1) //for season users, function will return a 1.
                        {
                            //database_operations(READ,message);
                            //localstruct = db;
                            /* Exit time is obtained from the current time */
                            calc_charge_time(db);
                            /* To antenna unit - message */
                            
                            MsgReply (rcvid, EOK, temp1, sizeof (temp1));

                            DisplayMessage(state,message,CASH_DOLLAR,1,display);
                            sleep(1);
                            rcvid = MsgReceive (attach->chid, message, sizeof (message),NULL);
                            //*****Call routine here to convert message from whatever format to whatever format********//
                            msg_id = GetData(message,MSG_ID,temp); //converting to integer from string (or character array.
                            printf ("Application : Got a message from Photon, rcvid is %X\n", rcvid);

                            printf ("Application : MEssage ID is %d \n", msg_id);
                            /* Send message for Gantry open */                            
                            /* Send message for Display */
                            DisplayMessage(state,message,0,3,display); //display will return a message saying "Season User ...."
                            printf ("Season user:IU label validated, gantry to open"); //IU label validated, cash is available and gantry can be opened: This is same as sending msg 01. Simulator should open the gantry.
                            strcpy(message,"Gantry Open");
                            count = 0;
                            state = 3;
                            strcat(message,display);
                            MsgReply (rcvid, EOK, message, sizeof (message));
                        }
                        else
                        {
                            DisplayMessage(state,message,IULABEL,4,display); //display will return a message saying "Invalid IU label, insert cash card ...."
                            strcpy (message, "Invalid IU label:Insert cash card"); //Invalid IU label

                            count++;
                            strcat(message,display);
                            MsgReply (rcvid, EOK, message, sizeof (message));
                        }
                        break;

                        case 6: //this is message id, dont confuse with State.
                            //if((database_operations(VALIDATE,message)) == -1)
                            {
                            	printf("\n Welcome Cash card user \n");
                            	database_operations(VALIDATE,message);
                                /* Obtain the entry time and exit time */
                                /* Cash charge 1 cents / 1 minute  */
                                /* Exit time is obtained from the current time */
                                //database_operations(READ,message); /* Not reqd nw as it is taken care of in validate */
                                //localstruct = db;
                                /* Will calculate the charge and populate the remaining fields */
                            	calc_charge_time(db);

                                Data_To_Send.msgid = 7;
                                Data_To_Send.gantryid = db->g_id;
                                printf("\n Gantry id is %d \n",db->g_id);
                                Data_To_Send.label = 0;
                                Data_To_Send.entry_hr = 0;
                                Data_To_Send.entry_min = 0;
                                Data_To_Send.exit_hr = 0;
                                Data_To_Send.exit_min =0;
                                Data_To_Send.dollar_avail = 0;
                                Data_To_Send.cents_avail = 0;
                                Data_To_Send.dollar_deduct = db->DeductAmount1;
                                Data_To_Send.cents_deduct = db->DeductAmount2;
                                FormData(&Data_To_Send,TO_CCREADER,temp1);
                                //strcat(message,display);
                                printf("\n\nFrom the application side %x %x %x\n\n",temp1[0],temp1[1],temp1[2]);
                                MsgReply (rcvid, EOK, temp1, sizeof (temp1));

                                sleep(1);

                                rcvid = MsgReceive (attach->chid, message, sizeof (message),NULL);
                                //*****Call routine here to convert message from whatever format to whatever format********//
                                msg_id = GetData(message,MSG_ID,temp); //converting to integer from string (or character array.
                                printf ("Application : Got a message from Photon, rcvid is %X\n", rcvid);

                                printf ("Application : MEssage ID is %d \n", msg_id);


                                strcpy(message,"Gantry Open");
                                DisplayMessage(state,message,CASH_DOLLAR,1,display);
                                strcat(message,display);
                                printf("Cash deducted is %d.%d\n",db->DeductAmount1,db->DeductAmount2);
                                sprintf(cashmessage,"%d.%d",db->DeductAmount1,db->DeductAmount2);
                                strcat(message,cashmessage);
                                MsgReply (rcvid, EOK, message, sizeof (message));
                                count = 0;
                                state = 3;
                            }
                        break;

                        case 8: //this is message id, dont confuse with State.
                            if((database_operations(VALIDATE,message)) == 1) //for complementary users, label must be present in the database.
                            {
                                //database_operations(READ,message);
                                //localstruct = db;
                                /* Exit time is obtained from the current time */
                               // cash_charge = calc_charge_time();
                                /* To antenna unit - message */

                                /* Send message for Gantry open */                            
                                /* Send message for Display */
                                DisplayMessage(state,message,CCLABEL,5,display); 					   
                                count = 0;
                                state = 3;
                                strcat(message,display);
                                MsgReply (rcvid, EOK, message, sizeof (message));
                            }
                            else
                            {
                                DisplayMessage(state,message,CCLABEL,4,display); //display will return a message saying "Invalid comple card label ...."
                                strcpy (message, "Invalid complementary card label"); //Invalid complementary card label
                                count++;
                                strcat(message,display);
                                MsgReply (rcvid, EOK, message, sizeof (message));
                            }

                        break;

                    }
                }
                else
                {
                    if(count < 3)
                    {
                        display_default_message(rcvid,message);
                    }
                    else
                    {
                        count = 0;
                        state = 50; //just set the state where the user has to call operator
                        //NOT NEEDED errorhandler(call); //have to decide parameters to error handler. Here calling the opearator is handled.
                    }
                }
            break;

            case 3:
                /* Wait for obstacle sensor to go high or check for ticket dispenser */
                if (msg_id == 17)
                {
                    printf ("In state 3 and the message s from ticket dispenser \"%x %x\".\n", message[0],message[1]);

                    Data_To_Send.msgid = 11;
                    Data_To_Send.gantryid = db->g_id;
                    Data_To_Send.label = db->label;
                    Data_To_Send.entry_hr = db->entry_hr;
                    Data_To_Send.entry_min = db->entry_mn;
                    Data_To_Send.exit_hr = db->exit_hr;
                    Data_To_Send.exit_min = db->exit_mn;
                    Data_To_Send.dollar_avail = db->AvailAmount1;
                    Data_To_Send.cents_avail = db->AvailAmount2;
                    Data_To_Send.dollar_deduct = db->DeductAmount1;
                    Data_To_Send.cents_deduct = db->DeductAmount2;
                    FormData(&Data_To_Send,TO_TICKET,temp1);
                    MsgReply (rcvid, EOK, temp1, sizeof (temp1));
                    state = 3;
                }
                else if (msg_id == 3)
                {
                    printf ("In state 3 and the message was \"%s\".\n", message);
                    if(GetData(message,SENSORSTATE,temp)==1) //if obstacle sensor is high go to next state and wait for load sensor to go high.
                    {

                        DisplayMessage(state,message,0,1,display);
                        strcpy (message, "Obstacle sensor high"); //Obstacle sensor high
                        DB_DeleteLabel(db);
                        state = 4;
                    }
                    else
                    {
                        DisplayMessage(state,message,0,2,display);
                        strcpy (message, "Vehicle has not yet reached under the gantry arm"); //Vehicle has not yet reached under the gantry arm.
                    }
                    strcat(message,display);
                    MsgReply (rcvid, EOK, message, sizeof (message));
                }
                else
                {
                    display_default_message(rcvid,message);
                }
            break;

            case 4: // waiting for load sensor after gantry.
                if (msg_id == 2)
                {
                    printf ("In state 4 and the message was \"%s\".\n", message);
                    if((GetData(message,BEFOREAFTER,temp) ==1) && (GetData(message,SENSORSTATE,temp)==1)) //after gantry is 1.
                    {
                        DisplayMessage(state,message,0,1,display);
                        strcpy (message,"Vehicle present after Gantry01"); //Vehicle present after Gantry01 - Entrance
                        state = 5;
                    }
                    else
                    {
                        DisplayMessage(state,message,0,2,display);
                        strcpy (message,"Vehicle not present after Gantry01"); //Vehicle not present after Gantry01 - Entrance
                    }
                    strcat(message,display);
                    MsgReply (rcvid, EOK, message, sizeof (message));
                }
                else
                {
                    display_default_message(rcvid,message);
                }
            break;

            case 5: //Wait for obstacle sensor to go low
                if (msg_id == 3)
                {
                    printf ("In state 5 and the message was \"%s\".\n", message);
                    if((GetData(message,SENSORSTATE,temp))==0) //if obstacle sensor is low go to next state and wait for load sensor to go low.
                    {
                        DisplayMessage(state,message,0,1,display);
                        strcpy (message,"Obstacle sensor low"); //Obstacle sensor low
                        state = 6;
                    }
                    else
                    {
                        DisplayMessage(state,message,0,2,display);
                        strcpy (message,"Vehicle is still under the gantry arm"); //Vehicle is still under the gantry arm.
                    }
                    strcat(message,display);
                    MsgReply (rcvid, EOK, message, sizeof (message));
                    }
                    else
                    {
                        display_default_message(rcvid,message);
                    }
            break;

            case 6: // waiting for load sensor to go LOW after gantry.
                if (msg_id == 2)
                {
                    printf ("In state 6 and the message was \"%s\".\n", message);
                    if((GetData(message,BEFOREAFTER,temp) ==1) && (GetData(message,SENSORSTATE,temp)==0)) //'after' gantry is 1.
                    {
                        DisplayMessage(state,message,0,1,display);
                        strcpy (message,"NO vehicle present after Gantry01"); //NO vehicle present after Gantry01 - Entrance, send msg 01 to close gantry to simulator.
                        state = 1; //again wait for start to be pressed.
                    }
                    else
                    {
                        DisplayMessage(state,message,0,2,display);
                        strcpy (message,"Vehicle still present after Gantry01"); //Vehicle still present after Gantry01 - Entrance
                    }
                    strcat(message,display);
                    MsgReply (rcvid, EOK, message, sizeof (message));
                }
                else
                {
                display_default_message(rcvid,message);
                }
            break;


            case 50: // this state if for operator support panel. MSG ID 12 even thou says it goes "to" operator support panel when user presses button,
            //input is taken from the simulator as this is a user action. MSG ID 13 which is a response from the operator support panel is also got from simulator.
            // But for "to display" application directly sends it internally, as display input is given by the application.
                if (msg_id == 12)
                {
                    if((GetData(message,BUTTONSTATE,temp)) == 1)
                    {
                        DisplayMessage(state,message,0,1,display); //display will return a message saying "Wait for operator to authorize ...."
                        strcpy (message, "Voice intercom activated, speak and wait for operator to authorize entry");
                        state = 51;
                    }
                    else
                    {
                        DisplayMessage(state,message,0,2,display); //display will return a message saying "Speak to operator ...."
                        strcpy (message, "Push voice intercom and speak to operator to authorize entry");

                    }
                    MsgReply (rcvid, EOK, message, sizeof (message));
                }
                else
                    display_default_message(rcvid,message);
            break;

            case 51: // this state is to get authority from operator to get entry.
                if (msg_id == 13)
                {
                    if((GetData(message,GANTRYOPERATION,temp)) == 1)
                    {
                        DisplayMessage(state,message,0,1,display); //display will return a message saying "Entry authorized, ...."
                        strcpy (message, "Authorized entry, wait for gantry to open"); //send msg 01 to open gantry
                        state = 3; //wait for car to pass obstacle sensor and load sensor after Gantry.
                    }
                    else
                    {
                        DisplayMessage(state,message,0,2,display); //display will return a message saying "Entry not authorized ...."
                        strcpy (message, "Wait for operator to authorize entry");
                    }
                    MsgReply (rcvid, EOK, message, sizeof (message));
                }
                else
                    display_default_message(rcvid,message);
                break;

            default:
                strcpy (message, "**** Could not decode message or wrong message");
                MsgReply (rcvid, EOK, message, sizeof (message));
                printf("before default msg \n");
        }
    }


    name_detach(attach, 0);
    return EXIT_SUCCESS;
}

void display_default_message(int rcvid,char *message)
{
    strcpy (message, "Could not decode message or not expecting this message");
    MsgReply (rcvid, EOK, message, sizeof (message));
    printf("Indefault msg \n");
}

int calc_charge_time(DB_OP *localstruct)
{
    struct tm *p;
    time_t t;
    int total_hours,total_min,cash_charge,temp,temp1,temp2;
    char *user;

    t=time(NULL);
    ctime(&t);
    p = localtime(&t);

    localstruct->exit_hr = p->tm_hour;
    localstruct->exit_mn = p->tm_min;
    user = localstruct->user;
    if(user[0]!='S')
    {
        total_hours =  localstruct->exit_hr - localstruct->entry_hr;
        printf("Entry hour = %d; Exit hour = %d",localstruct->entry_hr,localstruct->exit_hr);
        printf("Entry min = %d; Exit min = %d",localstruct->entry_mn,localstruct->exit_mn);
        if(total_hours<0)
        {
            total_hours = 24 - localstruct->entry_hr;
            total_hours += localstruct->exit_hr - 0;
        }
        total_min = (localstruct->exit_mn - 0)+(60 - localstruct->entry_mn);

        if(total_hours!=0)
        {
            printf("\n total hours = %d\n",total_hours);
            cash_charge = (total_hours-1)*60+total_min*1;
        }
        else
        {
        	cash_charge = total_min*1;
        }

        temp = cash_charge % 10;
        localstruct->DeductAmount1 = cash_charge/100;
        localstruct->DeductAmount2 = (cash_charge%100)-temp;
        temp1 = cash_charge;
        temp1 = temp1 + localstruct->DeductAmount2; /* Total Deduct amount */
        temp2 = localstruct->AvailAmount1;
        temp2 = temp2 * 100;
        temp2 = temp2 + localstruct->AvailAmount2;
        temp2 = temp2 - cash_charge;
        localstruct->AvailAmount1 = temp2/100;
        temp = temp2%10;
        localstruct->AvailAmount2 = (temp2%100)-temp;

        printf("\n\nThe charge is %d.%d\n",cash_charge/100,cash_charge%100);
    }
    else
    {

    }
    return 0;
}

