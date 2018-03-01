/*
 * globalstruct.h
 *
 *  Created on: Apr 11, 2011
 *      Author: Velu
 */

#ifndef GLOBALSTRUCT_H_
#define GLOBALSTRUCT_H_


#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <qdb/qdb.h>
#include <sys/neutrino.h>

typedef struct
{
	int  label; // label of the iu card or cash card or comp card
	char *type;  // IU or CA or CO
	char *user;  // S or H or F
	int entry_hr; // enter the hour
	int entry_mn; // enter the minute
	int exit_hr; // enter the hour
	int exit_mn; // enter the minute
	int month;   // required for season user
	int AvailAmount1; // dollar
	int AvailAmount2; // cent
	int DeductAmount1; // dollar
	int DeductAmount2; // cent
	unsigned char g_id;
}DB_OP;

extern DB_OP *db;



int DB_DeleteLabel(DB_OP *val);
int DB_ValidateExit(DB_OP *val);
int DeleteAll();
#endif /* GLOBALSTRUCT_H_ */
