/*
 * exit_top_header.h
 *
 *  Created on: Apr 22, 2011
 *      Author: Nishin
 */

#ifndef EXIT_TOP_HEADER_H_
#define EXIT_TOP_HEADER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>
#include <process.h>
#include <math.h>
#include <time.h>

#include <globalstruct.h>


#define ATTACH_POINT            "ExitG01"
#define TRUE                    "TRUE$" //not used anymore
#define FALSE                   "FALSE$" //not used anymore
#define DEMARCATE               "$"

#define VALIDATE                101
#define WRITE                   102
#define READ                    103
#define DELETE                  104

#define MSG_ID                  201
#define BEFOREAFTER             202 /* to check before or after gantry */
#define SENSORSTATE             203 /* to check if sensor is active or inactive */
#define CASH_DOLLAR             204 /* to check if sensor is active or inactive */
#define BUTTONSTATE             205
#define GANTRYOPERATION         206
#define IULABEL                 207
#define CASHLABEL               208
#define CCLABEL                 209
#define CASH_CENTS              210
#define GANTRY_ID               211

#define TO_TICKET               300
#define FROM_TICKET             301
#define FROM_MAINT_SUPPORT1     302
#define FROM_MAINT_SUPPORT2     303
#define FROM_BCS                304
#define TO_ANTENNA              305
#define TO_CCREADER             306
#define TO_GANTRY               307

typedef struct
{
   int dollar_deduct; /* Dollar value deducted */
   int cents_deduct; /* Cents value deducted */
   int dollar_avail; /* Dollar value available */
   int cents_avail; /* Cents value available */
   int entry_hr; /* Entry hour */
   int entry_min; /* Entry minute */
   int exit_hr; /* Exit hour */
   int exit_min; /* Exit minute */
   int label; /* IU/Cash card label */
   unsigned char msgid;
   unsigned char gantryid;
}Message_Data;

    //Functions Used in this program::::::
	extern void DisplayMessage(int state,char *message,int data_extracted,int case_selector_indisplay,char *data_returned);
    //add a special characte to demarcate between "user" message and message sent to debug text box on photon.
	// char anything will give flexibility to programmer to add extra cases in DsiplayMessage routine for a particular state and msg_id.
	extern int GetData(char *message,int data_tobe_extracted,unsigned char *temp); //data_tobe_extracted could be IUlabel, cash or msg_id from the data received from simulator.
	extern int database_operations(int action,char *message); //possible actions are 'validate','write' and 'read'. Message and action have to be passed to this functions.
	extern void display_default_message(int rcvid,char *message);

    int calc_charge_time();
    extern int FormData(Message_Data *,int data_tobe_extracted,unsigned char *temp);


#endif /* EXIT_TOP_HEADER_H_ */
