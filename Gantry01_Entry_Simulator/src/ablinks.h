/* Link header for application - AppBuilder 2.03  */

extern ApContext_t AbContext;

ApWindowLink_t G01_user_access_window = {
	"G01_user_access_window.wgtw",
	&AbContext,
	AbLinks_G01_user_access_window, 0, 12
	};

ApWindowLink_t base = {
	"base.wgtw",
	&AbContext,
	AbLinks_base, 13, 9
	};

