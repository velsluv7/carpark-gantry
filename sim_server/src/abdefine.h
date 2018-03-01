/* Define header for application - AppBuilder 2.03  */

/* 'CA_IE12' Window link */
extern const int ABN_CA_IE12;
#define ABW_CA_IE12                          AbGetABW( ABN_CA_IE12 )
extern const int ABN_IU_IC12;
#define ABW_IU_IC12                          AbGetABW( ABN_IU_IC12 )
extern const int ABN_Car03_IU;
#define ABW_Car03_IU                         AbGetABW( ABN_Car03_IU )
extern const int ABN_IU_IC78;
#define ABW_IU_IC78                          AbGetABW( ABN_IU_IC78 )
extern const int ABN_Car05_IU;
#define ABW_Car05_IU                         AbGetABW( ABN_Car05_IU )
extern const int ABN_Car01_CC;
#define ABW_Car01_CC                         AbGetABW( ABN_Car01_CC )
extern const int ABN_Car05_CC;
#define ABW_Car05_CC                         AbGetABW( ABN_Car05_CC )
extern const int ABN_Car04_CC;
#define ABW_Car04_CC                         AbGetABW( ABN_Car04_CC )
extern const int ABN_Car03_CC;
#define ABW_Car03_CC                         AbGetABW( ABN_Car03_CC )
extern const int ABN_CA_IE34;
#define ABW_CA_IE34                          AbGetABW( ABN_CA_IE34 )
extern const int ABN_CO_IF12;
#define ABW_CO_IF12                          AbGetABW( ABN_CO_IF12 )
extern const int ABN_CO_IF34;
#define ABW_CO_IF34                          AbGetABW( ABN_CO_IF34 )
extern const int ABN_Car03_COMP;
#define ABW_Car03_COMP                       AbGetABW( ABN_Car03_COMP )
extern const int ABN_Car04_COMP;
#define ABW_Car04_COMP                       AbGetABW( ABN_Car04_COMP )
extern const int ABN_Car05_COMP;
#define ABW_Car05_COMP                       AbGetABW( ABN_Car05_COMP )
extern const int ABN_IU_IC34;
#define ABW_IU_IC34                          AbGetABW( ABN_IU_IC34 )

/* 'base' Window link */
extern const int ABN_base;
#define ABW_base                             AbGetABW( ABN_base )
extern const int ABN_EntrG01Disp01;
#define ABW_EntrG01Disp01                    AbGetABW( ABN_EntrG01Disp01 )
extern const int ABN_EntrG01Disp02;
#define ABW_EntrG01Disp02                    AbGetABW( ABN_EntrG01Disp02 )
extern const int ABN_EntrG02Antenna;
#define ABW_EntrG02Antenna                   AbGetABW( ABN_EntrG02Antenna )
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
extern const int ABN_Ticket_Gan01;
#define ABW_Ticket_Gan01                     AbGetABW( ABN_Ticket_Gan01 )
extern const int ABN_EntrG01VoiceIntercom;
#define ABW_EntrG01VoiceIntercom             AbGetABW( ABN_EntrG01VoiceIntercom )
extern const int ABN_EntrG02_firealarm;
#define ABW_EntrG02_firealarm                AbGetABW( ABN_EntrG02_firealarm )
extern const int ABN_EntrG01attendant_authorized;
#define ABW_EntrG01attendant_authorized      AbGetABW( ABN_EntrG01attendant_authorized )
extern const int ABN_EntrG01attendant_notauthorized;
#define ABW_EntrG01attendant_notauthorized   AbGetABW( ABN_EntrG01attendant_notauthorized )
extern const int ABN_EntrG01powersupply;
#define ABW_EntrG01powersupply               AbGetABW( ABN_EntrG01powersupply )
extern const int ABN_alertbutton02;
#define ABW_alertbutton02                    AbGetABW( ABN_alertbutton02 )

/* 'Ticket_window01' Window link */
extern const int ABN_Ticket_window01;
#define ABW_Ticket_window01                  AbGetABW( ABN_Ticket_window01 )
extern const int ABN_close_ticket_window;
#define ABW_close_ticket_window              AbGetABW( ABN_close_ticket_window )
extern const int ABN_cfileforticket;
#define ABW_cfileforticket                   AbGetABW( ABN_cfileforticket )

#define AbGetABW( n ) ( AbWidgets[ n ].wgt )

#define AB_OPTIONS "s:x:y:h:w:S:"
