/* Y o u r   D e s c r i p t i o n                       */
/*                            AppBuilder Photon Code Lib */
/*                                         Version 2.03  */

/* Standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <process.h>
/* Local headers */
#include "ablibs.h"
#include "abimport.h"
#include "proto.h"

int fire_coid;


int
alertbutton02( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{

	char message[2];
	char rmsg[3];
	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;


	message[0]=1;
	if(MsgSend(fire_coid,message,strlen(message)+1,rmsg,sizeof(message)) == -1)
	{
		printf("failed\n");
	}
	return( Pt_CONTINUE );

	}

