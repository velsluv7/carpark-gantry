/* Event header for application - AppBuilder 2.03  */

static const ApEventLink_t AbApplLinks[] = {
	{ 3, 0, 0L, 0L, 0L, &base, NULL, NULL, 0, NULL, 0, 0, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_CA_IE12[] = {
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "IU_IC12", 2009, Car01_IU, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "IU_IC12", 2009, Close_IU_IC12, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "IU_IC12", 2009, EntrG01Antenna, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "Car03_IU", 2009, IU_IC56, 0, 0, 0, 0, },
	{ 10, 0, 0L, 0L, 0L, NULL, NULL, "Car03_IU", 2009, Close_IU_IC56, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "Car03_IU", 2009, EntrG01Antenna, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "IU_IC78", 2009, IU_IC78, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "IU_IC78", 2009, Close_IU_IC78, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "IU_IC78", 2009, EntrG01Antenna, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "Car01_CC", 2009, Car01_CC, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "Car01_CC", 2009, Close_Car01_CC, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "Car01_CC", 2009, EntrG01Antenna, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "CA_IE34", 2009, CA_IE34, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "CA_IE34", 2009, Close_Car01_CC, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "CA_IE34", 2009, EntrG01Antenna, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "CO_IF12", 2009, CO_IF12, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "CO_IF12", 2009, Close_Car01_COMP, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "CO_IF34", 2009, CO_IF34, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "IU_IC34", 2009, IU_IC34, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "IU_IC34", 2009, Close_IU_IC34, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "IU_IC34", 2009, EntrG01Antenna, 0, 0, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_base[] = {
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "EntrG01LS01", 2009, EntrG01LS01, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "EntrG01Obstacle", 2009, EntrG01Obstacle, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "EntrG01LS02", 2009, EntrG01LS02, 0, 0, 0, 0, },
	{ 3, 0, 0L, 0L, 0L, &CA_IE12, NULL, "EntrG01GrantAccess", 2009, NULL, 0, 3, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "Ticket_Gan01", 2009, request_ticket, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "EntrG01VoiceIntercom", 2009, EntrG01VoiceIntercom, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "EntrG02_firealarm", 2009, EntrG02_firealarm, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "EntrG01attendant_authorized", 2009, EntrG01attendant_authorized, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "EntrG01attendant_notauthorized", 2009, EntrG01attendant_notauthorized, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "EntrG01powersupply", 2009, powercut_alarm, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "alertbutton02", 2009, alertbutton02, 0, 0, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_Ticket_window01[] = {
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "close_ticket_window", 2009, close_ticket_win01, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "cfileforticket", 2009, cfileforticket, 0, 0, 0, 0, },
	{ 0 }
	};

const char ApOptions[] = AB_OPTIONS;
