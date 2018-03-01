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



char rmsg[200];

char disp_buff[200];
char debug_buff[200];
int i,j,sizeofrmsg;
unsigned char flag11=0;

int
EntrG02_firealarm( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{
		char message_id_016[50];

		/* eliminate 'unreferenced' warnings */
		widget = widget, apinfo = apinfo, cbinfo = cbinfo;

	    flag11 = !flag11;

	    if(flag11 == 1)
	    {
			message_id_016[0] = 0x10;
			message_id_016[1] = 0x10;


			if (MsgSend (EntrG01_coid,message_id_016,strlen (message_id_016)+1,rmsg,sizeof (rmsg)) == -1)
			{
					fprintf (stderr, "Error during MsgSend to message id 6\n");
					perror (NULL);
					exit (EXIT_FAILURE);
			}

			if (strlen ((char *)rmsg) > 0)
			{
				printf ("Application process replies ::: %x %x \n",rmsg[0],rmsg[1]);

			}
			PtSetResource(ABW_EntrG01Disp01,Pt_ARG_TEXT_STRING,"DANGER:EMERGENCY:GANTRY OPEN",0);
			PtSetResource(ABW_EntrG01Gate ,Pt_ARG_ONOFF_STATE,1,0);
	    }
	    else
	    	PtSetResource(ABW_EntrG01Gate ,Pt_ARG_ONOFF_STATE,0,0);
	return( Pt_CONTINUE );

	}

