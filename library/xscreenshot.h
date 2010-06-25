/*
 * xscreenshot.h
 *
 *  Created on: 2010-06-25
 *      Author: kharg
 */

#ifndef XSCREENSHOT_H_
#define XSCREENSHOT_H_

#include "ambilight.h"


XImage* xscreenshot_take_screenshot(int x, int y, unsigned int w, unsigned int h);

void xscreenshot_mean_color(XImage* image, unsigned int x, unsigned int y, unsigned int w, unsigned int h, color_t* color);

void xscreenshot_destroy_image(XImage* image);


#endif /* XSCREENSHOT_H_ */
