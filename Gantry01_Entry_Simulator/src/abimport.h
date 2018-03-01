/* Import (extern) header for application - AppBuilder 2.03  */

#include "abdefine.h"

extern ApWindowLink_t G01_user_access_window;
extern ApWindowLink_t base;
extern ApWidget_t AbWidgets[ 30 ];


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
int Car01_COMP( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Car01_IU( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Close_Car01_IU( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Close_Car01_CC( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Close_Car01_COMP( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int EntrG01firealarm( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int alertbutton01( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Car02_IU( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Close_Car02_IU( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Car02_CC( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Close_Car02_CC( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Car03_IU( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Close_Car03_IU( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
#ifdef __cplusplus
}
#endif
