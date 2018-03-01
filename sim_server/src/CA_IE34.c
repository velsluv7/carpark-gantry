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
char message_id_006[50];
char disp_buff[200];
char debug_buff[200];
int i,j,sizeofrmsg;


int
CA_IE34( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{

	//message_id_006="00000110xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx@Minimum balance not available$Insufficient Balance";
		message_id_006[0] = 0x06;
		message_id_006[1] = 0x9E;
		message_id_006[2] = 0x34;
		message_id_006[3] = 0x30;
		message_id_006[4] = 0x70;
		/* eliminate 'unreferenced' warnings */
		widget = widget, apinfo = apinfo, cbinfo = cbinfo;
		/*
		if ((EntrG01_coid = name_open(ATTACH_POINT, 0)) == -1) {
							    printf("failure to connect to message id 6 \n");
								return EXIT_FAILURE;
							}*/
		if (MsgSend (EntrG01_coid,message_id_006,strlen (message_id_006)+1,rmsg,sizeof (rmsg)) == -1)
					{
					    	fprintf (stderr, "Error during MsgSend to message id 6\n");
					    	perror (NULL);
					    	exit (EXIT_FAILURE);
					}

		if (strlen ((char *)rmsg) > 0)
				{
			        printf ("Application process replies ::: %x %x %x\n",rmsg[0],rmsg[1],rmsg[2]);

				}

		message_id_006[0] = 0x00;
		message_id_006[1] = 0x00;

		if (MsgSend (EntrG01_coid,message_id_006,strlen (message_id_006)+1,rmsg,sizeof (rmsg)) == -1)
					{
					    	fprintf (stderr, "Error during MsgSend to message id 6\n");
					    	perror (NULL);
					    	exit (EXIT_FAILURE);
					}
		if (strlen (rmsg) > 0)
					{
							printf ("Application replies for message id 6 ::: \"%s\"\n",rmsg);
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
									else
									{
									debug_buff[i]=NULL;
									break;
									}
								}

							if(strcmp(debug_buff,"Gantry Open") == 0)
							{
								PtSetResource(ABW_EntrG01Gate,Pt_ARG_ONOFF_STATE,1,0);
								PtSetResource(ABW_EntrG01Disp01,Pt_ARG_TEXT_STRING,"Opening Gantry",0);
								sleep(2);
							}
							else
								PtSetResource(ABW_EntrG01Gate ,Pt_ARG_ONOFF_STATE,0,0);

								PtSetResource(ABW_EntrG01Disp01,Pt_ARG_TEXT_STRING,disp_buff,0);
								PtSetResource(ABW_EntrG01Disp02,Pt_ARG_TEXT_STRING,debug_buff,0);
					}
		return( Pt_CONTINUE );

	}

