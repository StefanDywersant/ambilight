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

	struct x11grab_config config;
	config.edge_thickness = 30;
	config.margin_bottom = 0;
	config.margin_left = 0;
	config.margin_right = 0;
	config.margin_top = 0;

	x11grab_init(&config);
}


void ambilight_refresh(unsigned int led_no) {
	XImage* image;
//	color_t* color;

//	color = (color_t*)malloc(sizeof(color_t));

	image = x11grab_get_sub_image(0, 0, 1920, 30);

//	x11grab_mean_color(image, 0, 0, 100, 100, color);

//	printf("(%03d,%03d,%03d)\n", color->r, color->g, color->b);

//	usb_transmit((uint8_t*)color);

//	free(color);
}
