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


typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} color_t;


void ambilight_init();

void ambilight_refresh(unsigned int led_no);


#endif /* AMBILIGHT_H_ */
