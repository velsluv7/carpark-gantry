// This is the main header file used in entry 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>
#include <process.h>
#include <math.h>
#include<globalstruct.h>



#define ATTACH_POINT "EntrG01"
#define TRUE "TRUE$" //not used anymore
#define FALSE "FALSE$" //not used anymore
#define DEMARCATE "$"
#define GANTRY_ID 211



#define VALIDATE 101
#define WRITE 102
#define READ 103
#define VALIDATE1111 199

#define MSG_ID 201
#define BEFOREAFTER 202
#define SENSORSTATE 203
#define CASH_DOLLAR 204
#define BUTTONSTATE 205
#define GANTRYOPERATION 206
#define IULABEL 207
#define CASHLABEL 208
#define CCLABEL 209
#define CASH_CENTS 210

#define TO_TICKET        300
#define FROM_TICKET      301
#define FROM_MAINT_SUPPORT1    302
#define FROM_MAINT_SUPPORT2    303
#define FROM_BCS         304
#define TO_ANTENNA       305
#define TO_CCREADER      306




void DisplayMessage(int state,char *message,int data_extracted,int case_selector_indisplay,char *data_returned); 
		//add a special characte to demarcate between "user" message and message sent to debug text box on photon.
		// char anything will give flexibility to programmer to add extra cases in DsiplayMessage routine for a particular state and msg_id.
	int GetData(char *message,int data_tobe_extracted,unsigned char *temp); //data_tobe_extracted could be IUlabel, cash or msg_id from the data received from simulator.
	int database_operations(int action,char *message); //possible actions are 'validate','write' and 'read'. Message and action have to be passed to this functions.
	int display_default_message(int rcvid,char *message);
	int convert_bd(char *temp);
