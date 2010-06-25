/*
 * ambilight.h
 *
 *  Created on: 2010-06-25
 *      Author: kharg
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
