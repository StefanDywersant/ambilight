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


int usb_open_device(void) {
	libusb_device** devices;
	ssize_t devices_cnt;
	uint16_t i;

	if (dev != NULL)
		return USB_ERROR_DEVICE_OPENED;

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
		return USB_OK;
	}

	// device not found
	libusb_free_device_list(devices, devices_cnt);
	return USB_ERROR_NO_DEVICE;
}


int usb_transmit(unsigned char* payload) {
	if (dev == NULL)
		return USB_ERROR_NO_DEVICE;

	int ret = libusb_control_transfer(dev, LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_OUT, CMD_UPDATE_LEDS, 0 ,0, payload, 3, 10000);

	if (ret > 0)
		return USB_OK;

	switch(ret) {
	case LIBUSB_ERROR_NO_DEVICE:
		usb_close_device();
		return USB_ERROR_NO_DEVICE;
	case LIBUSB_ERROR_PIPE:
		return USB_ERROR_PIPE;
	case LIBUSB_ERROR_TIMEOUT:
		usb_close_device();
		return USB_ERROR_TIMEOUT;
	default:
		return USB_ERROR;
	}
}


void usb_close_device() {
	libusb_close(dev);
	libusb_exit(NULL);
}
