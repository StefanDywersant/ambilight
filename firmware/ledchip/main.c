/**
 * Ambilight
 * Aktywne podświetlenie monitora.
 *
 * Copyright: (c) 2010 by Karol Maciaszek
 * E-mail   : <karol.maciaszek@gmail.com>
 * WWW      : http://www.czystybeton.pl/
 *
 * $Id$
 */

#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "debug.h"
#include "rgbled.h"
#include "spi.h"


/**
 * Structure containing current led color.
 */
static rgbled_colour* colour;


/**
 * Byte number in packet received through SPI from IOChip.
 */
static uint8_t byte_no = 0;


uint8_t rx_byte(uint8_t byte) {
	switch (byte_no) {
	case 0x00:
		colour->r = byte;
		return ++byte_no;
	case 0x01:
		colour->g = byte;
		return ++byte_no;
	case 0x02:
		colour->b = byte;
		return ++byte_no;
	default:
		rgbled_set_colour(byte, colour);
		return byte_no = 0x00;
	}
}


int main(void) {
	colour = (rgbled_colour*)malloc(sizeof(rgbled_colour));

	debug_init();

	PRINTF("\nAmbilight device\n");

	PRINTF("Enabling interrupts... ");
	sei();
	PRINTF("done");

	PRINTF("Initializing SPI... ");
	spi_init_slave(&rx_byte);
	PRINTF("done\n");

	PRINTF("Initializing led buffer... ");
	rgbled_init();
	PRINTF("done\n");

	PRINTF("Entering main loop...\n");

	while (1)
		rgbled_refresh();

	return 0;
}
