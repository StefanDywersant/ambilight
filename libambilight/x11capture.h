/**
 * Ambilight Project
 * Ambilight device access library
 *
 * Copyright: (c) 2010 by Karol Maciaszek
 * E-mail   : <karol.maciaszek@gmail.com>
 * WWW      : http://www.czystybeton.pl/
 *
 * $Id: x11grab.h 7 2010-06-26 06:40:45Z kharg $
 */


#ifndef X11CAPTURE_H_
#define X11CAPTURE_H_


#include "ambilight.h"


enum x11capture_error {
	X11CAPTURE_OK = 0,
	X11CAPTURE_CANT_OPEN_DISPLAY = -1,
	X11CAPTURE_NOT_INITIALIZED = -2
};


int x11capture_init(struct ambilight_config* cfg);

int x11capture_close(void);

void x11capture_refresh(void);

ambilight_led* x11capture_get_led(unsigned char led_no);


#endif /* X11CAPTURE_H_ */
