/* Event header for application - AppBuilder 2.03  */

static const ApEventLink_t AbApplLinks[] = {
	{ 3, 0, 0L, 0L, 0L, &base, NULL, NULL, 0, NULL, 0, 0, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_G01_user_access_window[] = {
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "Car01_IU", 2009, Car01_IU, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "Car01_IU", 2009, Close_Car01_IU, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "Car02_IU", 2009, Car02_IU, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "Car02_IU", 2009, Close_Car02_IU, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "Car03_IU", 2009, Car03_IU, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "Car03_IU", 2009, Close_Car03_IU, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "Car01_CC", 2009, Car01_CC, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "Car01_CC", 2009, Close_Car01_CC, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "Car02_CC", 2009, Car02_CC, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "Car02_CC", 2009, Close_Car02_CC, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "Car01_COMP", 2009, Car01_COMP, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "Car01_COMP", 2009, Close_Car01_COMP, 0, 0, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_base[] = {
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "EntrG01LS01", 2009, EntrG01LS01, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "EntrG01Obstacle", 2009, EntrG01Obstacle, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "EntrG01LS02", 2009, EntrG01LS02, 0, 0, 0, 0, },
	{ 3, 0, 0L, 0L, 0L, &G01_user_access_window, NULL, "EntrG01GrantAccess", 2009, NULL, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "EntrG01VoiceIntercom", 2009, EntrG01VoiceIntercom, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "EntrG01firealarm", 2009, EntrG01firealarm, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "EntrG01attendant_authorized", 2009, EntrG01attendant_authorized, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "EntrG01attendant_notauthorized", 2009, EntrG01attendant_notauthorized, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "alertbutton01", 2009, alertbutton01, 0, 0, 0, 0, },
	{ 0 }
	};

const char ApOptions[] = AB_OPTIONS;
