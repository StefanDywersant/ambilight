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


#include <X11/Xlib.h>
#include "xscreenshot.h"
#include "ambilight.h"


XImage* xscreenshot_take_screenshot(int x, int y, unsigned int w, unsigned int h) {
	Display *display = XOpenDisplay(NULL);
	XImage *image = XGetImage(display, XDefaultRootWindow(display), x, y, w, h, AllPlanes, ZPixmap);
	XCloseDisplay(display);
	return image;
}


void xscreenshot_mean_color(XImage* image, unsigned int x, unsigned int y, unsigned int w, unsigned int h, color_t* color) {
	unsigned int i, j;
	unsigned int r, g, b;

	r = g = b = 0;

	for (i = x; i < x + w; i++) {
		for (j = y; j < y + h; j++) {
			unsigned long color = image->f.get_pixel(image, i, j);
			r += (unsigned char)(color >> 16);
			g += (unsigned char)(color >> 8);
			b += (unsigned char)color;
		}
	}

	color->r = (unsigned char)(r / (w * h));
	color->g = (unsigned char)(g / (w * h));
	color->b = (unsigned char)(b / (w * h));
}


void xscreenshot_destroy_image(XImage* image) {
	image->f.destroy_image(image);
}
