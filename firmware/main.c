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
#include "usbdrv.h"


rgbled_colour* colour;


usbMsgLen_t usbFunctionSetup(uchar data[8]) {
	usbRequest_t* request = (usbRequest_t*)data;

	colour->r = request->wValue.bytes[0];
	colour->g = request->wValue.bytes[1];
	colour->b = request->wIndex.bytes[0];

	rgbled_set_colour(request->bRequest, colour);

	return 0;
}


int main(void) {
	colour = (rgbled_colour*)malloc(sizeof(rgbled_colour));

	debug_init();

	PRINTF("\nAmbilight device\n");

	PRINTF("Initializing USB... ");
	usbInit();
	usbDeviceDisconnect();
	_delay_ms(250);
	usbDeviceConnect();
	PRINTF("done\n");

	sei();

	PRINTF("Initializing led buffer... ");
	rgbled_init(&usbPoll);
	PRINTF("done\n");

	colour->r = 0;
	colour->g = 0;
	colour->b = 0;
	rgbled_set_colour(0, colour);

	PRINTF("Entering main loop...\n");

	while (1)
		rgbled_refresh();

	return 0;
}
