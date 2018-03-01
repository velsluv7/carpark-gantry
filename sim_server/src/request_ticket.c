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
#include <Pt.h>
#include <Ph.h>

  char Verdana24[MAX_FONT_TAG];

  PtMultiLines_t hello[] = {
      { "Hello\n", Pt_DEFAULT_FONT, Pt_DEFAULT_COLOR,
        Pt_INHERIT_COLOR },
      { "World!", Pt_DEFAULT_FONT, Pt_DEFAULT_COLOR, Pt_INHERIT_COLOR }
  };

#define ATTACH_POINT "ExitG01"

char rmsg[120],smsg[120];
char message_id_017[50];
char disp_buff[200];
char debug_buff[200];
int i,j,sizeofrmsg;
int IULABEL,entryhour,exithour,exitmin,entrymin,cashavailable1,cashavailable2;
int cashdeducted1,cashdeducted2,temp;

int
request_ticket( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{
	PtArg_t args[2];
	char a[100],b[100],c[100],d[100],e[100];
	message_id_017[0] = 0x11;
	message_id_017[1] = 0x80;
    int nargs = 0;
    PhDim_t dim = { 250, 150 };
    PtWidget_t *window;


	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;


    if ((window = PtCreateWidget(PtWindow, Pt_NO_PARENT,
                                 0, NULL)) == NULL)
        PtExit( EXIT_FAILURE );

	if ((EntrG01_coid = name_open(ATTACH_POINT, 0)) == -1) {
					    printf("failure to connect to message id 4 \n");
						return EXIT_FAILURE;
					}
	/* first send the IU Label followed by dummy message */
		if (MsgSend (EntrG01_coid,message_id_017,strlen (message_id_017)+1,rmsg,sizeof (rmsg)) == -1)
					{
				    	fprintf (stderr, "Error during MsgSend to message id 4\n");
				    	perror (NULL);
				    	exit (EXIT_FAILURE);
					}
		if (strlen ((char *)rmsg) > 0)
				{
			printf ("Application process replies ::: %x %x %x %x %x %x %x %x %x %x\n",rmsg[0],rmsg[1],rmsg[2],rmsg[3],rmsg[4],rmsg[5],rmsg[6],rmsg[7],rmsg[8],rmsg[9]);

				}
		//int IULABEL,entryhour,exithour,exitmin,entrymin,cashavailable1,cashavailable2,cashdeducted,temp1;
		IULABEL = 0x1F & ((unsigned char) rmsg[1]);
		IULABEL = IULABEL<<8;
		temp = 0xFF & ((unsigned char) rmsg[2]); /* Lower byte of label */

		IULABEL |= temp;
		cashavailable1 = 0xFF & ((unsigned char) rmsg[3]); /* Tens of dollar avail */
        printf("\ncash avalilable 1 = %2x\n",cashavailable1);
		temp = 0xF0 & ((unsigned char) rmsg[4]);
		cashavailable2 = temp;
		printf("\ncash avalilable 2 = %2x\n",cashavailable2);
		cashdeducted1 = 0x0F & ((unsigned char) rmsg[4]); /* Tens of dollar avail */
		cashdeducted1 = cashdeducted1<<4;
		temp = 0xF0 & ((unsigned char) rmsg[5]);
		temp = temp>>4;
		cashdeducted1 |= temp;
		printf("\ncash deducted 1 = %2x\n",cashdeducted1);
		temp = 0x0F & ((unsigned char) rmsg[5]);
		cashdeducted2 = (temp<<4)&0xF0;
		printf("\ncash deducted 2 = %2x\n",cashdeducted2);
		entryhour = 0xFF & ((unsigned char) rmsg[6]);
		entrymin = 0xFF & ((unsigned char) rmsg[7]);
		exithour = 0xFF & ((unsigned char) rmsg[8]);
		exitmin = 0xFF & ((unsigned char) rmsg[9]);
		printf("\n entry hour = %x\n",entryhour);
		printf("\n entry min = %x\n",entrymin);
		printf("\n exithour = %x\n",exithour);
		printf("\n exithour = %x\n",exitmin);
		// sprintf(smsg,);

        sprintf(a,"Entry time = %x:%.2x hrs\n",entryhour,entrymin);
        sprintf(b,"Exit time = %x:%.2x hrs\n",exithour,exitmin);
        sprintf(c,"Cash Available = $%x.%.2x \n",cashavailable1,cashavailable2);
        sprintf(d,"Cash Deducted =  $%x.%.2x \n",cashdeducted1,cashdeducted2);
        sprintf(e,"IULABEL is  =  %x\n",IULABEL);
	    PtMultiLines_t hello[] = {
	    	{ e, Pt_DEFAULT_FONT, Pt_DEFAULT_COLOR, Pt_INHERIT_COLOR },
	        { a, Pt_DEFAULT_FONT, Pt_DEFAULT_COLOR, Pt_INHERIT_COLOR },
	        { b, Pt_DEFAULT_FONT, Pt_DEFAULT_COLOR, Pt_INHERIT_COLOR },
	        { c, Pt_DEFAULT_FONT, Pt_DEFAULT_COLOR, Pt_INHERIT_COLOR },
	        { d, Pt_DEFAULT_FONT, Pt_DEFAULT_COLOR, Pt_INHERIT_COLOR }
	    };

	    PtSetArg( &args[nargs++], Pt_ARG_DIM, &dim, 0 );
	    PtSetArg( &args[nargs++], Pt_ARG_MULTITEXT_SEGMENTS,
	        &hello, sizeof( hello )/sizeof(hello[0]) );

	    PtCreateWidget( PtMultiText, Pt_DEFAULT_PARENT,
	                    nargs, args );

	    PtRealizeWidget( window );

	return( Pt_CONTINUE );

	}

