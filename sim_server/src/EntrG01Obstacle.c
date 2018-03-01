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
char message_id_003[50];
char disp_buff[200];
char debug_buff[200];
int i,j,sizeofrmsg;
int obstacle_sensed=0;

int
EntrG01Obstacle( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{
	obstacle_sensed=!obstacle_sensed;
	if(obstacle_sensed)
	{
	//message_id_003="0000001101010000@Gantry Open$Obstacle sensed ";
		message_id_003[0] = 0x03;
		message_id_003[1] = 0x90;
	}
	else if(!obstacle_sensed)
	{
		message_id_003[0] = 0x03;
		message_id_003[1] = 0x80;
	}

	printf("Message is %x %x\n",message_id_003[0],message_id_003[1]);
	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;
	/*
	if ((EntrG01_coid = name_open(ATTACH_POINT, 0)) == -1) {
						    printf("failure to connect to message id 3 \n");
							return EXIT_FAILURE;
						}*/
	if (MsgSend (EntrG01_coid,message_id_003,strlen (message_id_003)+1,rmsg,sizeof (rmsg)) == -1)
						{
					    	fprintf (stderr, "Error during MsgSend to message id 3\n");
					    	perror (NULL);
					    	exit (EXIT_FAILURE);
						}
	if (strlen (rmsg) > 0)
						{
							printf ("Application replies for message id 3 ::: \"%s\"\n",rmsg);
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
						//	if(strcmp(debug_buff,"Gantry Open") == 0)
							if(obstacle_sensed)
							{
								PtSetResource(ABW_EntrG01Gate,Pt_ARG_ONOFF_STATE,1,0);
								printf("\n Gantry still remains open \n");
							}
							else
							{
								PtSetResource(ABW_EntrG01Gate ,Pt_ARG_ONOFF_STATE,0,0);
							}

							PtSetResource(ABW_EntrG01Disp01,Pt_ARG_TEXT_STRING,disp_buff,0);
							PtSetResource(ABW_EntrG01Disp02,Pt_ARG_TEXT_STRING,debug_buff,0);
						}
	return( Pt_CONTINUE );

	}

