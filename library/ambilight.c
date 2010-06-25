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


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include "ambilight.h"
#include "usb.h"
#include "x11grab.h"


void ambilight_init() {
	usb_open_device();
	x11grab_init();
}


void ambilight_refresh(unsigned int led_no) {
	XImage* image;
	color_t* color;

	color = (color_t*)malloc(sizeof(color_t));

	image = x11grab_get_sub_image(150, 150, 100, 100);

	x11grab_mean_color(image, 0, 0, 100, 100, color);

	x11grab_destroy_image(image);

	printf("(%03d,%03d,%03d)\n", color->r, color->g, color->b);

	usb_transmit((uint8_t*)color);

	free(color);
}
