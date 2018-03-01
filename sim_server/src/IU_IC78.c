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

char rmsg[120];

char disp_buff[200];
char debug_buff[200];
int i,j,sizeofrmsg;


int
IU_IC78( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{

	char message_id_004[50];
			/* eliminate 'unreferenced' warnings */
			widget = widget, apinfo = apinfo, cbinfo = cbinfo;
		#if 1

			message_id_004[0] = 0x04;
			message_id_004[1] = 0x9D;
			message_id_004[2] = 0x78;
			message_id_004[3] = 0x25;
			message_id_004[4] = 0x50;



			if ((EntrG01_coid = name_open(ATTACH_POINT, 0)) == -1) {
							    printf("failure to connect to message id 4 \n");
								return EXIT_FAILURE;
							}
			/* first send the IU Label followed by dummy message */
				if (MsgSend (EntrG01_coid,message_id_004,strlen (message_id_004)+1,rmsg,sizeof (rmsg)) == -1)
							{
						    	fprintf (stderr, "Error during MsgSend to message id 4\n");
						    	perror (NULL);
						    	exit (EXIT_FAILURE);
							}
				if (strlen ((char *)rmsg) > 0)
						{
					        printf ("Application process replies ::: %x %x %x\n",rmsg[0],rmsg[1],rmsg[2]);

						}

		      /* dummy message */
				message_id_004[0] = 0x00;
				message_id_004[1] = 0x00;
				if (MsgSend (EntrG01_coid,message_id_004,strlen (message_id_004)+1,rmsg,sizeof (rmsg)) == -1)
							{
						    	fprintf (stderr, "Error during MsgSend to message id 4\n");
						    	perror (NULL);
						    	exit (EXIT_FAILURE);
							}
				if (strlen (rmsg) > 0)
							{
								printf ("Application replies for message id 4 ::: \"%s\"\n",rmsg);
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
		#endif
	return( Pt_CONTINUE );

	}

