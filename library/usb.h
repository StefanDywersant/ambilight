/*
 * usb.h
 *
 *  Created on: 2010-06-24
 *      Author: kharg
 */

#ifndef USB_H_
#define USB_H_


enum usb_error {
	USB_OK = 0,
	USB_ERROR_NO_DEVICE = -1,
	USB_ERROR_PIPE = -2,
	USB_ERROR_TIMEOUT = -3,
	USB_ERROR_DEVICE_OPENED = -4,
	USB_ERROR = -99
};


int usb_open_device();

int usb_transmit(unsigned char* payload);

void usb_close_device();


#endif /* USB_H_ */
