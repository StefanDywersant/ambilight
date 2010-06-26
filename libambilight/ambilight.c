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


void ambilight_init(struct ambilight_config* cfg) {
	usb_open_device();

	config = cfg;

	x11capture_init(config);
}


void ambilight_refresh(void) {
	x11capture_refresh();

	unsigned char i;
	for (i = 0; i < (config->leds_top + config->leds_left + config->leds_bottom + config->leds_right); i++) {
		usb_transmit_single(i, x11capture_get_led(i));
		usleep(1000000 / (config->frequency * (config->leds_top + config->leds_left + config->leds_bottom + config->leds_right)));
	}


}
