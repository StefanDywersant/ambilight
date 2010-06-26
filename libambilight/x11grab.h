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


#ifndef XSCREENSHOT_H_
#define XSCREENSHOT_H_


#include "ambilight.h"


struct x11grab_config {
	int edge_thickness;
	int margin_top;
	int margin_bottom;
	int margin_left;
	int margin_right;
};


enum x11grab_error {
	X11GRAB_OK = 0,
	X11GRAB_CANT_OPEN_DISPLAY = -1,
	X11GRAB_NOT_INITIALIZED = -2
};


int x11grab_init(struct x11grab_config* cfg);

int x11grab_close(void);

XImage* x11grab_get_sub_image(int x, int y, unsigned int w, unsigned int h);

void x11grab_mean_color(XImage* image, unsigned int x, unsigned int y, unsigned int w, unsigned int h, color_t* color);


#endif /* XSCREENSHOT_H_ */
