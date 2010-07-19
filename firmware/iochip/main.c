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

#include <usbdrv.h>
#include <softspi.h>


usbMsgLen_t usbFunctionSetup(uchar data[8]) {
	usbRequest_t* request = (usbRequest_t*)data;

	// begin spi transaction
	softspi_begin();

	softspi_write_data(1, &request->bRequest);	// led no
	softspi_write_data(1, &request->wValue.bytes[0]); // red
	softspi_write_data(1, &request->wValue.bytes[1]); // green
	softspi_write_data(1, &request->wIndex.bytes[0]); // blue

	softspi_end();
	// end spi transaction

	return 0;
}


int main(void) {

	usbInit();
	usbDeviceDisconnect();
	_delay_ms(250);
	usbDeviceConnect();

	softspi_init();

	sei();

	while (1)
		usbPoll();

	return 0;
}
