/*
 * FormData.c
 *
 *  Created on: Apr 22, 2011
 *      Author: Nishin
 */
#include "exit_top_header.h"

extern int FormData(Message_Data *msgtobesent,int data_tobe_extracted,unsigned char *temp)
{
	int data_extracted=0,buffer;
	unsigned char msgid,data1,data2,data3;
	msgid = msgtobesent->msgid;
	switch(data_tobe_extracted)
	{

		case TO_TICKET:
        if(msgid == 11)
		{
			temp[0] = msgid;/* temp 0 will now contian the msg id*/
			data1 = msgtobesent->gantryid;
			printf("data1 b4 the compiled messge is %x",data1);
			data1 = data1<<5;
			temp[1] = data1;
            printf("temp[1] in the compiled messge is %x",temp[1]);
	        buffer = ((msgtobesent->label)&0xFF00);
			buffer = buffer>>8;
			temp[1] |= (unsigned char)buffer;
			printf("temp[1] in the compiled messge after label addition is %x",temp[1]);
			buffer = ((msgtobesent->label)&0x00FF);
			temp[2] = (unsigned char)(buffer); /* Extracting the tens value first */
			/* Cash available */
			data1 = (unsigned char)((msgtobesent->dollar_avail)/10); /* Extracting the tens value first */
            data1 = data1<<4; /* Shifting the tens value to the upper nibble */
			temp[3] = (unsigned char)data1; /* Extracting the tens value first */
			data2 = (unsigned char)((msgtobesent->dollar_avail)%10); /* Now extracting the units value */
			temp[3] |= (unsigned char)data2; /* writing the units value */
			data3 = (unsigned char)((msgtobesent->cents_avail)/10); /* Only extracting the tens value for cents */
			data1 = (unsigned char)((msgtobesent->dollar_deduct)/10); /* Only extracting the tens value for deduct_dollar */
			data3 = data3<<4;
            temp[4] = data3;
			temp[4] |= data1; /* Lower nibble of temp3 will contain the tens place of the dollar */

			/* Cash deducted */
            data2 = (unsigned char)((msgtobesent->dollar_deduct)%10); /* Only extracting the units value for deduct_dollar */
			data2 = data2<<4;
			data3 = (unsigned char)((msgtobesent->cents_deduct)/10); /* Only extracting the tens value for cents */
			data2 |= data3;
			temp[5] = data2;

			/* Entry time */
			data1 = (unsigned char)((msgtobesent->entry_hr)/10); /* Only extracting the tens value for entry_hr */
			data1 = data1<<4;
			temp[6] = data1;
			data1 = (unsigned char)((msgtobesent->entry_hr)%10); /* Only extracting the units value for entry_hr */
			temp[6] |= data1;

			data1 = (unsigned char)((msgtobesent->entry_min)/10); /* Only extracting the tens value for entry_min */
			data1 = data1<<4;
			temp[7] = data1;
			data1 = (unsigned char)((msgtobesent->entry_min)%10); /* Only extracting the units value for entry_min */
			temp[7] |= data1;

			/* Exit time */
			data1 = (unsigned char)((msgtobesent->exit_hr)/10); /* Only extracting the tens value for exit_hr */
			data1 = data1<<4;
			temp[8] = data1;
			data1 = (unsigned char)((msgtobesent->exit_hr)%10); /* Only extracting the units value for exit_hr */
			temp[8] |= data1;

			data1 = (unsigned char)((msgtobesent->exit_min)/10); /* Only extracting the tens value for exit_min */
			data1 = data1<<4;
			temp[9] = data1;
			data1 = (unsigned char)((msgtobesent->exit_min)%10); /* Only extracting the units value for exit_min */
			temp[9] |= data1;

			printf("Temp is %x %x %x %x %x %x %x %x %x %x \n",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7],temp[8],temp[9]);

        }
        break;

		case TO_ANTENNA:
        if(msgid == 5)
		{
			temp[0] = msgid;/* temp 0 will now contian the msg id*/
			data1 = msgtobesent->gantryid;
			data1 = data1<<5;
			temp[1] = data1;
			data1 = (unsigned char)((msgtobesent->dollar_deduct)/10); /* Extracting the tens value first */
            temp[1] |= (char)data1; /* Extracting the tens value first */
            data1 = (unsigned char)((msgtobesent->dollar_deduct)%10); /* Now extracting the units value */
            data1 = data1<<4; /* Shifting the tens value to teh upper nibble */
			data2 = (unsigned char)((msgtobesent->cents_deduct)/10); /* Only extracting the tens value for cents */
            data1 |= data2; /* st */
            temp[2] = data1;
            printf("Temp is %x %x %x\n",temp[0],temp[1],temp[2]);
        }
        break;

   		case TO_CCREADER:
        if(msgid == 7)
		{
			temp[0] = msgid;/* temp 0 will now contian the msg id*/
			data2 = msgtobesent->gantryid;
			data1 = (unsigned char)(data2<<5);
			temp[1] = (unsigned char)data1;
			data1 = (unsigned char)((msgtobesent->dollar_deduct)/10); /* Extracting the tens value first */
            temp[1] |= (unsigned char)data1; /* Extracting the tens value first */
            data1 = (unsigned char)((msgtobesent->dollar_deduct)%10); /* Now extracting the units value */
            data1 = data1<<4; /* Shifting the tens value to teh upper nibble */
			data2 = (unsigned char)((msgtobesent->cents_deduct)/10); /* Only extracting the tens value for cents */
            data1 |= data2; /* st */
            temp[2] = data1;
            printf("Temp is %x %x %x\n",temp[0],temp[1],temp[2]);
        }
        break;

   		case TO_GANTRY:
        if(msgid == 16)
		{
			temp[0] = msgid;/* temp 0 will now contian the msg id*/
			data2 = msgtobesent->gantryid;
			data1 = (unsigned char)(data2<<5);
			temp[1] = (unsigned char)data1;
            temp[1] |= 0x10;
            printf("Temp is %x %x\n",temp[0],temp[1]);
        }
        break;
	}
	return data_extracted;
}
