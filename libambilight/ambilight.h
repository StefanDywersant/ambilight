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


#ifndef AMBILIGHT_H_
#define AMBILIGHT_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#include <X11/Xlib.h>


enum ambilight_error {
	AMBILIGHT_OK = 0,
	AMBILIGHT_ERROR = 1,

	AMBILIGHT_NO_DEVICE = 2,
	AMBILIGHT_DEVICE_TIMEOUT = 4,
	AMBILIGHT_DEVICE_NOT_INITIALIZED = 8,
	AMBILIGHT_DEVICE_ERROR = 16,

	AMBILIGHT_CANT_OPEN_DISPLAY = 32,
	AMBILIGHT_DISPLAY_NOT_INITIALIZED = 64
};


struct ambilight_config {
	unsigned int frequency;
	unsigned char leds_top;
	unsigned char leds_bottom;
	unsigned char leds_left;
	unsigned char leds_right;
	unsigned int edge_thickness;
	unsigned int margin_top;
	unsigned int margin_bottom;
	unsigned int margin_left;
	unsigned int margin_right;
};


typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} ambilight_led;


int ambilight_configure(struct ambilight_config* cfg);

int ambilight_open_device(void);

void ambilight_close_device(void);

void ambilight_refresh(void);

int ambilight_get_screenshot(XImage* screenshot);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AMBILIGHT_H_ */
