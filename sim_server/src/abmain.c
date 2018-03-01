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
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>
#include <process.h>
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
#include "fornameopen.h"

#define ATTACH_POINT "ExitG01"

int slottot=20;
int hlottot=20;
unsigned char flag = 0;

void* updatelots()
{
       int sslot=55,hslot=55;
       char hour[2],season[2];
  	   /* eliminate 'unreferenced' warnings */
  	 //  widget = widget, apinfo = apinfo, cbinfo = cbinfo;

		while(!flag)
		{

				if(sslot!=scount())
				{
					sslot=scount();
					sprintf(season,"%d",slottot-sslot);
					//printf(" the season slot is %d\n",sslot);
					PtEnter(0);
					PtSetResource(ABW_EntrG01Disp04,Pt_ARG_TEXT_STRING,season,0);
					PtLeave(0);
				}

				if(hslot!=hcount())
				{
					hslot = hcount();
					sprintf(hour,"%d",hlottot-hslot);
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

	int new_proc;
	pthread_t th;
	pid_t pid_app;
	pid_app = getpid();
	printf("Welcome to Gantry 01 - Entrance\n");
	printf("The Process pid is %d\n",pid_app);

	new_proc = spawnl(P_NOWAIT,"/mnt/WindowsMount/client_exit_n/x86/o-g/client_exit_n_g","myprog", "ARG1", "ARG2", NULL);
	//new_proc = spawnl(P_NOWAIT,"/mnt/wrk/Application_test/x86/o-g/Application_test_g","myprog", "ARG1", "ARG2", NULL);

	_Ap_.Ap_winstate = 0;

	/* AppBuilder Initialization */
	ApInitialize( argc, argv, &AbContext );

	/* Display main window */
	ApLinkWindow( NULL, &AbApplLinks[0], NULL );

	//PtSetResource(ABW_EntrG01Disp01,Pt_ARG_TEXT_STRING,"Application will now begin",0);
	//PtSetResource(ABW_EntrG01Disp02,Pt_ARG_TEXT_STRING,"Available Lots Hourly:xx  Season:xx",0);

    pthread_create(&th,NULL,updatelots,NULL);

    if ((EntrG01_coid = name_open(ATTACH_POINT, 0)) == -1) {
    				    printf("failure to connect to message id 2 \n");
    					return EXIT_FAILURE;
    				}
	/* Loop until user quits application */
	PtMainLoop( );
	flag = 1;
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
	{ "PtToolbarGroup", &PtToolbarGroup },
	{ "PtMenuBar", &PtMenuBar },
	{ "PtMenuButton", &PtMenuButton },
	{ "PtToolbar", &PtToolbar },
	{ NULL, NULL }
	};

ApContext_t AbContext = { ClassTable, 1, AbWidgets };


