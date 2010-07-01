/**
 * Ambilight Project
 * Ambilight device access library
 *
 * Copyright: (c) 2010 by Karol Maciaszek
 * E-mail   : <karol.maciaszek@gmail.com>
 * WWW      : http://www.czystybeton.pl/
 *
 * $Id$
 */


#ifndef X11CAPTURE_H_
#define X11CAPTURE_H_


#include <X11/Xlib.h>

#include "ambilight.h"


int x11capture_init(struct ambilight_config* cfg);

int x11capture_close(void);

void x11capture_refresh(void);

ambilight_led* x11capture_get_led(unsigned char led_no);

int x11capture_get_screenshot(XImage* screenshot);


#endif /* X11CAPTURE_H_ */
