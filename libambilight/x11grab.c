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
#include <X11/Xlib.h>

#include "x11grab.h"
#include "ambilight.h"


static Display* display = NULL;

struct _scr_size {
	int width;
	int height;
};


struct _images {
	XImage* top;
	XImage* bottom;
	XImage* left;
	XImage* right;
};

static struct x11grab_config config;

static struct _scr_size scr_size;

static struct _images images;


static void _update_images(void) {
	if (images.top != NULL)
		images.top->f.destroy_image(images.top);

	images.top = XGetImage(
			display,
			XDefaultRootWindow(display),
			config.margin_left,
			config.margin_top,
			scr_size.width - config.margin_left - config.margin_right,
			config.edge_thickness,
			AllPlanes,
			ZPixmap
		);

	if (images.left != NULL)
		images.left->f.destroy_image(images.left);

	images.left = XGetImage(
			display,
			XDefaultRootWindow(display),
			config.margin_left,
			config.margin_top + config.edge_thickness,
			config.edge_thickness,
			scr_size.height - config.margin_top - config.margin_bottom - 2 * config.edge_thickness,
			AllPlanes,
			ZPixmap
		);

	if (images.bottom != NULL)
		images.bottom->f.destroy_image(images.bottom);

	images.bottom = XGetImage(
			display,
		XDefaultRootWindow(display),
				config.margin_left,
			scr_size.height - config.margin_bottom - config.edge_thickness,
			scr_size.width - config.margin_left - config.margin_right,
			config.edge_thickness,
			AllPlanes,
			ZPixmap
		);

	if (images.right != NULL)
		images.right->f.destroy_image(images.right);

	images.right = XGetImage(
			display,
			XDefaultRootWindow(display),
			scr_size.width - config.margin_right - config.edge_thickness,
			config.margin_top + config.edge_thickness,
			config.edge_thickness,
			scr_size.height - config.margin_top - config.margin_bottom - 2 * config.edge_thickness,
			AllPlanes,
			ZPixmap
		);
}


int x11grab_init(struct x11grab_config* cfg) {
	config.edge_thickness = cfg->edge_thickness;
	config.margin_left = cfg->margin_left;
	config.margin_bottom = cfg->margin_bottom;
	config.margin_right = cfg->margin_right;
	config.margin_top = cfg->margin_top;

	display = XOpenDisplay(NULL);

	if (display == NULL)
		return X11GRAB_CANT_OPEN_DISPLAY;

	scr_size.width = XDisplayWidth(display, 0);
	scr_size.height = XDisplayHeight(display, 0);

	_update_images();

	return X11GRAB_OK;
}


int x11grab_close(void) {
	if (display == NULL)
		return X11GRAB_NOT_INITIALIZED;

	XCloseDisplay(display);
	display = NULL;

	images.top->f.destroy_image(images.top);
	images.left->f.destroy_image(images.left);
	images.bottom->f.destroy_image(images.bottom);
	images.right->f.destroy_image(images.right);

	return X11GRAB_OK;
}


XImage* x11grab_get_sub_image(int x, int y, unsigned int w, unsigned int h) {
//	if (display == NULL)
//		return X11GRAB_NOT_INITIALIZED;

//	XImage *image = XGetImage(display, XDefaultRootWindow(display), x, y, w, h, AllPlanes, ZPixmap);

	_update_images();

//	printf("%d %d\n", config.edge_thickness, config.margin_bottom);

	return images.top;
}


void x11grab_mean_color(XImage* image, unsigned int x, unsigned int y, unsigned int w, unsigned int h, color_t* color) {
	unsigned int i, j;
	unsigned int r, g, b;

	r = g = b = 0;

	for (i = x; i < x + w; i++) {
		for (j = y; j < y + h; j++) {
			unsigned long color = image->f.get_pixel(image, i, j);
			r += (unsigned char)(color >> 16);
			g += (unsigned char)(color >> 8);
			b += (unsigned char)color;
		}
	}

	color->r = (unsigned char)(r / (w * h));
	color->g = (unsigned char)(g / (w * h));
	color->b = (unsigned char)(b / (w * h));
}

