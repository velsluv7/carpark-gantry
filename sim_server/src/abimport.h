/* Import (extern) header for application - AppBuilder 2.03  */

#include "abdefine.h"

extern ApWindowLink_t CA_IE12;
extern ApWindowLink_t base;
extern ApWindowLink_t Ticket_window01;
extern ApWidget_t AbWidgets[ 37 ];


#ifdef __cplusplus
extern "C" {
#endif
int EntrG01VoiceIntercom( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int EntrG01attendant_authorized( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int EntrG01attendant_notauthorized( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int EntrG01LS01( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int EntrG01Obstacle( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int EntrG01LS02( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Car01_CC( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int CO_IF12( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Car01_IU( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Close_IU_IC12( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Close_Car01_CC( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Close_Car01_COMP( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int EntrG02_firealarm( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int alertbutton02( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int EntrG01Antenna( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int close_ticket_win01( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int cfileforticket( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int IU_IC34( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int CA_IE34( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int CO_IF34( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int IU_IC78( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Close_IU_IC34( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int request_ticket( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int IU_IC56( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Close_IU_IC56( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Close_IU_IC78( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int powercut_alarm( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
#ifdef __cplusplus
}
#endif
