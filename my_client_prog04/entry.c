#include<entryheader.h>


int state = 1;


DB_OP globalstruct;
DB_OP *db;

//Functions Used in this program::::::
	

int main(int argc, char *argv[]) {

	name_attach_t *attach;
	int rcvid=0,car1=0,car2=0,state_car1=0,state_car2=0;
	char    message [512];
	unsigned char temp[512]; // big enough for our purposes
	char display [512];
	int count = 0, msg_id = 0;
	pid_t pid_sim;
	pid_sim = getpid();



	
	db = &globalstruct;

	printf("Welcome to the QNX Momentics IDE\n");
	printf("this is application process and the pid = %d\n",pid_sim);

	if ((attach = name_attach(NULL, ATTACH_POINT, 0)) == NULL) {
		 printf("In Photon:: Cannot attach to myname \n");
		 //return EXIT_FAILURE;
	 }

	printf("Before while in Application \n");

	while(1)
	{

			rcvid = MsgReceive (attach ->chid, message, sizeof (message),NULL);
			//*****Call routine here to convert message from whatever format to whatever format********//
			msg_id = GetData(message,MSG_ID,temp); //converting to integer from string (or character array.
	    	//printf ("Application : Got a message from Photon, rcvid is %X\n", rcvid);
			printf ("Application : State is %d \n", state);
			printf ("Application : IN while in Application \"%s\".\n", message);
			//printf ("Application : MEssage ID is %d \n", msg_id);
		if(msg_id==12)
			state = 50;



		switch(state)
		{
			case 0: //state 0 is when the application is waiting for start button to be pressed.
			
			    printf ("Message was \"%s\".\n", message);



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


					printf ("In state 1 and the message was \"%s\".\n", message);
					if((GetData(message,BEFOREAFTER,temp) == 0) && ((GetData(message,SENSORSTATE,temp)) == 1)) //before gantry is 0.
					{
						// now, prepare the reply.  We reuse "message"
						DisplayMessage(state,message,0,1,display); //a special charater will be added to demarcate between message (bound for debug text box in photon and diaplay message
						strcpy (message,"Vehicle present before Gantry01 - Entrance"); //Vehicle present before Gantry01 - Entrance
						//**********Call Display routine by forming appropriate message***********//

						printf ("Display message is \"%s\".\n", display);
						state = 2;

						if(car1 == 0)
				  		car1=1;
						else
						car2 = 1;
					}
					else
					{
						if(GetData(message,BEFOREAFTER,temp) == 0)
						{
						DisplayMessage(state,message,0,2,display); //a special charater will be added to demarcate between message (bound for debug text box in photon and diaplay message
						strcpy (message, "Vehicle not present before Gantry01 - Entrance"); //Vehicle not present before Gantry01 - Entrance
						}
						else
						strcpy (message, "Press Load sensor 1 and not load sensor 2"); //Vehicle not present before Gantry01 - Entrance
					}
					strcat(message,display);
					MsgReply (rcvid, EOK, message, sizeof (message));
				}
				else
				{
				display_default_message(rcvid,message);
				MsgReply (rcvid, EOK, message, sizeof (message));
				}
				break;
			
			case 2: // state 2 is when application is wating IU label message or cash card message or complementary card.
			  	if (((msg_id == 4) | (msg_id == 6) | (msg_id == 8)) && count < 3) //3 chances are give, if all 3 times user cannot provide a correct card, then he/she has to call the operator.
	        	{
					printf ("In state 2 and the message was \"%s\".\n", message);
					switch(msg_id)
					{
						case 4: //this is message id, dont confuse with State.

						if((database_operations(VALIDATE,message)) == -1) //*********************************for hourly users, function returns a -1. database_operations(VALIDATE,message)
						{
							db->user = "H";
						//	printf("In state 2 case 4: %f \n",(float)GetData(message,CASH_DOLLAR,temp));
							if( ((GetData(message,CASH_DOLLAR,temp))) > 3) //OR if season user//type casting the cash returned to int (cash returned is of type char)
							{
								database_operations(WRITE,message); //2 - WRITE ******************************
								DisplayMessage(state,message,CASH_DOLLAR,1,display); //display will return a message saying "Cash available is ...."
								strcpy (message, "IU label validated, cash is available and gantry open"); //IU label validated, cash is available and gantry can be opened: This is same as sending msg 01. Simulator should open the gantry.

								printf("In state 2 and case 4 before of car1 is statecar1:%d and car1 is car1:%d, \n",state_car1,car1);
								printf("In state 2 and case 4 before of car2 is statecar2:%d and car2 is car2:%d, \n",state_car2,car2);

								count = 0;
								if((car1==1) && (car2==1))
								{
									if((car1 == 1) && (state_car1!=6))
									{
										state_car1 = 3;
									}
									else if((car2 == 1) && (state_car2!=6))
									{
										state_car2 = 3;
									}
									state = 6;

								}
								else
								state = 3;

								printf("In state 2 and case 4 after of car1 is statecar1:%d and car1 is car1:%d, \n",state_car1,car1);
								printf("In state 2 and case 4 after of car2 is statecar2:%d and car2 is car2:%d, \n",state_car2,car2);

								printf("good lots of cash :) ha ha,\n");
							}
							else
							{
								count++;
								DisplayMessage(state,message,CASH_DOLLAR,2,display); //display will return a message saying "Insufficient balance, insert cash card ...."
								strcpy (message, "Insufficient balance: Insert cash card"); //Sufficient balance is not available

							}							
						}
						else if((database_operations(VALIDATE,message)) == 1) //for season users, function will return a 1.
						{
								db -> user = "S";
								database_operations(WRITE,message); //****************************************8
								DisplayMessage(state,message,0,3,display); //display will return a message saying "Season User ...."
								strcpy (message, "IU label validated, cash is available and gantry open"); //IU label validated, cash is available and gantry can be opened: This is same as sending msg 01. Simulator should open the gantry.

								count = 0;
								if((car1==1) && (car2==1))
								{
									if((car1 == 1) && (state_car1!=6))
									{
										state_car1 = 3;
									}
									else if((car2 == 1) && (state_car2!=6))
									{
										state_car2 = 3;
									}
									state = 6;

								}
								else
								state = 3;
						}
						else
						{
							DisplayMessage(state,message,IULABEL,4,display); //display will return a message saying "Invalid IU label, insert cash card ...."
							strcpy (message, "Invalid IU label:Insert cash card"); //Invalid IU label

							count++;
						}
						strcat(message,display);
						MsgReply (rcvid, EOK, message, sizeof (message));	
						break;
						
						case 6: //this is message id, dont confuse with State.
						if((database_operations(VALIDATE,message)) == -1) //*********************************
						{
							if( (GetData(message,CASH_DOLLAR,temp)) > 3)
							{
								db->user = "H";
								database_operations(WRITE,message); //********************************
								DisplayMessage(state,message,CASH_DOLLAR,1,display); //display will return a message saying "Cash available is ...."
								strcpy (message, "IU label validated, cash is available and gantry open"); //Cash card label validated, cash is available and gantry can be opened: Send msg 01.

								count = 0;
								if((car1==1) && (car2==1))
								{
									if((car1 == 1) && (state_car1!=6))
									{
										state_car1 = 3;
									}
									else if((car2 == 1) && (state_car2!=6))
									{
										state_car2 = 3;
									}
									state = 6;

								}
								else
								state = 3;
							}
							else
							{
								count++;
								DisplayMessage(state,message,CASH_DOLLAR,2,display); //display will return a message saying "Insufficient balance in cash card ...."
								strcpy (message, "IU label validated, cash is available and gantry open"); //Sufficient balance is not available

							}							
						}
						else if((database_operations(VALIDATE,message)) == 1) //for season users, function will return a 1.
						{
								globalstruct.user = "S";
								database_operations(WRITE,message); //*****************************
								DisplayMessage(state,message,0,3,display); //display will return a message saying "Season User ...."
								strcpy (message, "Season user:IU label validated,gantry open"); //IU label validated, cash is available and gantry can be opened: This is same as sending msg 01. Simulator should open the gantry.

								count = 0;
								if((car1==1) && (car2==1))
								{
									if((car1 == 1) && (state_car1!=6))
									{
										state_car1 = 3;
									}
									else if((car2 == 1) && (state_car2!=6))
									{
										state_car2 = 3;
									}
									state = 6;

								}
								else
								state = 3;
						}
						else
						{
							DisplayMessage(state,message,CASHLABEL,4,display); //display will return a message saying "Invalid cash card label ...."
							strcpy (message, "Invalid cash card"); //Invalid Cash card label

							count++;
						}
						strcat(message,display);
						MsgReply (rcvid, EOK, message, sizeof (message));	
						break;						
						
						case 8: //this is message id, dont confuse with State.
						if((database_operations(VALIDATE,message)) == 1) //for complementary users, label must be present in the database.
						{
								db->user = "S";
								database_operations(WRITE,message); //**********************************8888
								DisplayMessage(state,message,CCLABEL,5,display); //display will return a message saying "Complementary card is validated ...."
								strcpy (message, "Complementary card label validated, gantry can now be opened:"); //Complementary card label validated, gantry can now be opened:

								count = 0;
								if((car1==1) && (car2==1))
								{
									if((car1 == 1) && (state_car1!=6))
									{
										state_car1 = 3;
									}
									else if((car2 == 1) && (state_car2!=6))
									{
										state_car2 = 3;
									}
									state = 6;

								}
								else
								state = 3;									
						}
						else
						{
							DisplayMessage(state,message,CCLABEL,4,display); //display will return a message saying "Invalid comple card label ...."
							strcpy (message, "Invalid complementary card label"); //Invalid complementary card label

							count++;
						}
						strcat(message,display);
						MsgReply (rcvid, EOK, message, sizeof (message));	
						break;						
						
					}
			

				}
			  	else if(  (msg_id == 2) && ((car1 == 1) || (car2 == 1)) && (GetData(message,BEFOREAFTER,temp) ==1)    ) //should be a after message
			  	{
			  		if((car1==1) && (car2==1))
			  		{
			  			if((car1 == 1) && (state_car1 == 6))
			  			{
							DisplayMessage(6,message,0,1,display);
							strcpy (message,"NO vehicle present after Gantry01"); //NO vehicle present after Gantry01 - Entrance, send msg 01 to close gantry to simulator.
			  				state_car1 = 0;
			  				state_car2 = 2;
			  				car1 = 0;
			  			}
			  			else if((car2 == 1) && (state_car2 == 6))
			  			{
							DisplayMessage(6,message,0,1,display);
							strcpy (message,"NO vehicle present after Gantry01"); //NO vehicle present after Gantry01 - Entrance, send msg 01 to close gantry to simulator.
			  				state_car2 = 0;
			  				state_car1 = 2;
			  				car2 = 0;
			  			}
			  			else
			  			{
			  				display_default_message(rcvid,message);
			  				MsgReply (rcvid, EOK, message, sizeof (message));
			  			}
			  			state = 2;
					}
					else
					state = 2;

					strcat(message,display);
					MsgReply (rcvid, EOK, message, sizeof (message));
					printf("In 2 state of car1 is statecar1:%d and car1 is car1:%d, \n",state_car1,car1);
					printf("In 2 state of car2 is statecar2:%d and car2 is car2:%d, \n",state_car2,car2);


			  	}
				else
				{
					if(count < 3)
					{
						display_default_message(rcvid,message);
						MsgReply (rcvid, EOK, message, sizeof (message));
					}
					else
					{
						count = 0;
						state = 50; //just set the state where the user has to call operator
						//NOT NEEDED errorhandler(call); //have to decide parameters to error handler. Here calling the opearator is handled.
					}
				}				
				break;
			
			
			case 3: //Wait for obstacle sensor to go high
			  	if (msg_id == 3) 
	        	{
					printf ("In state 3 and the message was \"%s\".\n", message);
					if(GetData(message,SENSORSTATE,temp)==1) //if obstacle sensor is high go to next state and wait for load sensor to go high.
					{
						
						DisplayMessage(state,message,0,1,display);
						strcpy (message, "Obstacle sensor high"); //Obstacle sensor high
				
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
	  			MsgReply (rcvid, EOK, message, sizeof (message));
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
						if(GetData(message,BEFOREAFTER,temp) ==1)
						{
						DisplayMessage(state,message,0,2,display);
						strcpy (message,"Vehicle has not yet crossed Gantry01"); //Vehicle not present after Gantry01 - Entrance
						}
						else
						{
						strcpy (message,"Wrong load sensor is pressed. Press Load sensor 2");
						}
					
					}
					strcat(message,display);
					MsgReply (rcvid, EOK, message, sizeof (message));
				}
				else
				{
				display_default_message(rcvid,message);
	  			MsgReply (rcvid, EOK, message, sizeof (message));
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
	  			MsgReply (rcvid, EOK, message, sizeof (message));
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

						if(car1 == 1)
						{
							car1=0;
							state_car1 = 0;
						}
						else if(car2 == 1)
						{
							state_car2 = 0;
							car2=0;
						}

						if((state_car1) ==3 || (state_car2==3))
						state = 3;
						else
						state = 1; //again wait for start to be pressed.

						printf("state of car1 is %d, \n",state_car1);
						printf("state of car2 is %d, \n",state_car2);

					}
					else if((GetData(message,BEFOREAFTER,temp) ==0) && (GetData(message,SENSORSTATE,temp)==1) && (state_car1!=3 || state_car2!=3))
					{

						// now, prepare the reply.  We reuse "message"
						DisplayMessage(1,message,0,1,display); //a special charater will be added to demarcate between message (bound for debug text box in photon and diaplay message

						if(car1 == 1)
						{
							car2 = 1;
							state_car1 = 6;
						}
						else if(car2 == 1)
						{
							car1 = 1;
							state_car2 = 6;
						}
						state = 2;
						printf("state of car1 is statecar1:%d and car1 is car1:%d, \n",state_car1,car1);
						printf("state of car2 is statecar2:%d and car2 is car2:%d, \n",state_car2,car2);

						strcpy (message,"Another vehicle present before Gantry01 - Entrance"); //Another vehicle present before Gantry01 - Entrance
						//**********Call Display routine by forming appropriate message***********//

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
	  			MsgReply (rcvid, EOK, message, sizeof (message));
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

						car2 = 0;			//just resetting everything. dont care about state of car1 and car2 :)
						car1 = 0;
						state_car1 = 0;
						state_car2 = 0;

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
			  	{
			  		display_default_message(rcvid,message);
			  		MsgReply (rcvid, EOK, message, sizeof (message));
				}
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
			  	{
			  		display_default_message(rcvid,message);
			  		MsgReply (rcvid, EOK, message, sizeof (message));
			  	}
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

int display_default_message(int rcvid,char* message)
{
        		strcpy (message,"Could not decode message or $ not expecting this message");
        		//MsgReply (rcvid, EOK, message, sizeof (message));
				printf("Indefault msg \n");
				printf("Default Message is %s, \n",message);
				return 1;
}



























