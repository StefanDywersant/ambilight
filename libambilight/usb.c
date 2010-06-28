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


#include <stdio.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

#include "usb.h"

#define DEV_VENDOR_ID			0x16c0
#define DEV_PRODUCT_ID			0x03e8
#define DEV_MANUFACTURER_NAME	"czystybeton.pl"
#define DEV_PRODUCT_NAME		"Ambilight"

#define CMD_UPDATE_LEDS			0x04


static libusb_device_handle* dev = NULL;


static int _transmit(unsigned char led_no, unsigned char* data) {
	if (dev == NULL)
		return AMBILIGHT_NO_DEVICE;

	int ret = libusb_control_transfer(
			dev,
			LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_OUT,
			led_no,
			(uint16_t)(data[0] | data[1] << 8),
			(uint16_t)data[2],
			NULL,
			0,
			10000
		);

	if (ret > 0)
		return AMBILIGHT_OK;

	switch(ret) {
	case LIBUSB_ERROR_NO_DEVICE:
		usb_close_device();
		return AMBILIGHT_NO_DEVICE;
	case LIBUSB_ERROR_TIMEOUT:
		usb_close_device();
		return AMBILIGHT_DEVICE_TIMEOUT;
	default:
		return AMBILIGHT_DEVICE_ERROR;
	}
}


int usb_open_device(void) {
	libusb_device** devices;
	ssize_t devices_cnt;
	uint16_t i;

	if (dev != NULL)
		return AMBILIGHT_DEVICE_ERROR;

	libusb_init(NULL);

	devices_cnt = libusb_get_device_list(NULL, &devices);

	printf("Looking for device...\n");

	for (i = 0; i < devices_cnt; i++) {
		struct libusb_device_descriptor dev_descriptor;
		unsigned char manufacturer_name[256];
		unsigned char product_name[256];
		libusb_device_handle* tmp_dev_handle;

		if (libusb_get_device_descriptor(devices[i], &dev_descriptor) < 0) {
			printf("Cannot get device's #%d descriptor!\n", i);
			continue;
		}

		if (dev_descriptor.idVendor != DEV_VENDOR_ID || dev_descriptor.idProduct != DEV_PRODUCT_ID)
			continue;

		if (libusb_open(devices[i], &tmp_dev_handle) < 0) {
			printf("Cannot open device %04x:%04x!\n", dev_descriptor.idVendor, dev_descriptor.idProduct);
			continue;
		}

		if (libusb_get_string_descriptor_ascii(tmp_dev_handle, dev_descriptor.iManufacturer, manufacturer_name, sizeof(manufacturer_name)) < 0) {
			printf("Cannot get manufacturer string from device %04x:%04x!\n", dev_descriptor.idVendor, dev_descriptor.idProduct);
			libusb_close(tmp_dev_handle);
			continue;
		}

		if (libusb_get_string_descriptor_ascii(tmp_dev_handle, dev_descriptor.iProduct, product_name, sizeof(product_name)) < 0) {
			printf("Cannot get product string from device %04x:%04x!\n", dev_descriptor.idVendor, dev_descriptor.idProduct);
			libusb_close(tmp_dev_handle);
			continue;
		}

		if (strncmp(DEV_MANUFACTURER_NAME, (char*)manufacturer_name, 256) != 0 || strncmp(DEV_PRODUCT_NAME, (char*)product_name, 256) != 0) {
			libusb_close(tmp_dev_handle);
			continue;
		}

		// device found
		printf("Device found at %04d:%04d\n", libusb_get_bus_number(devices[i]), libusb_get_device_address(devices[i]));
		printf("Device info: %s / %s [%04x:%04x]\n", manufacturer_name, product_name, dev_descriptor.idVendor, dev_descriptor.idProduct);

		dev = tmp_dev_handle;
		libusb_free_device_list(devices, devices_cnt);
		return AMBILIGHT_OK;
	}

	// device not found
	libusb_free_device_list(devices, devices_cnt);
	return AMBILIGHT_NO_DEVICE;
}


void usb_close_device() {
	libusb_close(dev);
	libusb_exit(NULL);
}


int usb_transmit_single(unsigned char led_no, ambilight_led* led) {
	return _transmit(led_no, (unsigned char*)led);
}
