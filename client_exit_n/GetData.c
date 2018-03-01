/*
 * GetData.c
 *
 *  Created on: Apr 22, 2011
 *      Author: Nishin
 */
#include "exit_top_header.h"

extern int GetData(char *message,int data_tobe_extracted,unsigned char *temp)
{
	int data_extracted=0,dollar,cents,data_extracted_copy;
	char *data;

	unsigned char msgid,data1;
	data = message;

	msgid = (unsigned char)data[0];
	printf("msgid is %x\n",msgid);

	switch(data_tobe_extracted)
	{
		case MSG_ID:
		data_extracted = (unsigned char)data[0];
		break;

		case GANTRY_ID:
		data_extracted = (unsigned char)(0xE0&data[0]);
		data_extracted = data_extracted>>5;
		break;

		case BEFOREAFTER:
		data1 = (unsigned char)data[1];
		printf("%x\n",data1);
		if(0!=(0x10&data1))
        {
			printf("After Gantry\n");
            data_extracted = 1;
        }
		else
        {
			printf("Before Gantry\n");
            data_extracted = 0;
        }
		break;

		case SENSORSTATE:
        data_extracted = 0;
		if(msgid==2)
        {
            data1 = (unsigned char)data[1];
            printf("%x\n",data1);
            if(0x08==(data1&0x08))
            {
                printf("Vehicle Present\n");
                data_extracted = 1;
            }
            else
            {
                printf("Vehicle Absent\n");
                data_extracted = 0;
            }
        }
        else
        {
            data1 = (unsigned char)data[1];
            printf("%x\n",data1);
            if(0x10==(data1&0x10))
            {
                printf("Obstacle Detected\n");
                data_extracted = 1;
            }
            else
            {
                printf("Obstacle Not Detected\n");
                data_extracted = 0;
            }
        }
		break;

		case CASH_DOLLAR:
		data_extracted = (unsigned char)data[3];
		printf("data_extracted is %x\n",data_extracted);
        data1 = (data_extracted>>4)*10;
        dollar = data_extracted&0x0F;
        dollar = data1+dollar;
		printf("Dollars is %d\n",dollar);
		data_extracted = dollar;
		break;

		case CASH_CENTS:
		data_extracted = (unsigned char)data[4];
		printf("data_extracted is %x\n",data_extracted);
		cents = data_extracted&(0x00F0);
		cents = (cents>>4)*10;
		data_extracted = cents;
		printf("Cents is %d\n",cents);
		break;

		case BUTTONSTATE:
        if(msgid==12)
        {
            data1 = (unsigned char)data[1];
            printf("%x\n",data1);
            if(0x10==(data1&0x10))
            {
                printf("Button pressed\n");
                data_extracted = 1;
            }
            else
            {
                printf("Button not pressed\n");
                data_extracted = 0;
            }
        }
		break;

		case GANTRYOPERATION:
        if(msgid==13)
        {
            data1 = (unsigned char)data[1];
            printf("%x\n",data1);
            if(0x10==(data1&0x10))
            {
                printf("Authorized Exit\n");
                data_extracted = 1;
            }
            else
            {
                printf("Not Authorized Exit\n");
                data_extracted = 0;
            }
        }
		break;

		case IULABEL:
        if(msgid == 4)
		{
            data_extracted = (unsigned char)data[1];
            data_extracted &= 0x1F;
            data_extracted = data_extracted<<8;
            data_extracted |= (unsigned char)data[2];
            printf("IU Label is %x\n",data_extracted);
        }
		break;

		case CASHLABEL:
        if(msgid == 6)
		{
            data_extracted = (unsigned char)data[1];
            data_extracted &= 0x1F;
            data_extracted = data_extracted<<8;
            data_extracted |= (unsigned char)data[2];
            printf("IU Label is %x\n",data_extracted);
            printf("IU Label is %d\n",data_extracted);
            data_extracted_copy = data_extracted;
            temp[3] = (char)(data_extracted_copy%10);
            printf("%d",temp[3]);
            data_extracted_copy = data_extracted_copy/10;
            temp[2] = (char)(data_extracted_copy%10);
            printf("%d",temp[2]);
            data_extracted_copy = data_extracted_copy/10;
            temp[1] = (char)(data_extracted_copy%10);
            printf("%d",temp[1]);
            data_extracted_copy = data_extracted_copy/10;
            temp[0] = (char)(data_extracted_copy%10);
            printf("%d",temp[0]);
        }
		break;

		case CCLABEL:
        if(msgid == 8)
		{
            data_extracted = (unsigned char)data[1];
            data_extracted &= 0x1F;
            data_extracted = data_extracted<<8;
            data_extracted |= (unsigned char)data[2];
            printf("IU Label is %x\n",data_extracted);
           // printf("IU Label is %d\n",data_extracted);


        }
		break;

		case FROM_MAINT_SUPPORT1:
        if(msgid == 14)
		{
            data1 = (unsigned char)data[1];
            printf("%x\n",data1);
            if(0x10==(data1&0x10))
            {
                printf("Manual\n");
                data_extracted = 1;
            }
            else
            {
                printf("Automatic\n");
                data_extracted = 0;
            }
        }
        break;

		case FROM_MAINT_SUPPORT2:
        if(msgid == 15)
		{
            data1 = (unsigned char)data[1];
            printf("%x\n",data1);
            if(0x00==(data1&0x18))
            {
                printf("Disable Maintenance\n");
                data_extracted = 0; /* Disable Maintenance */
            }
            else if(0x08==(data1&0x18))
            {
                printf("Gantry Arm Up\n");
                data_extracted = 1; /* Gantry Arm Up */
            }
            else if(0x10==(data1&0x18))
            {
                printf("Gantry Arm Down\n");
                data_extracted = 2; /* Gantry Arm Down */
            }
            else if(0x18==(data1&0x18))
            {
                printf("Run BIT\n");
                data_extracted = 3; /* Gantry Arm Up */
            }
            else
            {
            }
        }
        break;


		case FROM_BCS:
        if(msgid == 16)
		{
            data1 = (unsigned char)data[1];
            printf("%x\n",data1);
            if(0x10==(data1&0x10))
            {
                printf("Alarm Triggered\n");
                data_extracted = 1; /* Alarm Triggered */
            }
            if(0x08==(data1&0x08))
            {
                printf("Power Supply CutOff\n");
                data_extracted = 2; /* Power Supply CutOff */
            }
        }
        break;
	}
	return data_extracted;
}
