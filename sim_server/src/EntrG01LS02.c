/* Y o u r   D e s c r i p t i o n                       */
/*                            AppBuilder Photon Code Lib */
/*                                         Version 2.03  */

/* Standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>
/* Local headers */
#include "ablibs.h"
#include "abimport.h"
#include "proto.h"
#include "fornameopen.h"

#define ATTACH_POINT "ExitG01"

char rmsg[200];
char message_id_002[50];
char disp_buff[200];
char debug_buff[200];
int i,j,sizeofrmsg,val;
unsigned char flag1=0;



int
EntrG01LS02( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )
	{
	//message_id_002="0000001001011000@Load Sensor2 Detected$Thanks.. Please Proceed..";
	//PtGetResource(ABW_EntrG01LS02,Pt_ARG_ONOFF_STATE ,&val,1);
    flag1 = !flag1;

    if(flag1)
    {
       message_id_002[0] = 0x02;
       message_id_002[1] = 0x18;
	   printf("Value of button is 1\n");
    }
    else
    {
       message_id_002[0] = 0x02;
       message_id_002[1] = 0x10;
       printf("Value of button is 0\n");
    }

	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;
/*
	if ((EntrG01_coid = name_open(ATTACH_POINT, 0)) == -1) {
				    printf("failure to connect to message id 2 \n");
					return EXIT_FAILURE;
				}*/
	if (MsgSend (EntrG01_coid,message_id_002,strlen (message_id_002)+1,rmsg,sizeof (rmsg)) == -1)
				{
			    	fprintf (stderr, "Error during MsgSend to message id 2\n");
			    	perror (NULL);
			    	exit (EXIT_FAILURE);
				}
	if (strlen (rmsg) > 0)
				{
					printf ("Application replies for message id 2 ::: \"%s\"\n",rmsg);
					sizeofrmsg=strlen(rmsg);
					//looping for extracting user display
					for (i=0;i<=sizeofrmsg;i++)
					{
							if (rmsg[i]=='$')
							for(j=0;j<=sizeofrmsg;j++)
							{
								i++;
								disp_buff[j]=rmsg[i];
							}
					}
					//looping for extracting debug message
					for (i=0;i<=sizeofrmsg;i++)
						{
							if (rmsg[i]!='$')
							debug_buff[i]=rmsg[i];
							else break;
						}

					PtSetResource(ABW_EntrG01Disp01,Pt_ARG_TEXT_STRING,disp_buff,0);
					PtSetResource(ABW_EntrG01Disp02,Pt_ARG_TEXT_STRING,debug_buff,0);
					//PtSetResource(ABW_EntrG01Antenna,Pt_ARG_ONOFF_STATE,1,0);
				}

	return( Pt_CONTINUE );

	}

