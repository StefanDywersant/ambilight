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
#include "x11grab.h"
#include "ambilight.h"


static Display* display = NULL;


int x11grab_init(void) {
	display = XOpenDisplay(NULL);

	if (display == NULL)
		return X11GRAB_CANT_OPEN_DISPLAY;

	return X11GRAB_OK;
}


int x11grab_close(void) {
	if (display == NULL)
		return X11GRAB_NOT_INITIALIZED;

	XCloseDisplay(display);
	display = NULL;

	return X11GRAB_OK;
}

XImage* x11grab_get_sub_image(int x, int y, unsigned int w, unsigned int h) {
//	if (display == NULL)
//		return X11GRAB_NOT_INITIALIZED;

	XImage *image = XGetImage(display, XDefaultRootWindow(display), x, y, w, h, AllPlanes, ZPixmap);

	return image;
}


void x11grab_mean_color(XImage* image, unsigned int x, unsigned int y, unsigned int w, unsigned int h, color_t* color) {
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


void x11grab_get_dimensions() {

}


void x11grab_destroy_image(XImage* image) {
	image->f.destroy_image(image);
}
