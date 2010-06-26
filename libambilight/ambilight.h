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


void ambilight_init(struct ambilight_config* cfg);

void ambilight_refresh(void);


#endif /* AMBILIGHT_H_ */
