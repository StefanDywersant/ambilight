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


rgbled_colour* colour;


int main(void) {
	colour = (rgbled_colour*)malloc(sizeof(rgbled_colour));

	debug_init();

	PRINTF("\nAmbilight device\n");

	sei();

	PRINTF("Initializing led buffer... ");
	rgbled_init();
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
