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


int usb_open_device();

void usb_close_device();

int usb_reset(void);

int usb_transmit_single(unsigned char led_no, ambilight_led* led);

#endif /* USB_H_ */
