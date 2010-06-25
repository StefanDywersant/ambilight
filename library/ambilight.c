/*
 * ambilight.c
 *
 *  Created on: 2010-06-25
 *      Author: kharg
 */


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include "ambilight.h"
#include "usb.h"
#include "xscreenshot.h"


void ambilight_init() {
	usb_open_device();
}


void ambilight_refresh(unsigned int led_no) {
	XImage* image;
	color_t* color;

	color = (color_t*)malloc(sizeof(color_t));

	image = xscreenshot_take_screenshot(150, 150, 100, 100);

	xscreenshot_mean_color(image, 0, 0, 100, 100, color);

	xscreenshot_destroy_image(image);

	printf("(%03d,%03d,%03d)\n", color->r, color->g, color->b);

	usb_transmit((uint8_t*)color);

	free(color);
}
