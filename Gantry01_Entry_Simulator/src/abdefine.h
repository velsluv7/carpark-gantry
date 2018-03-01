/* Define header for application - AppBuilder 2.03  */

/* 'G01_user_access_window' Window link */
extern const int ABN_G01_user_access_window;
#define ABW_G01_user_access_window           AbGetABW( ABN_G01_user_access_window )
extern const int ABN_Car01_IU;
#define ABW_Car01_IU                         AbGetABW( ABN_Car01_IU )
extern const int ABN_Car02_IU;
#define ABW_Car02_IU                         AbGetABW( ABN_Car02_IU )
extern const int ABN_Car03_IU;
#define ABW_Car03_IU                         AbGetABW( ABN_Car03_IU )
extern const int ABN_Car04_IU;
#define ABW_Car04_IU                         AbGetABW( ABN_Car04_IU )
extern const int ABN_Car01_CC;
#define ABW_Car01_CC                         AbGetABW( ABN_Car01_CC )
extern const int ABN_Car04_CC;
#define ABW_Car04_CC                         AbGetABW( ABN_Car04_CC )
extern const int ABN_Car03_CC;
#define ABW_Car03_CC                         AbGetABW( ABN_Car03_CC )
extern const int ABN_Car02_CC;
#define ABW_Car02_CC                         AbGetABW( ABN_Car02_CC )
extern const int ABN_Car01_COMP;
#define ABW_Car01_COMP                       AbGetABW( ABN_Car01_COMP )
extern const int ABN_Car02_COMP;
#define ABW_Car02_COMP                       AbGetABW( ABN_Car02_COMP )
extern const int ABN_Car03_COMP;
#define ABW_Car03_COMP                       AbGetABW( ABN_Car03_COMP )
extern const int ABN_Car04_COMP;
#define ABW_Car04_COMP                       AbGetABW( ABN_Car04_COMP )

/* 'base' Window link */
extern const int ABN_base;
#define ABW_base                             AbGetABW( ABN_base )
extern const int ABN_EntrG01Disp01;
#define ABW_EntrG01Disp01                    AbGetABW( ABN_EntrG01Disp01 )
extern const int ABN_EntrG01Disp02;
#define ABW_EntrG01Disp02                    AbGetABW( ABN_EntrG01Disp02 )
extern const int ABN_EntrG01Antenna;
#define ABW_EntrG01Antenna                   AbGetABW( ABN_EntrG01Antenna )
extern const int ABN_EntrG01LS01;
#define ABW_EntrG01LS01                      AbGetABW( ABN_EntrG01LS01 )
extern const int ABN_EntrG01Gate;
#define ABW_EntrG01Gate                      AbGetABW( ABN_EntrG01Gate )
extern const int ABN_EntrG01Obstacle;
#define ABW_EntrG01Obstacle                  AbGetABW( ABN_EntrG01Obstacle )
extern const int ABN_EntrG01LS02;
#define ABW_EntrG01LS02                      AbGetABW( ABN_EntrG01LS02 )
extern const int ABN_EntrG01Disp03;
#define ABW_EntrG01Disp03                    AbGetABW( ABN_EntrG01Disp03 )
extern const int ABN_EntrG01Disp04;
#define ABW_EntrG01Disp04                    AbGetABW( ABN_EntrG01Disp04 )
extern const int ABN_EntrG01GrantAccess;
#define ABW_EntrG01GrantAccess               AbGetABW( ABN_EntrG01GrantAccess )
extern const int ABN_EntrG01VoiceIntercom;
#define ABW_EntrG01VoiceIntercom             AbGetABW( ABN_EntrG01VoiceIntercom )
extern const int ABN_EntrG01firealarm;
#define ABW_EntrG01firealarm                 AbGetABW( ABN_EntrG01firealarm )
extern const int ABN_EntrG01attendant_authorized;
#define ABW_EntrG01attendant_authorized      AbGetABW( ABN_EntrG01attendant_authorized )
extern const int ABN_EntrG01attendant_notauthorized;
#define ABW_EntrG01attendant_notauthorized   AbGetABW( ABN_EntrG01attendant_notauthorized )
extern const int ABN_EntrG01powersupply;
#define ABW_EntrG01powersupply               AbGetABW( ABN_EntrG01powersupply )
extern const int ABN_alertbutton01;
#define ABW_alertbutton01                    AbGetABW( ABN_alertbutton01 )

#define AbGetABW( n ) ( AbWidgets[ n ].wgt )

#define AB_OPTIONS "s:x:y:h:w:S:"
