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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>

#include "ambilight.h"
#include "usb.h"
#include "x11capture.h"


static struct ambilight_config* config;


int ambilight_configure(struct ambilight_config* cfg) {
	config = cfg;
	x11capture_close();
	return x11capture_init(config);
}


int ambilight_open_device(void) {
	return usb_open_device();
}


void ambilight_close_device(void) {
	usb_close_device();
}


void ambilight_refresh(void) {
	x11capture_refresh();

	unsigned char i;
	for (i = 0; i < (config->leds_top + config->leds_left + config->leds_bottom + config->leds_right); i++) {
		usb_transmit_single(i, x11capture_get_led(i));
		usleep(1000000 / (config->frequency * (config->leds_top + config->leds_left + config->leds_bottom + config->leds_right)));
	}
}


int ambilight_get_screenshot(XImage* screenshot) {
	return x11capture_get_screenshot(screenshot);
}
