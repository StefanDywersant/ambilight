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
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <debug.h>
#include <hwspi.h>
#include <usbdrv.h>


usbMsgLen_t usbFunctionSetup(uchar data[8]) {
	usbRequest_t* request = (usbRequest_t*)data;
	uint8_t dupsko;

	hwspi_begin();

	dupsko = hwspi_read_write_byte(request->wValue.bytes[0]); // red
	PRINTF("%02x", dupsko);

	dupsko = hwspi_read_write_byte(request->wValue.bytes[1]); // green
	PRINTF("%02x", dupsko);

	dupsko = hwspi_read_write_byte(request->wIndex.bytes[0]); // blue
	PRINTF("%02x", dupsko);

	dupsko = hwspi_read_write_byte(request->bRequest);	// led no
	PRINTF("%02x\n", dupsko);

	hwspi_end();

	return 0;
}


int main(void) {

	debug_init();

	PRINTF("Ambilight IOChip\n");

	usbInit();
	usbDeviceDisconnect();
	_delay_ms(1000);
	usbDeviceConnect();

	hwspi_init_master();

	sei();

	while (1) {
		usbPoll();
	}

	return 0;
}
