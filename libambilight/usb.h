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


#ifndef USB_H_
#define USB_H_

#include "ambilight.h"


enum usb_error {
	USB_OK = 0,
	USB_ERROR_NO_DEVICE = -1,
	USB_ERROR_PIPE = -2,
	USB_ERROR_TIMEOUT = -3,
	USB_ERROR_DEVICE_OPENED = -4,
	USB_ERROR = -99
};


int usb_open_device();

void usb_close_device();

int usb_reset(void);

int usb_transmit_single(unsigned char led_no, ambilight_led* led);

#endif /* USB_H_ */
