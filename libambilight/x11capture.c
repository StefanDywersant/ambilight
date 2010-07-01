/**
 * Ambilight Project
 * Ambilight device access library
 *
 * Copyright: (c) 2010 by Karol Maciaszek
 * E-mail   : <karol.maciaszek@gmail.com>
 * WWW      : http://www.czystybeton.pl/
 *
 * $Id: x11grab.c 7 2010-06-26 06:40:45Z kharg $
 */


#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#include "x11capture.h"
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


typedef struct {
	XImage** image;
	int x;
	int y;
	int w;
	int h;
} _area;


static _area* areas;

static ambilight_led* leds;

static struct ambilight_config config;

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


static void _init_areas(void) {
	int i;
	int led_no = 0;

	// allocate memory for areas
	areas = (_area*)malloc((config.leds_bottom + config.leds_left + config.leds_right + config.leds_top) * sizeof(_area));

	// calculate top led bar
	for (i = 0; i < config.leds_top; i++) {
		double w = (double)images.top->width / config.leds_top;

		areas[led_no].x = i * w;
		areas[led_no].y = 0;
		areas[led_no].w = w;
		areas[led_no].h = config.edge_thickness;

		printf("led_no=%d (x,y)=(%d,%d) (w,h)=(%d,%d)\n", led_no, areas[led_no].x, areas[led_no].y, areas[led_no].w, areas[led_no].h);

		areas[led_no].image = &images.top;
		led_no++;
	}

	// calculate right led bar
	for (i = 0; i < config.leds_right; i++) {
		double h = (double)images.right->height / config.leds_right;

		areas[led_no].x = 0;
		areas[led_no].y = i * h;
		areas[led_no].w = config.edge_thickness;
		areas[led_no].h = h;

		printf("led_no=%d (x,y)=(%d,%d) (w,h)=(%d,%d)\n", led_no, areas[led_no].x, areas[led_no].y, areas[led_no].w, areas[led_no].h);

		areas[led_no].image = &images.right;
		led_no++;
	}

	// calculate bottom led bar
	for (i = config.leds_bottom - 1; i > -1; i--) {
		double w = (double)images.bottom->width / config.leds_bottom;

		areas[led_no].x = i * w;
		areas[led_no].y = 0;
		areas[led_no].w = w;
		areas[led_no].h = config.edge_thickness;

		printf("led_no=%d (x,y)=(%d,%d) (w,h)=(%d,%d)\n", led_no, areas[led_no].x, areas[led_no].y, areas[led_no].w, areas[led_no].h);

		areas[led_no].image = &images.bottom;
		led_no++;
	}

	// calculate left led bar
	for (i = config.leds_left - 1; i > -1 ; i--) {
		double h = (double)images.left->height / config.leds_left;

		areas[led_no].x = 0;
		areas[led_no].y = i * h;
		areas[led_no].w = config.edge_thickness;
		areas[led_no].h = h;

		printf("led_no=%d (x,y)=(%d,%d) (w,h)=(%d,%d)\n", led_no, areas[led_no].x, areas[led_no].y, areas[led_no].w, areas[led_no].h);

		areas[led_no].image = &images.left;
		led_no++;
	}
}


static void _calculate_mean(_area* area, ambilight_led* led) {
	int x, y;
	long r = 0;
	long g = 0;
	long b = 0;

//	printf("(x,y)=(%d,%d) (w,h)=(%d,%d) (iw,ih)=(%d,%d)\n", area->x, area->y, area->w, area->h, (*area->image)->width, (*area->image)->height);

	for (x = area->x; x < area->x + area->w; x++) {
		for (y = area->y; y < area->y + area->h; y++) {
			unsigned long color = (*area->image)->f.get_pixel(*area->image, x, y);
//			printf("%dx%d ", x, y);
//			unsigned long color = 0xf000f0;
			r += (unsigned char)(color >> 16);
			g += (unsigned char)(color >> 8);
			b += (unsigned char)(color);
		}
//		printf("\n");
	}
//	printf("\n\n");

	led->r = (unsigned char)(r / (area->w * area->h));
	led->g = (unsigned char)(g / (area->w * area->h));
	led->b = (unsigned char)(b / (area->w * area->h));
}



int x11capture_init(struct ambilight_config* cfg) {
	config.edge_thickness = cfg->edge_thickness;
	config.margin_left = cfg->margin_left;
	config.margin_bottom = cfg->margin_bottom;
	config.margin_right = cfg->margin_right;
	config.margin_top = cfg->margin_top;
	config.leds_left = cfg->leds_left;
	config.leds_bottom = cfg->leds_bottom;
	config.leds_right = cfg->leds_right;
	config.leds_top = cfg->leds_top;

	display = XOpenDisplay(NULL);

	if (display == NULL)
		return AMBILIGHT_DISPLAY_NOT_INITIALIZED;

	scr_size.width = XDisplayWidth(display, 0);
	scr_size.height = XDisplayHeight(display, 0);

	// allocate memory for leds
	leds = (ambilight_led*)malloc((config.leds_bottom + config.leds_left + config.leds_right + config.leds_top) * sizeof(ambilight_led));

	_update_images();

	_init_areas();

	return AMBILIGHT_OK;
}


int x11capture_close(void) {
	if (display == NULL)
		return AMBILIGHT_DISPLAY_NOT_INITIALIZED;

	// close display pointer
	XCloseDisplay(display);
	display = NULL;

	// destroy image structures
	images.top->f.destroy_image(images.top);
	images.left->f.destroy_image(images.left);
	images.bottom->f.destroy_image(images.bottom);
	images.right->f.destroy_image(images.right);

	// clean up areas cache
	int i;
	for (i = 0; i < config.leds_bottom + config.leds_left + config.leds_right + config.leds_top; i++)
		free(&areas[i]);

	// clean up leds cache
	for (i = 0; i < config.leds_bottom + config.leds_left + config.leds_right + config.leds_top; i++)
		free(&leds[i]);

	return AMBILIGHT_OK;
}


void x11capture_refresh(void) {
	// update image cache
	_update_images();

	// calculate led colors for each area
	int i;
	for (i = 0; i < config.leds_bottom + config.leds_left + config.leds_right + config.leds_top; i++)
		_calculate_mean(&areas[i], &leds[i]);
}


ambilight_led* x11capture_get_led(unsigned char led_no) {
	return &leds[led_no];
}


int x11capture_get_screenshot(XImage* screenshot) {
	if (display == NULL)
		return AMBILIGHT_DISPLAY_NOT_INITIALIZED;

	screenshot = XGetImage(
			display,
			XDefaultRootWindow(display),
			0,
			0,
			scr_size.width,
			scr_size.height,
			AllPlanes,
			ZPixmap
		);

	return AMBILIGHT_OK;
}
