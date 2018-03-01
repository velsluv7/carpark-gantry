/* M a i n l i n e                                       */
/*                            AppBuilder Photon Code Lib */
/*                                         Version 2.03  */

#ifdef __USAGE
%C - This is a QNX/Photon Application.
%C [options]

Options:
  -s server   Server node or device name
  -x x        Initial x position
  -y y        Initial y position
  -h h        Initial h dimension
  -w w        Initial w dimension

Examples:
%C -s4
  Run using Photon server on node 4

%C -s//4/dev/photon
  Same as above

%C -x10 -y10 -h200 -w300
  Run at initial position 10,10 with initial 
  dimension of 200x300.
#endif

/* Standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Local headers */
#include "ablibs.h"
#include "abimport.h"
#include "proto.h"
#include "abwidgets.h"
#include "abdefine.h"
#include "abevents.h"
#include "ablinks.h"
#include "abvars.h"
#include "hourseason.h"
#include "pthread.h"


  unsigned char flag1 = 0;
int no_sslot = 20;
int no_hslot = 20;

void* updatelots()
{

       int sslot=50,hslot=50;
    	   char hour[2],season[2];
  	   /* eliminate 'unreferenced' warnings */
  	 //  widget = widget, apinfo = apinfo, cbinfo = cbinfo;

		while(!flag1)
		{

		    if(sslot!=scount())
		    {
		    	sslot=scount();
			    sprintf(season,"%d",no_sslot-sslot);
				//printf(" the season slot is %d\n",sslot);
				PtEnter(0);
				PtSetResource(ABW_EntrG01Disp04,Pt_ARG_TEXT_STRING,season,0);
				PtLeave(0);
		    }

		    if(hslot!=hcount())
		    {
		    	hslot = hcount();
				sprintf(hour,"%d",no_hslot - hslot);
				//printf(" the hourly slot is %d\n",hslot);
				PtEnter(0);
				PtSetResource(ABW_EntrG01Disp03,Pt_ARG_TEXT_STRING,hour,0);
				PtLeave(0);
		    }

			sleep(1);
		}
     pthread_exit(0);
}
int
main ( int argc, char *argv[] )

	{
	pthread_t th;
	int new_proc,new_proc1;
	pid_t pid_app;
	pid_app = getpid();
	printf("Welcome to Gantry 01 - Entrance\n");
	printf("The Process pid is %d\n",pid_app);

	new_proc = spawnl(P_NOWAIT,"/mnt/WindowsMount/my_client_prog04/x86/o/my_client_prog04","myprog", "ARG1", "ARG2", NULL);
	new_proc1 = spawnl(P_NOWAIT,"/mnt/WindowsMount/sim_server/x86/o-g/sim_server_g","myprog", "ARG1", "ARG2", NULL);


	_Ap_.Ap_winstate = 0;

	/* AppBuilder Initialization */
	ApInitialize( argc, argv, &AbContext );

	/* Display main window */
	ApLinkWindow( NULL, &AbApplLinks[0], NULL );

	pthread_create(&th,NULL,updatelots,NULL);

	PtSetResource(ABW_EntrG01Disp01,Pt_ARG_TEXT_STRING,"Application will now begin",0);
	PtSetResource(ABW_EntrG01Disp02,Pt_ARG_TEXT_STRING,"Slots Available",0);
	/* Loop until user quits application */
	PtMainLoop( );
	flag1 = 1;
		pthread_join(th,NULL);
		PtExit( 0 );

	kill (0,0);

	return 0;
	}

static const ApClassTab_t ClassTable[] = {
	{ "PtWindow", &PtWindow },
	{ "PtContainer", &PtContainer },
	{ "PtButton", &PtButton },
	{ "PtLabel", &PtLabel },
	{ "PtMultiText", &PtMultiText },
	{ "PtPane", &PtPane },
	{ "PtOnOffButton", &PtOnOffButton },
	{ "PtImageArea", &PtImageArea },
	{ "PtClock", &PtClock },
	{ NULL, NULL }
	};

ApContext_t AbContext = { ClassTable, 1, AbWidgets };


