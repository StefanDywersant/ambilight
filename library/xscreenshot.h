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


XImage* xscreenshot_take_screenshot(int x, int y, unsigned int w, unsigned int h);

void xscreenshot_mean_color(XImage* image, unsigned int x, unsigned int y, unsigned int w, unsigned int h, color_t* color);

void xscreenshot_destroy_image(XImage* image);


#endif /* XSCREENSHOT_H_ */
