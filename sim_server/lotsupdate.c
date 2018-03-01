/*
 * lotsupdate.c
 *
 *  Created on: Apr 23, 2011
 *      Author: Nishin
 */
#include "hourseason.h"
#if 0
void lotsupdate()
{
  	int sslot,hslot;
  	char hour[2],season[2];

  	while(1)
  	{
  		sslot= scount();
  		sprintf(season,"%d",sslot);
  		printf(" the season slot is %d\n",sslot);
  		PtSetResource(ABW_EntrG01Disp03,Pt_ARG_TEXT_STRING,season,0);

  		hslot = hcount();
  		sprintf(hour,"%d",hslot);
  		printf(" the hourly slot is %d\n",hslot);
  		//PtSetResource(ABW_EntrG01Disp04,Pt_ARG_TEXT_STRING,hour,0);
  		sleep(2);
  	}
}
#endif


